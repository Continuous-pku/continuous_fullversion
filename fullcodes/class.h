
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<time.h>
#include<iostream>
#include<cstring>
#include<iomanip>
#include<cmath>
#include<list>
#include <string>
#include <vector>
#include<QWidget>
#include"mainw.h"
#include"QDebug"
#include"qfile.h"

using namespace std;
class Game;
class Person;
class Policy;
class Building;
class Affair;

class Hospital; // 医院
class Library; // 图书馆
class Gate; // 大门
class Laboratory; // 实验室
class Dormitory; // 宿舍
class TeachingBuilding; // 教学楼
class Playground; // 操场
class Gymnasium; // 体育馆
class DiningHall; // 餐厅
class Lake; // 未名湖

class RequireMasks; // 佩戴口罩 编号为0
class MeasureTemperatureAndScanCode; // 测温扫码 编号为1
class ShutDownBuilding; // 关闭建筑 编号为2
class AddBaffle; // 增设挡板 编号为3
class StopDineIn; // 停止堂食 编号为4
class TemporaryLockdown; // 临时关闭 编号为5
class ShutDownDormitory; // 关闭寝室 编号为6


class CoupleByLake; // 未名湖边的小情侣 0 Lake
class ReadByLake; // 未名湖畔好读书 1 Lake
class OnlineExhibition; // 线上展览 3 Library
class NastyMeals; // 难以下咽的饭菜 4 DiningHall
class LuxuriousIsolationConditions; // 豪华隔离条件 5 Hospital
class InterestingQurantineLife; // 有趣的隔离生活 6 Hospital
class BrokenWashingMachine; // 坏掉的洗衣机 7 Dormitory
class BrokenAirConditioner; // 坏掉的空调 8 Dormitory
class BrokenWaterHeater; // 坏掉的热水器 9 Dormitory
class Gathering; // 家园门口的聚集 10 DiningHall
class ProtesetInShudong; // 树洞里的抗议 11 All Building
class SingInDormitory; // 宿舍楼里的歌剧魅影 12 Dormitory
class ShushuBegins; // “鼠鼠”文学的泛滥 13 Dormitory
class QuarrelInDormitory; // 宿舍楼里的争吵 14 Dormitory
class UnbearableSnoring; // 难以忍受的打呼噜声 15 Dormitory
class Top10InBathroom; // 浴室里的十佳 16 Dormitory
class LearningInDormitory; // 宿舍里的自习室 17 Dormitory
class MahjongInDormitory; // 宿舍里的麻将馆 18 Dormitory
class HarmoniousDormitory; // 和谐的寝室 19 Dormitory
class HealthySleeping; // 健康的睡眠 20 Dormitory
class BrokenOutPersonnel; //员工开始崩溃 21 Hospital Library TeachingBuilding DiningHall
class VolunteerLack; // 基层志愿者人手短缺 22 Hospital
class LackOfMedicalResources; // 医疗资源短缺 23 Hospital
class GreatPrevention; // 井然有序的防控 24 Hospital
class Detention; // 处分！ 25 Gate
class Top10; // 十佳 26 Gymnasium
class BrokenHeater; // 暖气！该死的暖气坏了！ 27 Dormitory


class Do_pcr; // 全员核酸
class ReseachOnVirus; // 开始调查研究
class SuspendCampusTour; // 停止校园参观
class PostponeStartOfSchool; // 推迟开学
class ProvideDesktopVideo; // 提供桌面视屏会议
class StartOnlineCourse; // 开始网课
class StartPF; // 开始PF制

class Game {
    friend class buildings;
    friend class Policy;
private:
    int year;
    int month;
    int day;
    int hour;
    double overall_satisfaction;

    int activity_point;
    int sum_healthy_person;
    int sum_ill_person;
    int sum_quarantine_person;
    int sum_building;
    int total_infection_likelyhood=0;//影响全局感染速度
    bool is_building_shut_down = false;//判断当日有无建筑关闭
    Policy* all_policy[1000];
    Person* all_person[40000];
    bool ifpcr=false;//判断当日是否进行了核酸检测，如果进行了，小幅度提高当天的传染概率

