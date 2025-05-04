// OsuParser.cpp — 完整支援 Slider 尾端時間計算 (SM, SV, Timing)
#include "OsuParser.h"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <optional>
#include <string.h>

// ───────── 工具函式 ────────────────────────────────────────────────
static inline std::string trim(const std::string &s) {
    const char *ws = " \t\r\n";
    const auto b = s.find_first_not_of(ws);
    if (b == std::string::npos) return "";
    return s.substr(b, s.find_last_not_of(ws) - b + 1);
}
static inline bool toInt(const std::string &s,int &o){try{o=std::stoi(s);return true;}catch(...){return false;}}
static inline double toD(const std::string &s){try{return std::stod(s);}catch(...){return 0.0;}}

// ───────── 結構 ───────────────────────────────────────────────────
struct TimingPoint{ double offset=0; double msPerBeat=0; bool inherited=false;};

// ───────── 協助查詢當前 BPM / SV ──────────────────────────────────
static std::tuple<double,double> queryTiming(const std::vector<TimingPoint>&tp,double time){
    double beatLen=500, sv=1.0;
    for(const auto& t:tp){
        if(t.offset>time) break;
        if(!t.inherited)  beatLen=t.msPerBeat;
        else              sv= -100.0 / t.msPerBeat;
    }
    return {beatLen,sv};
}

// ───────── 解析主流程 ─────────────────────────────────────────────
bool OsuParser::ParseFile(const std::string &path, LevelData &out){
    std::ifstream in(path); if(!in.is_open()) return false;

    enum class Sec{None,Diff,Timing,Hit}; Sec cur=Sec::None;
    std::string line;
    double sliderMultiplier=1.4;                   // default
    std::vector<TimingPoint> timings;

    while(std::getline(in,line)){
        line=trim(line); if(line.empty()||line[0]=='\ufeff') continue;
        if(line[0]=='['){
            if(line=="[Difficulty]")cur=Sec::Diff;
            else if(line=="[TimingPoints]")cur=Sec::Timing;
            else if(line=="[HitObjects]") cur=Sec::Hit;
            else cur=Sec::None; continue;}

        // ───────── Difficulty 取 SliderMultiplier 與 AR ─────
        if(cur==Sec::Diff){
            if (auto p = line.find("HPDrainRate:"); p != std::string::npos) {
                // 取出冒號之後的數字
                std::string v = trim(line.substr(p + strlen("HPDrainRate:")));
                out.hpDrainRate = std::stoi(v);
            }
            if(auto p=line.find("SliderMultiplier:");p!=std::string::npos)
                sliderMultiplier= toD(trim(line.substr(p+17)));
            if(auto p=line.find("ApproachRate:");p!=std::string::npos){
                double ar= toD(trim(line.substr(p+13)));
                if(ar<= 5) out.approachMs=int(1800-120*ar);
                else out.approachMs=int(1200-150*(ar-5));
            }
            if(auto p=line.find("HPDrainRate:");p!=std::string::npos) {
                double hpd = toD(trim(line.substr(p + 13)));
                out.diff = hpd;
            }
        }
        // ───────── TimingPoints 收集 ───────────────────
        else if(cur==Sec::Timing){
            std::stringstream ss(line); std::string tok;
            TimingPoint tp; ss>>tp.offset; ss.ignore();
            ss>>tp.msPerBeat; tp.inherited = tp.msPerBeat<0;
            timings.push_back(tp);
        }
        // ───────── HitObjects 解析 ─────────────────────
        else if(cur==Sec::Hit){
            std::stringstream ss(line); std::string tok;
            int x=0,y=0,type=0,repeat=0; int pixelLen=0; int64_t time=0;
            if(!std::getline(ss,tok,','))continue; toInt(tok,x);
            if(!std::getline(ss,tok,','))continue; toInt(tok,y);
            if(!std::getline(ss,tok,','))continue; time=std::stoll(tok);
            if(!std::getline(ss,tok,','))continue; type=std::stoi(tok);
            std::getline(ss,tok,',');                // hitSound skip

            if(type & 2){ // Slider
                std::string curve; std::getline(ss,curve,',');
                std::getline(ss,tok,','); repeat=std::stoi(tok);
                std::getline(ss,tok,','); pixelLen=std::stoi(tok);

                // 終點座標 = 曲線定義第一個節點
                int tailX=x, tailY=y;
                auto bar=curve.find('|'); if(bar!=std::string::npos){
                    std::string node=curve.substr(bar+1);
                    auto colon=node.find(':');
                    if(colon!=std::string::npos){
                       toInt(node.substr(0,colon),tailX);
                       toInt(node.substr(colon+1,node.find('|')-colon-1),tailY);
                    }
                }

                // 查 BPM & SV
                auto [beatLen,sv]=queryTiming(timings,time);
                double velocity= sliderMultiplier*sv*100.0;
                double spanMs = (double)pixelLen / velocity * beatLen;
                double totalMs= spanMs * repeat;
                int64_t tailTime = time + (int64_t)(totalMs+0.5);

                out.objects.push_back({x,y,time});
                out.objects.push_back({tailX,tailY,tailTime});
            }
            else{ // HitCircle
                out.objects.push_back({x,y,time});
            }
        }
    }

    if(out.approachMs<=0) out.approachMs=1200;
    std::stable_sort(out.objects.begin(),out.objects.end(),[](auto&a,auto&b){return a.hitTime<b.hitTime;});
    return !out.objects.empty();
}