    bool ifResearchOnVirusStart = false;//判断是否已经开始进行特效药研究
    bool ifResearchOnVirusDone = false;//判断特效药研究是否已经完成
    bool campusTour_state = false;//校园参观状态
    bool postponeStartOfSchool_state = false;//是否已延迟开学
    bool provideDesktopVideo_state = false;
    bool onlineCourse_state = false;
    bool PF_state = false;
    int researchOnVirusSchedule = 100;//"(100-this)%"为特效药研制进度
public:
    Game();
    void save(int i);
    void load(int i);
    Building* all_building[100];
    void gameRun();
    int start_newday();//这里把gamerun的功能拆开来成了两个部分
    bool gameWin();
    bool gameLose();
    bool gameEnd();
    void startSpread();
    void startQuarantine(); // 每个感染者都有概率被隔离，满14天后恢复健康
    void updateAllSatisfaction(); // 更新满意度
    void nextDay();
    void updateTrack();
    bool cost_ap(int t);
    void pcr();
    bool getpcr_state();
    void startResearchOnVirus();
    bool getResearchOnVirus_state();
    void suspendCampusTour();
    bool getCampusTour_state();
    void postponeStartOfSchool();
    bool getPostponeStartOfSchool_state();
    void provideDesktopVideo();
    bool getProvideDesktopVideo_state();
    void startOnlineCourse();
    bool getOnlineCourse_state();
    bool getPostponeStartOfschool_state();
    bool getProvideDesktopVideo();
    void startPF();
    bool getPF_state();
    Policy* get_policy(int i);
    Building* getBuilding(int idx);
    int getdate();
    int getsat();
    int getap();
    int getill();
    int getquarantine();
    int getSeason();
    string yam;
    mainw* win;
};
class Person {//�� ��
    friend class Game;
private:
    int health_state;//0 表示健康 1表示感染 2表示隔离
    int quarantine_day;//隔离天数
    bool is_now_infected;
    double satisfaction;
    int track[24];
public:
    Person();
    void updateSatisfaction(double delta);
    double getSatisfaction();
};
class Building
{
private:
    int level; // �����ﵱǰ�ĵȼ�

    Policy* available_policy[10];
    int policy_state[10];
    int kind;
    int idx;
    int action_point_per_day;
    int total_number_of_available;

    bool is_shut_down;
    int total_people;
    int total_infectd_people;
    int upgrade_cost[3];
    Person* people_in_building[40000];
public:
    friend class Game;
    friend class Policy;
    friend class buildings;
    friend class b_upgrade;
    friend class build_info;
    double change_in_infection_likelihood;
    Building(int _kind, int _idx,Game* _g);
    virtual void upgrade();
    void enactPolcy(int policy_idx);
    int produceActionPoint();
    void updateChange(double delta);
    void updateActionPoint(int delta);
    void shutDown();
    bool isShutDown();
    virtual void setInitialPolicy();
    void addPolicy(Policy* p);
    void updatePolicyState();
    void peopleArrived(int delta, Person* p);
    void infectedPeopleArrived(int delta);
    int getLevel();
    int getkind(); // 得到当前建筑物的种类
    int getaction_point_per_day(); // 得到当前建筑物每天产生的行动力
    virtual void addBaffle();
    int getInfectedNumber();
    int getTotalNumber();
    virtual void checkAffairHappen();
    void updateSatisfaction(double delta);
    bool isDormitoryShutDown();
    Game* g;
    bool isWinter();
    double getSatisfaction();

};

class DiningHall : public Building
{
private:
    bool added_baffle;
public:
    Affair* possible_affairs[10];
    int num_of_possible_affairs;
    DiningHall(int _idx, int _kind,Game* _g);
    void setInitialPolicy();
    void addBaffle();
    void checkAffairHappen();
};
class TeachingBuilding : public Building
{
public:
    TeachingBuilding(int _idx, int _kind,Game* _g);
    void setInitialPolicy();
    Affair* possible_affairs[10];
    int num_of_possible_affairs;
    void checkAffairHappen();
};
class Lake : public Building
{
private:
    Affair* possible_affairs[10];
    int number_of_possible_affairs;
public:
    Lake(int _idx, int _kind,Game* _g);
    void checkAffairHappen();
};
class Gymnasium : public Building
{
public:
    Gymnasium(int _idx, int _kind,Game* _g);
    Affair* possible_affairs[10];
    int num_of_possible_affairs;
    void checkAffairHappen();
};
class Playground : public Building
{
public:
    Playground(int _idx, int _kind,Game* _g);
    Affair* possible_affairs[10];
    int num_of_possible_affairs;
    void checkAffairHappen();
};
class Library : public Building
{
public:
    Affair* possible_affairs[10];
    int num_of_possible_affairs;
    Library(int _idx, int _kind,Game* _g);
    void checkAffairHappen();
};
class Gate : public Building
{
public:
    Gate(int _idx, int _kind,Game* _g);
    Affair* possible_affairs[10];
    int num_of_possible_affairs;
    void checkAffairHappen();
};
class Laboratory : public Building
{
public:
    Laboratory(int _idx, int _kind,Game* _g);
    Affair* possible_affairs[10];
    int num_of_possible_affairs;
    void checkAffairHappen();
};
class Hospital : public Building
{
public:
    Hospital(int _idx, int _kind,Game* _g);
    Affair* possible_affairs[10];
    int num_of_possible_affairs;
    void checkAffairHappen();
};
class Dormitory : public Building
{
public:
    Dormitory(int _idx, int _kind,Game* _g);
    void setInitialPolicy();
    Affair* possible_affairs[20];
    int num_of_possible_affairs;
    void checkAffairHappen();
};

class Policy
{
    friend class Game;
    friend class buildings;
private:
    int idx;
    Building* building_attached;
public:
    friend class pchoice;

    Policy(int _idx, int _cost, Building* _b);
    static Policy* all_policy[50];

    virtual void takeEffect();
    virtual void printPolicy();
    virtual bool available();
    Building* BuildingAttached();
    int cost;
};
class RequireMasks : public Policy
{
public:
    RequireMasks(int _idx, int _cost, Building* _b);
    void takeEffect();
    bool available();
    void printPolicy();
};
class MeasureTemperatureAndScanCode : public Policy
{
public:
    MeasureTemperatureAndScanCode(int _idx, int _cost, Building* _b);
    void takeEffect();
    bool available();
    void printPolicy();
};
class ShutDownBuilding : public Policy
{
public:
    ShutDownBuilding(int _idx, int _cost, Building* _b);
    void takeEffect();
    bool available();
    void printPolicy();
};
class AddBaffle : public Policy
{
public:
    AddBaffle(int _idx, int _cost, Building* _b);
    void takeEffect();
    bool available();
    void printPolicy();
};
class StopDineIn : public Policy
{
public:
    StopDineIn(int _idx, int _cost, Building* _b);
    void takeEffect();
    bool available();
    void printPolicy();
};
class TemporaryLockdown : public Policy
{
public:
    TemporaryLockdown(int _idx, int _cost, Building* _b);
    void takeEffect();
    bool available();
    void printPolicy();
};
class ShutDownDormitory : public Policy
{
public:
    ShutDownDormitory(int _idx, int _cost, Building* _b);
    void takeEffect();
    bool available();
    void printPolicy();
};

class Do_pcr:public Policy//全员核算检测
{
public:
    Do_pcr(int _idx, int _cost,Game*game, Building* _b=NULL);
    void takeEffect();
    bool available();
    void printPolicy();
    Game*g;
    bool ever_done=false;
};

class ResearchOnVirus :public Policy
{
public:
    ResearchOnVirus(int _idx, int _cost, Game* game, Building* _b = NULL);
    void takeEffect();
    bool available();
    void printPolicy();
    Game* g;
};

class SuspendCampusTour :public Policy
{
public:
    SuspendCampusTour(int _idx, int _cost, Game* game, Building* _b = NULL);
    void takeEffect();
    bool available();
    void printPolicy();
    Game* g;
};

class PostponeStartOfSchool :public Policy
{
public:
    PostponeStartOfSchool(int _idx, int _cost, Game* game, Building* _b = NULL);
    void takeEffect();
    bool available();
    void printPolicy();
    Game* g;
};

class ProvideDesktopVideo :public Policy
{
public:
    ProvideDesktopVideo(int _idx, int _cost, Game* game, Building* _b = NULL);
    void takeEffect();
    bool available();
    void printPolicy();
    Game* g;
};

class StartOnlineCourse :public Policy
{
public:
    StartOnlineCourse(int _idx, int _cost, Game* game, Building* _b = NULL);
    void takeEffect();
    bool available();
    void printPolicy();
    Game* g;
};

class StartPF :public Policy
{
public:
    StartPF(int _idx, int _cost, Game* game, Building* _b = NULL);
    void takeEffect();
    bool available();
    void printPolicy();
    Game* g;
};

class Affair
{
private:
    double probability_of_occurrence;
    Building* happened_place;

public:
    int idx;
    Affair(int _idx, double _p, Building* _b);
    virtual void takeEffect();
    virtual void printAffair();
    virtual void happen();
    double getProb();
    Building* getPlace();
};

class CoupleByLake : public Affair
{
public:
    CoupleByLake(int _idx, double _p, Building* _b);
    void happen();
    void takeEffect();
    void printAffair();
};
class ReadByLake : public Affair
{
public:
    ReadByLake(int _idx, double _p, Building* _b);
    void happen();
    void takeEffect();
    void printAffair();
};

class OnlineExhibition : public Affair
{
public:
    OnlineExhibition(int _idx, double _p, Building* _b);
    void happen();
    void takeEffect();
    void printAffair();
};
class NastyMeals : public Affair
{
public:
    NastyMeals(int _idx, double _p, Building* _b);
    void happen();
    void takeEffect();
    void printAffair();
};
class LuxuriousIsolationConditions : public Affair
{
public:
    LuxuriousIsolationConditions(int _idx, double _p, Building* _b);
    void happen();
    void takeEffect();
    void printAffair();
};
class InterestingQuarantineLife : public Affair
{
public:
    InterestingQuarantineLife(int _idx, double _p, Building* _b);
    void happen();
    void takeEffect();
    void printAffair();
};
class BrokenWashingMachine : public Affair
{
public:
    BrokenWashingMachine(int _idx, double _p, Building* _b);
    void happen();
    void takeEffect();
    void printAffair();
};
class BrokenAirConditioner : public Affair
{
public:
    BrokenAirConditioner(int _idx, double _p, Building* _b);
    void happen();
    void takeEffect();
    void printAffair();
};
class BrokenWaterHeater : public Affair
{
public:
    BrokenWaterHeater(int _idx, double _p, Building* _b);
    void happen();
    void takeEffect();
    void printAffair();
};
class Gathering : public Affair
{
public:
    Gathering(int _idx, double _p, Building* _b);
    void happen();
    void takeEffect();
    void printAffair();
};
class ProtesetInShudong : public Affair
{
public:
    ProtesetInShudong(int _idx, double _p, Building* _b);
    void happen();
    void takeEffect();
    void printAffair();
};
class SingInDormitory : public Affair
{
public:
    SingInDormitory(int _idx, double _p, Building* _b);
    void happen();
    void takeEffect();
    void printAffair();
};
class ShushuBegins : public Affair
{
public:
    ShushuBegins(int _idx, double _p, Building* _b);
    void happen();
    void takeEffect();
    void printAffair();
};
class QuarrelInDormitory : public Affair
{
public:
    QuarrelInDormitory(int _idx, double _p, Building* _b);
    void happen();
    void takeEffect();
    void printAffair();
};
class UnbearableSnoring : public Affair
{
public:
    UnbearableSnoring(int _idx, double _p, Building* _b);
    void happen();
    void takeEffect();
    void printAffair();
};
class Top10InBathroom : public Affair
{
public:
    Top10InBathroom(int _idx, double _p, Building* _b);
    void happen();
    void takeEffect();
    void printAffair();
};
class LearningInDormitory : public Affair
{
public:
    LearningInDormitory(int _idx, double _p, Building* _b);
    void happen();
    void takeEffect();
    void printAffair();
};
class MahjongInDormitory : public Affair
{
public:
    MahjongInDormitory(int _idx, double _p, Building* _b);
    void happen();
    void takeEffect();
    void printAffair();
};
class HarmoniousDormitory : public Affair
{
public:
    HarmoniousDormitory(int _idx, double _p, Building* _b);
    void happen();
    void takeEffect();
    void printAffair();
};
class HealthySleeping : public Affair
{
public:
    HealthySleeping(int _idx, double _p, Building* _b);
    void happen();
    void takeEffect();
    void printAffair();
};
class BrokenOutPersonnel : public Affair
{
public:
    BrokenOutPersonnel(int _idx, double _p, Building* _b);
    void happen();
    void takeEffect();
    void printAffair();
};
class VolunteerLack : public Affair
{
public:
    VolunteerLack(int _idx, double _p, Building* _b);
    void happen();
    void takeEffect();
    void printAffair();
};
class LackOfMedicalResources : public Affair
{
public:
    LackOfMedicalResources(int _idx, double _p, Building* _b);
    void happen();
    void takeEffect();
    void printAffair();
};
class GreatPrevention : public Affair
{
public:
    GreatPrevention(int _idx, double _p, Building* _b);
    void happen();
    void takeEffect();
    void printAffair();
};
class Detention : public Affair
{
public:
    Detention(int _idx, double _p, Building* _b);
    void happen();
    void takeEffect();
    void printAffair();
};
class Top10 : public Affair
{
public:
    Top10(int _idx, double _p, Building* _b);
    void happen();
    void takeEffect();
    void printAffair();
};
class BrokenHeater : public Affair
{
public:
    BrokenHeater(int _idx, double _p, Building* _b);
    void happen();
    void takeEffect();
    void printAffair();
};
