/*
1.game里面加入了一个win的指针指向主窗口，主要要用的接口函数是a_text()，这个函数可以在主界面的日志栏里面输出一行文字，用法如下：
win->a_text(QString::fromUtf8( "字符串写在这里，注意使用uft-8编码"));

还有void e_happen(int idx),这个函数用于表现突发事件，idx是时间编号，具体显示内容在event_.cpp里面修改，目前只添加了事件id是0\1的事件

2.目前游戏缺少bgm，如果要填充音乐的话，可以填充上几首，亟待推荐

3.游戏预计还会做两段演出放在游戏末尾，分别做失败动画和成功动画（如果有什么对于脚本/文案的建议那再好不过了）

4.游戏界面读取隔离人数利用int Game::getquarantine()直接读取了隔离人数，因此修改隔离人数会在界面上直接显示

5.学生满意度的结算目前似乎有一些bug

6.关于政策，我直接使用了建筑的policy，其中取building*=NULL，idx从10开始取(但是加入all——policy时还是从0开始加入的)，依次是

    10 全员核酸(我把这个政策做出来了，在class.cpp底下有）
    11 科研专项
    12 接种疫苗
    13 推迟开学
    14 视频会议
    15 线上十佳
    16 线上军训
    17 防控宣讲
    18 线上毕业
    19 线上开学
    20 线上晚会
    21 开始网课
    22 pf制
    23 口罩令
    24 管控舆论
    25 接收树洞
    26 志愿者
    27 暂停参观
    28 开始流调
    29 常态核酸
    30 场所码

7.game中新增了一项total_infection_likelyhood,影响总体传播速度，受到学生满意度（抵抗力）以及政策（例如全员核酸小幅增加感染概率）的影响

8.我还添加了编号为2的事件“第一次核酸检测”，因为这个事件只显示，没有任何实际做用，所以没有新增一个类，但要注意添加新的事件时idx要从3开始
*/

#define _CRT_SECURE_NO_WARNINGS
#include<time.h>
#include<iostream>
#include<cstring>
#include<iomanip>
#include<cmath>
#include<list>
#include<random>
#include"class.h"
using namespace std;

random_device seed;
ranlux48 engine(seed());


//Game �� | ����Ϸ ��
Game::Game() {
    time_t now_time;
    time(&now_time);//��ȡ��1900��1��1��0��0�뵽���ھ���������
    tm* p = localtime(&now_time);//������ת��Ϊ����ʱ�䣬���1900������Ҫ+1900����Ϊ0~11������Ҫ+1
    year = p->tm_year + 1900;//��ʼ����Ϊ��ʵ��ǰ���
    month = p->tm_mon + 1;//��ʼ����Ϊ��ʵ��ǰ��
    yam=to_string(year)+"年 "+to_string(month)+"月";
    day = p->tm_mday;//��ʼ����Ϊ��ʵ��ǰ��
    hour = 0;//��ʼ��СʱΪ0ʱ
    overall_satisfaction = 90;//��ʼ�������Ϊ0
    activity_point = 0;//��ʼ���ж���Ϊ0
    sum_healthy_person = 40000;
    sum_ill_person = 0;
    sum_quarantine_person = 0;
    sum_building = 71;
    //��ʼ��all_building
    /*
    kind:
    0 ѧ������
    1 ʳ��
    2 ��ѧ¥
    3 ͼ���
    4 УҽԺ
    5 �ٳ�
    6 ������
    7 δ����
    8 ʵ��¥
    9 ѧУУ��
    code:
    0~44    45������(0~44)
    45~50  ʳ��
    45 ũ԰
    46 ��԰
    47 ��԰
    48 ��԰
    49 ѧһ
    50 ѧ��
    51~57  ��ѧ¥
    51 һ��
    52 ����
    53 ����
    54 �Ľ�
    55 ����
    56 ��ʷ
    57 ��ѧ
    58 ͼ���
    59 УҽԺ
    60 ���Ĳٳ�
    61 ����������
    62 ��԰�������
    63 δ����
    64 ����ʵ��¥
    65 ����
    66 ����
    67 ����
    68 ������
    69 ������
    70 ������
    */
    for (int i = 0; i < sum_building; i++) {
        if (i <= 44) {
            all_building[i] = new Dormitory(0, i, this);
            all_building[i]->setInitialPolicy(); // ���ó�ʼ����
        }
        if (i >= 45 && i <= 50) {
            all_building[i] = new DiningHall(1, i, this);
            all_building[i]->setInitialPolicy(); // ���ó�ʼ����
        }
        if (i >= 51 && i <= 57) {
            all_building[i] = new TeachingBuilding(2, i, this);
            all_building[i]->setInitialPolicy(); // ���ó�ʼ����
        }
        if (i == 58) {
            all_building[i] = new Library(3, i, this);
            all_building[i]->setInitialPolicy(); // ���ó�ʼ����
        }
        if (i == 59) {
            all_building[i] = new Hospital(4, i, this);
            all_building[i]->setInitialPolicy(); // ���ó�ʼ����
        }
        if (i == 60) {
            all_building[i] = new Playground(5, i, this);
            all_building[i]->setInitialPolicy(); // ���ó�ʼ����
        }
        if (i >= 61 && i <= 62) {
            all_building[i] = new Gymnasium(6, i, this);
            all_building[i]->setInitialPolicy(); // ���ó�ʼ����
        }
        if (i == 63) {
            all_building[i] = new Lake(7, i, this);
            all_building[i]->setInitialPolicy(); // ���ó�ʼ����
        }
        if (i == 64) {
            all_building[i] = new Laboratory(8, i, this);
            all_building[i]->setInitialPolicy(); // ���ó�ʼ����
        }
        if (i >= 65 && i <= 70) {
            all_building[i] = new Gate(9, i, this);
            all_building[i]->setInitialPolicy(); // ���ó�ʼ����
        }
    }
    //��ʼ��all_person
    for (int i = 0; i < 40000; i++) {
        all_person[i] = new Person();
        double P;
        //0~6�㣬100%������˯��
        uniform_int_distribution<> int_distrib(0, 44);
        int temp_dormitory = int_distrib(engine);
        for (int j = 0; j <= 6; j++) {
            all_person[i]->track[j] = temp_dormitory;
        }
        //7�㣬50%ȥ���緹��50%�������
        uniform_int_distribution<> int_distrib1(45, 50);
        int temp_morning_dininghall = int_distrib1(engine);
        uniform_real_distribution<> real_distrib(0, 1);
        P = real_distrib(engine);
        if (P >= 0.5) { all_person[i]->track[7] = temp_morning_dininghall; }
        else { all_person[i]->track[7] = temp_dormitory; }
        //8~9�㣬40%��ѧ¥�ϿΣ�30%���ᣬ20%ͼ��ݣ�10%δ����
        uniform_int_distribution<> int_distrib2(51, 57);
        int temp_teachingbuilding1 = int_distrib2(engine);
        uniform_real_distribution<> real_distrib1(0, 1);
        P = real_distrib1(engine);
        for (int j = 8; j <= 9; j++) {
            if (0 <= P && P < 0.4) { all_person[i]->track[j] = temp_teachingbuilding1; }
            else if (0.4 <= P && P < 0.7) { all_person[i]->track[j] = temp_dormitory; }
            else if (0.7 <= P && P < 0.9) { all_person[i]->track[j] = 58; }//ͼ���
            else if (0.9 <= P && P <= 1.0) { all_person[i]->track[j] = 63; }//δ����
        }
        //10~11�㣬40%��ѧ¥�ϿΣ�20%���ᣬ15%ͼ��ݣ�10%ʳ�ã�10%δ������5%������
        uniform_int_distribution<> int_distrib3(51, 57);
        int temp_teachingbuilding2 = int_distrib3(engine);
        uniform_int_distribution<> int_distrib4(45, 50);
        int temp_lunchbuilding1 = int_distrib4(engine);
        uniform_int_distribution<> int_distrib5(61, 62);
        int temp_gymnasium1 = int_distrib5(engine);
        uniform_real_distribution<> real_distrib2(0, 1);
        P = real_distrib2(engine);
        for (int j = 10; j <= 11; j++) {
            if (0 <= P && P < 0.4) { all_person[i]->track[j] = temp_teachingbuilding2; }
            else if (0.4 <= P && P < 0.6) { all_person[i]->track[j] = temp_dormitory; }
            else if (0.6 <= P && P < 0.75) { all_person[i]->track[j] = 58; }//ͼ���
            else if (0.75 <= P && P < 0.85) { all_person[i]->track[j] = temp_lunchbuilding1; }
            else if (0.85 <= P && P < 0.95) { all_person[i]->track[j] = 63; }//δ����
            else if (0.95 <= P && P <= 1.0) { all_person[i]->track[j] = temp_gymnasium1; }
        }
        //12�㣬40%ʳ���緹��15%��ѧ¥��20%���ᣬ10%ͼ��ݣ�12%δ������3%������
        uniform_int_distribution<> int_distrib6(45, 50);
        int temp_lunchbuilding2 = int_distrib6(engine);
        uniform_int_distribution<> int_distrib7(51, 57);
        int temp_teachingbuilding3 = int_distrib7(engine);
        uniform_int_distribution<> int_distrib8(61, 62);
        int temp_gymnasium2 = int_distrib8(engine);
        uniform_real_distribution<> real_distrib3(0, 1);
        P = real_distrib3(engine);
        if (0 <= P && P < 0.4) { all_person[i]->track[12] = temp_lunchbuilding2; }
        else if (0.4 <= P && P < 0.55) { all_person[i]->track[12] = temp_teachingbuilding3; }
        else if (0.55 <= P && P < 0.75) { all_person[i]->track[12] = temp_dormitory; }
        else if (0.75 <= P && P < 0.85) { all_person[i]->track[12] = 58; }//ͼ���
        else if (0.85 <= P && P < 0.97) { all_person[i]->track[12] = 63; }//δ����
        else if (0.97 <= P && P <= 1.0) { all_person[i]->track[12] = temp_gymnasium2; }
        //13~14�㣬40%��ѧ¥��20%ͼ��ݣ�20%���ᣬ10%ʳ�ã�5%δ������3%�����ݣ�2%�ٳ�
        uniform_int_distribution<> int_distrib9(51, 57);
        int temp_teachingbuilding4 = int_distrib9(engine);
        uniform_int_distribution<> int_distrib10(45, 50);
        int temp_lunchbuilding3 = int_distrib10(engine);
        uniform_int_distribution<> int_distrib11(61, 62);
        int temp_gymnasium3 = int_distrib11(engine);
        uniform_real_distribution<> real_distrib4(0, 1);
        P = real_distrib4(engine);
        for (int j = 13; j <= 14; j++) {
            if (0 <= P && P < 0.4) { all_person[i]->track[j] = temp_teachingbuilding4; }
            else if (0.4 <= P && P < 0.6) { all_person[i]->track[j] = 58; }//ͼ���
            else if (0.6 <= P && P < 0.8) { all_person[i]->track[j] = temp_dormitory; }
            else if (0.8 <= P && P < 0.9) { all_person[i]->track[j] = temp_lunchbuilding3; }
            else if (0.9 <= P && P < 0.95) { all_person[i]->track[j] = 63; }//δ����
            else if (0.95 <= P && P < 0.98) { all_person[i]->track[j] = temp_gymnasium3; }
            else if (0.98 <= P && P <= 1.0) { all_person[i]->track[j] = 60; }//�ٳ�
        }
        //15~16�㣬40%��ѧ¥��20%ͼ��ݣ�20%���ᣬ10%ʳ�ã�5%δ������3%�����ݣ�2%�ٳ�
        uniform_int_distribution<> int_distrib12(51, 57);
        int temp_teachingbuilding5 = int_distrib12(engine);
        uniform_int_distribution<> int_distrib13(45, 50);
        int temp_lunchbuilding4 = int_distrib13(engine);
        uniform_int_distribution<> int_distrib14(61, 62);
        int temp_gymnasium4 = int_distrib14(engine);
        uniform_real_distribution<> real_distrib5(0, 1);
        P = real_distrib5(engine);
        for (int j = 15; j <= 16; j++) {
            if (0 <= P && P < 0.4) { all_person[i]->track[j] = temp_teachingbuilding5; }
            else if (0.4 <= P && P < 0.6) { all_person[i]->track[j] = 58; }//ͼ���
            else if (0.6 <= P && P < 0.8) { all_person[i]->track[j] = temp_dormitory; }
            else if (0.8 <= P && P < 0.9) { all_person[i]->track[j] = temp_lunchbuilding4; }
            else if (0.9 <= P && P < 0.95) { all_person[i]->track[j] = 63; }//δ����
            else if (0.95 <= P && P < 0.98) { all_person[i]->track[j] = temp_gymnasium4; }
            else if (0.98 <= P && P <= 1.0) { all_person[i]->track[j] = 60; }//�ٳ�
        }
        //17�㣬45%ʳ��������15%��ѧ¥��15%ͼ��ݣ�15%���ᣬ5%�ٳ���3%δ������2%������
        uniform_int_distribution<> int_distrib15(51, 57);
        int temp_teachingbuilding6 = int_distrib15(engine);
        uniform_int_distribution<> int_distrib16(45, 50);
        int temp_supperbuilding1 = int_distrib16(engine);
        uniform_int_distribution<> int_distrib17(61, 62);
        int temp_gymnasium5 = int_distrib17(engine);
        uniform_real_distribution<> real_distrib6(0, 1);
        P = real_distrib6(engine);
        if (0 <= P && P < 0.45) { all_person[i]->track[17] = temp_supperbuilding1; }
        else if (0.45 <= P && P < 0.6) { all_person[i]->track[17] = temp_teachingbuilding6; }
        else if (0.6 <= P && P < 0.75) { all_person[i]->track[17] = 58; }//ͼ���
        else if (0.75 <= P && P < 0.9) { all_person[i]->track[17] = temp_dormitory; }
        else if (0.9 <= P && P < 0.95) { all_person[i]->track[17] = 60; }//�ٳ�
        else if (0.95 <= P && P < 0.98) { all_person[i]->track[17] = 63; }//δ����
        else if (0.98 <= P && P <= 1.0) { all_person[i]->track[17] = temp_gymnasium5; }
        //18�㣬30%ʳ��������20%��ѧ¥��20%ͼ��ݣ�15%���ᣬ5%�ٳ���5%δ������5%������
        uniform_int_distribution<> int_distrib18(51, 57);
        int temp_teachingbuilding7 = int_distrib18(engine);
        uniform_int_distribution<> int_distrib19(45, 50);
        int temp_supperbuilding2 = int_distrib19(engine);
        uniform_int_distribution<> int_distrib20(61, 62);
        int temp_gymnasium6 = int_distrib20(engine);
        uniform_real_distribution<> real_distrib7(0, 1);
        P = real_distrib7(engine);
        if (0 <= P && P < 0.3) { all_person[i]->track[18] = temp_supperbuilding2; }
        else if (0.3 <= P && P < 0.5) { all_person[i]->track[18] = temp_teachingbuilding7; }
        else if (0.5 <= P && P < 0.7) { all_person[i]->track[18] = 58; }//ͼ���
        else if (0.7 <= P && P < 0.85) { all_person[i]->track[18] = temp_dormitory; }
        else if (0.85 <= P && P < 0.9) { all_person[i]->track[18] = 60; }//�ٳ�
        else if (0.9 <= P && P < 0.95) { all_person[i]->track[18] = 63; }//δ����
        else if (0.95 <= P && P <= 1.0) { all_person[i]->track[18] = temp_gymnasium6; }
        //19~20�㣬40%��ѧ¥��20%ͼ��ݣ�20%���ᣬ6%�ٳ���7%δ������7%������
        uniform_int_distribution<> int_distrib21(51, 57);
        int temp_teachingbuilding8 = int_distrib21(engine);
        uniform_int_distribution<> int_distrib22(61, 62);
        int temp_gymnasium7 = int_distrib22(engine);
        uniform_real_distribution<> real_distrib8(0, 1);
        P = real_distrib8(engine);
        for (int j = 19; j <= 20; j++) {
            if (0 <= P && P < 0.4) { all_person[i]->track[j] = temp_teachingbuilding8; }
            else if (0.4 <= P && P < 0.6) { all_person[i]->track[j] = 58; }//ͼ���
            else if (0.6 <= P && P < 0.8) { all_person[i]->track[j] = temp_dormitory; }
            else if (0.8 <= P && P < 0.86) { all_person[i]->track[j] = 60; }//�ٳ�
            else if (0.86 <= P && P < 0.93) { all_person[i]->track[j] = 63; }//δ����
            else if (0.93 <= P && P <= 1.0) { all_person[i]->track[j] = temp_gymnasium7; }
        }
        //21�㣬20%��ѧ¥��40%���ᣬ8%�ٳ���8%δ������9%�����ݣ�15%ͼ���
        uniform_int_distribution<> int_distrib23(51, 57);
        int temp_teachingbuilding9 = int_distrib23(engine);
        uniform_int_distribution<> int_distrib24(61, 62);
        int temp_gymnasium8 = int_distrib24(engine);
        uniform_real_distribution<> real_distrib9(0, 1);
        P = real_distrib9(engine);
        if (0 <= P && P < 0.2) { all_person[i]->track[21] = temp_teachingbuilding9; }
        else if (0.2 <= P && P < 0.6) { all_person[i]->track[21] = temp_dormitory; }
        else if (0.6 <= P && P < 0.68) { all_person[i]->track[21] = 60; }//�ٳ�
        else if (0.68 <= P && P < 0.76) { all_person[i]->track[21] = 63; }//δ����
        else if (0.76 <= P && P < 0.85) { all_person[i]->track[21] = temp_gymnasium8; }
        else if (0.85 <= P && P <= 1.0) { all_person[i]->track[21] = 58; }//ͼ���
        //22�㣬10%δ������7%�����ݣ�50%���ᣬ15%ͼ��ݣ�10%��ѧ¥��8%�ٳ�
        uniform_int_distribution<> int_distrib25(51, 57);
        int temp_teachingbuilding10 = int_distrib25(engine);
        uniform_int_distribution<> int_distrib26(61, 62);
        int temp_gymnasium9 = int_distrib26(engine);
        uniform_real_distribution<> real_distrib10(0, 1);
        P = real_distrib10(engine);
        if (0 <= P && P < 0.1) { all_person[i]->track[22] = 63; }//δ����
        else if (0.1 <= P && P < 0.17) { all_person[i]->track[22] = temp_gymnasium9; }
        else if (0.17 <= P && P < 0.67) { all_person[i]->track[22] = temp_dormitory; }
        else if (0.67 <= P && P < 0.82) { all_person[i]->track[22] = 58; }//ͼ���
        else if (0.82 <= P && P < 0.92) { all_person[i]->track[22] = temp_teachingbuilding10; }
        else if (0.92 <= P && P <= 1.0) { all_person[i]->track[22] = 60; }//�ٳ�
        //23�㣬95%���ᣬ5%δ����
        uniform_real_distribution<> real_distrib11(0, 1);
        P = real_distrib11(engine);
        if (0 <= P && P < 0.95) { all_person[i]->track[23] = temp_dormitory; }
        else if (0.95 <= P && P <= 1.0) { all_person[i]->track[23] = 63; }//δ����
    }

    //All policys
    all_policy[0]=new Do_pcr(10,10,this);
    all_policy[1]=new ResearchOnVirus(11,500,this,NULL);
    all_policy[2]=new SuspendCampusTour(12,100,this,NULL);
    all_policy[3]=new PostponeStartOfSchool(13,200,this,NULL);
    all_policy[4]=new ProvideDesktopVideo(14,300,this,NULL);
    all_policy[5]=new StartOnlineCourse(15,300,this,NULL);
    all_policy[6]=new StartPF(16,50,this,NULL);
}

int Game::getdate()
{
    return day;
}
int Game::getap()
{
    return activity_point;
}
int Game::getsat()
{
    return overall_satisfaction;
}
int Game::getill()
{
    return sum_ill_person;
}
void Game::pcr()
{
    ifpcr=true;
}
bool Game::getpcr_state()
{
    return ifpcr;
}
void Game::startResearchOnVirus() {
    ifResearchOnVirusStart = true;
}
bool Game::getResearchOnVirus_state() {
    return ifResearchOnVirusStart;
}
void Game::suspendCampusTour() {
    campusTour_state = true;
}
bool Game::getCampusTour_state() {
    return campusTour_state;
}
void Game::postponeStartOfSchool() {
    postponeStartOfSchool_state = true;
}
bool Game::getPostponeStartOfschool_state() {
    return postponeStartOfSchool_state;
}
void Game::provideDesktopVideo() {
    provideDesktopVideo_state = true;
}
bool Game::getProvideDesktopVideo() {
    return provideDesktopVideo_state;
}
void Game::startOnlineCourse() {
    onlineCourse_state = true;
}
bool Game::getOnlineCourse_state() {
    return onlineCourse_state;
}
void Game::startPF() {
    PF_state = true;
}
bool Game::getPF_state() {
    return PF_state;
}

Building* Game::getBuilding(int building_id) {
    return all_building[building_id];
}
bool Game::cost_ap(int t){
    if(activity_point<t) return false;
    else
    {
        activity_point-=t;
        win->showap();
        return true;
    }
}
void Game::gameRun() {
    //���Ƚ��л������ݵĳ�ʼ��
    activity_point = 0;//��ʼ���ж���
    overall_satisfaction = 90;//��ʼ���������

    //��ʼ��all_policy
    uniform_int_distribution<> fucking(0, 40000);
    int intitial_infected_idx = fucking(engine);
    all_person[intitial_infected_idx]->health_state = 1;
    sum_healthy_person--;
    sum_ill_person++;
}
/*    while (!gameEnd()) {
        yam=to_string(year)+"年 "+to_string(month)+"月";
        //printf("%d��%d��%d��\n", year, month, day);
        cout << "�ܽ���������" << sum_healthy_person << ' ' << "�ܸ�Ⱦ������" << sum_ill_person << ' ' << "�ܸ���������" << sum_quarantine_person << endl;
        //printf("��ǰѧ�������:%.2lf\n", overall_satisfaction);
        //printf("��ǰ�����ж�����%d\n", activity_point);
        //system("pause");
        win->showitems();

        cout << "����������£�" << endl;
        for (int building_index = 0; building_index < sum_building; building_index++) {
            cout << "building_index��" << building_index << endl;
            printf("��ǰbuilding��level�ǣ�%d\n", all_building[building_index]->getLevel());
            for (int policy_index = 0; policy_index < all_building[building_index]->total_number_of_available; policy_index++) {
                cout << "policy_index��" << setw(3) << policy_index << ' ';
                switch (all_building[building_index]->policy_state[policy_index]) {
                case 0:
                    cout << "�����ã�";
                    break;
                case 1:
                    cout << "  ���ã�";
                    break;
                case 2:
                    cout << "�Ѱ䲼��";
                    break;
                }
                // ����д������������
                all_building[building_index]->available_policy[policy_index]->printPolicy();
            }
            // ��ʼ��������¼�
            all_building[building_index]->checkAffairHappen();
        }
        // ����ط���qt��ʹ�õ���ķ�ʽ��
        printf("������1��ʾҪ��ʼѡ��������������\n");
        int opt;
        cin >> opt;
        if (opt == 1) {
            printf("�����ı�ŷ�Χ��0~70��������һ�����ѡ��Ŷ�����벻�������Χ����Ϊ����������Ŷ��\n");
            int temp_idx;
            while (cin >> temp_idx) {
                if (temp_idx < 0 || temp_idx > 70)
                    break;
                if (activity_point < all_building[temp_idx]->upgrade_cost[all_building[temp_idx]->level]) {
                    printf("���е��ж����޷�������ǰ����Ŷ\n");
                }
                else if (all_building[temp_idx]->level == 3) {
                    printf("��ǰ�Ľ����Ѿ�������\n");
                }
                else {
                    activity_point -= all_building[temp_idx]->upgrade_cost[all_building[temp_idx]->level];
                    all_building[temp_idx]->upgrade();
                }
            }
            printf("�������������Ѿ������ˣ�\n");
        }
        // ����дѡ�������߽��������Ķ���
        // ����ѡ�����ߺ��п��ܻᵼ�½������رգ�Ҫ�����µĹ켣�G
        is_building_shut_down = false;
        printf("������1����������������\n");
        cin >> opt;
        if (opt == 1) {
            printf("�������뽨����ı�ţ�ѡ��һ�������������ı��Ϊ0-70\n");
            int building_idx;
            while (cin >> building_idx) {
                if (building_idx < 0 || building_idx > 70)
                    break;
                printf("��������������������������ѡ��һ������ʵ�У�\n");
                for (int policy_idx = 0; policy_idx < all_building[building_idx]->total_number_of_available; policy_idx++) {
                    cout << "policy_index��" << setw(3) << policy_idx << ' ';
                    switch (all_building[building_idx]->policy_state[policy_idx]) {
                    case 0:
                        cout << "�����ã�";
                        break;
                    case 1:
                        cout << "  ���ã�";
                        break;
                    case 2:
                        cout << "�Ѱ䲼��";
                        break;
                    }
                    all_building[building_idx]->available_policy[policy_idx]->printPolicy();
                }
                int policy_idx;
                printf("������������Ҫѡ�õ����߱�ţ�����������Χ����Ϊ�˳���\n");
                while (cin >> policy_idx) {
                    if (policy_idx >= all_building[building_idx]->total_number_of_available || policy_idx < 0) {
                        break;
                    }
                    else if (all_building[building_idx]->policy_state[policy_idx] == 0) {
                        printf("��ǰ���߻�������Ŷ\n");
                    }
                    else if (all_building[building_idx]->policy_state[policy_idx] == 2) {
                        printf("��ǰ�����Ѿ��䲼��\n");
                    }
                    else {
                        if (activity_point < all_building[building_idx]->available_policy[policy_idx]->cost) {
                            printf("����ǰ�ĵ���������\n");
                        }
                        else {
                            activity_point -= all_building[building_idx]->available_policy[policy_idx]->cost;
                            all_building[building_idx]->enactPolcy(policy_idx);
                            if (all_building[building_idx]->isShutDown())
                                is_building_shut_down = true;
                        }
                    }
                }
            }
        }
        printf("ѡ��䲼���ߵĻ����Ѿ�������\n");
*/

int Game::start_newday()
{
        if (is_building_shut_down)
            updateTrack(); // ����н������رգ�ѡ�����ѧ���Ĺ켣��������ѧ���޷��ٽ�����������ˣ�����Ҫ�����������ٳ�ȥ��

        if (ifResearchOnVirusStart) {
            if (ifResearchOnVirusDone) {
                //遍历所有人，治愈1000个人，病人不足1000个则全部治愈
                int cnt = 0;
                for (int i = 0; i < sum_healthy_person + sum_ill_person + sum_quarantine_person; i++) {
                    if (all_person[i]->health_state == 1) {
                        all_person[i]->health_state = 0;
                        sum_healthy_person++;
                        sum_ill_person--;
                        cnt++;
                    }
                    if (cnt == 1000) { break; }
                }
            }
            else {
                researchOnVirusSchedule-=2;
                if (researchOnVirusSchedule == 0) {
                    ifResearchOnVirusDone = true;
                    win->a_text(QString::fromUtf8( "科研专项已经完成，我们终将要战胜病毒！即日起患者康复率大幅提升"));
                }
            }
        }

        startSpread();
        startQuarantine();
        updateAllSatisfaction();
        //cout << "总健康人数：" << sum_healthy_person << ' ' << "总感染人数：" << sum_ill_person << ' ' << "总隔离人数：" << sum_quarantine_person << endl;
        int temp_satisfaction = 0;
        int temp_total_person = 0;
        for (int i = 0; i < sum_healthy_person + sum_ill_person + sum_quarantine_person; i++) {
            temp_satisfaction += all_person[i]->satisfaction;
            temp_total_person++;
        }
        overall_satisfaction = temp_satisfaction * 1.0 / temp_total_person;
        total_infection_likelyhood=0.00005*(100-overall_satisfaction);//满意度改变全局感染概率
        for (int i = 0; i < sum_building; i++) {
            activity_point += all_building[i]->produceActionPoint();
        }
        nextDay();
        yam=to_string(year)+"年 "+to_string(month)+"月";
        ifpcr=false;
        qDebug()<<sum_quarantine_person;
        win->showitems();
        for (int building_index = 0; building_index < sum_building; building_index++)
            all_building[building_index]->checkAffairHappen();
        if(gameLose()) return -1;
        else if(gameWin()) return 1;
        else return 0;
}
void Game::save(int i)//用于实现存档功能，把所有游戏有关参数全部写入i号文件中并保存（i>=0&&i<=2)
{
    QFile file(QString::fromUtf8("save"+to_string(i)+".txt"));
    //如果i号文件已经存在，则删除
    if(file.exists())
    {
        file.remove();
    }
    qDebug()<<"A";
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    time_t now;
    time(&now);
    tm* tep = localtime(&now);
    out<<tep->tm_year + 1900<<'\n';//��ʼ����Ϊ��ʵ��ǰ���
    out<<tep->tm_mon + 1<<'\n';//��ʼ����Ϊ��ʵ��ǰ��
    out<<tep->tm_mday<<'\n';//��ʼ����Ϊ��ʵ��ǰ��
    out<<tep->tm_hour<<'\n';
    out<<tep->tm_min<<'\n';
    out<<year<<'\n';
    out<<month<<'\n';
    out<<day<<'\n';
    out<<sum_building<<'\n';
    out<<sum_healthy_person<<'\n';
    out<<sum_ill_person<<'\n';
    out<<sum_quarantine_person<<'\n';
    out<<overall_satisfaction<<'\n';
    out<<activity_point<<'\n';
    out<<total_infection_likelyhood<<'\n';
    out<<ifResearchOnVirusStart<<'\n';
    out<<ifResearchOnVirusDone<<'\n';
    out<<researchOnVirusSchedule<<'\n';
    out<<is_building_shut_down<<'\n';
    out<<ifpcr<<'\n';
    //此外还有政策相关的状态需要存储
    out<<this->campusTour_state<<'\n';
    out<<this->PF_state<<'\n';
    out<<this->provideDesktopVideo_state<<'\n';
    out<<this->onlineCourse_state<<'\n';


    qDebug()<<"B";
    //还应该存储building相关的状态以及people相关的状态和people的track
    for(int i=0;i<40000;++i)
    {
        out<<all_person[i]->health_state<<'\n';
        out<<all_person[i]->satisfaction<<'\n';
        out<<all_person[i]->quarantine_day<<'\n';
        for(int j=0;j<24;++j)
        {
            out<<all_person[i]->track[j]<<'\n';
        }
    }
    qDebug()<<"C";
    //下面存储building相关的状态
    /*    int level; // �����ﵱǰ�ĵȼ�

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
    Person* people_in_building[40000];*/
    //运行下面这个循环的时候程序崩溃了
    //可能是因为all_building[i]->people_in_building[j]中的people_in_building[j]为空指针
    //应做的修改是
    for(int i=0;i<=70;++i)
    {
        out<<all_building[i]->level<<'\n';
        for(int j=0;j<10;++j)
        {
            out<<all_building[i]->policy_state[j]<<'\n';
        }
        out<<all_building[i]->kind<<'\n';
        out<<all_building[i]->idx<<'\n';
        out<<all_building[i]->action_point_per_day<<'\n';
        out<<all_building[i]->total_number_of_available<<'\n';
        out<<all_building[i]->is_shut_down<<'\n';
        out<<all_building[i]->total_people<<'\n';
        out<<all_building[i]->total_infectd_people<<'\n';
        for(int j=0;j<3;++j)
        {
            out<<all_building[i]->upgrade_cost[j]<<'\n';
        }
        for(int j=0;j<all_building[i]->total_people;++j)
        {
            out<<all_building[i]->people_in_building[j]->health_state<<'\n';
            out<<all_building[i]->people_in_building[j]->satisfaction<<'\n';
            out<<all_building[i]->people_in_building[j]->quarantine_day<<'\n';
            for(int k=0;k<24;++k)
            {
                out<<all_building[i]->people_in_building[j]->track[k]<<'\n';
            }
        }
        out<<all_building[i]->change_in_infection_likelihood<<'\n';
    }
    qDebug()<<"D";
    //这里就结束了
    file.close();
}
void Game::load(int i)
{
    //依据存档规则反向进行读档
    QFile file(QString::fromUtf8("save"+to_string(i)+".txt"));
    if(!file.exists())
    {
        return;
    }
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    int temp;
    in>>temp;
    in>>temp;
    in>>temp;
    in>>temp;
    in>>temp;
    in>>year;
    in>>month;
    in>>day;
    in>>sum_building;
    in>>sum_healthy_person;
    in>>sum_ill_person;
    in>>sum_quarantine_person;
    in>>overall_satisfaction;
    in>>activity_point;
    in>>total_infection_likelyhood;
    int tep;
    in>>tep; ifResearchOnVirusStart=tep;
    in>>tep; ifResearchOnVirusDone=tep;
    in>>researchOnVirusSchedule;
    in>>tep; is_building_shut_down=tep;
    in>>tep; ifpcr=tep;
    //这里需要根据save补充一点内容
    in>>tep; this->campusTour_state=tep;
    in>>tep; this->PF_state=tep;
    in>>tep; this->provideDesktopVideo_state=tep;
    in>>tep; this->onlineCourse_state=tep;
    //还应该读取building相关的状态以及people相关的状态和people的track
    for(int i=0;i<40000;++i)
    {
        in>>all_person[i]->health_state;
        in>>all_person[i]->satisfaction;
        in>>all_person[i]->quarantine_day;
        for(int j=0;j<24;++j)
        {
            in>>all_person[i]->track[j];
        }
    }
    //下面读取building相关的状态
    for(int i=0;i<=70;++i)
    {
        in>>all_building[i]->level;
        for(int j=0;j<10;++j)
        {
            in>>all_building[i]->policy_state[j];
        }
        in>>all_building[i]->kind;
        in>>all_building[i]->idx;
        in>>all_building[i]->action_point_per_day;
        in>>all_building[i]->total_number_of_available;
        in>>tep;
        all_building[i]->is_shut_down=tep;
        in>>all_building[i]->total_people;
        in>>all_building[i]->total_infectd_people;
        for(int j=0;j<3;++j)
        {
            in>>all_building[i]->upgrade_cost[j];
        }
        for(int j=0;j<all_building[i]->total_people;++j)
        {
            in>>all_building[i]->people_in_building[j]->health_state;
            in>>all_building[i]->people_in_building[j]->satisfaction;
            in>>all_building[i]->people_in_building[j]->quarantine_day;
            for(int k=0;k<24;++k)
            {
                in>>all_building[i]->people_in_building[j]->track[k];
            }
        }
        in>>all_building[i]->change_in_infection_likelihood;
    }
    file.close();
}
bool Game::gameEnd() {
    if (gameWin())
        cout << "win!" << endl;
    if (gameLose())
        cout << "lose!" << endl;
    return gameWin() || gameLose();
}
bool Game::gameWin() {
    //���ܸ�Ⱦ�������㣬���ܽ���������Ϊ�㣬����Ϸʤ��
    bool ret = true;
    for (int i = 0; i < sum_healthy_person + sum_ill_person + sum_quarantine_person; i++) {
        if (all_person[i]->health_state == 1) { ret = false; }
    }
    if (sum_healthy_person == 0) { ret = false; }
    return ret;
}
bool Game::gameLose() {
    //���ܽ����������㣬����Ϸʧ��
    int ret = 0;
    for (int i = 0; i < sum_healthy_person + sum_ill_person + sum_quarantine_person; i++) {
        if (all_person[i]->health_state == 0) { ++ret; }
    }
    if(ret>=200) return false;
    return true;
}
Policy* Game::get_policy(int i)
{
    return all_policy[i];
}
void Game::startSpread() {
    // ��ʼ���е���Ĵ���
    int new_infected = 0; // ������Ⱦ�ߵ�����
    for (int h = 0; h < 24; h++) {
        // ����ö�ٵ�ǰ��ʱ���
        for (int i = 0; i < sum_healthy_person + sum_ill_person + sum_quarantine_person; i++) {
            // ��ö�����л������ƶ���ѧ��
            if (all_person[i]->health_state == 2)
                continue;
            // �����߸����˲�����ȥ������
            // ����������ѧ��Ҫȥ�Ľ������ر�����ô�죿�����������һ�£�

            all_building[all_person[i]->track[h]]->peopleArrived(1, all_person[i]); // һ��ѧ���������⽨��
            if (all_person[i]->health_state == 1)
                all_building[all_person[i]->track[h]]->infectedPeopleArrived(1); // һ������Ⱦ��ѧ���ִ��˵�ǰ�Ľ�����
        }
        for (int i = 0; i < sum_healthy_person + sum_ill_person + sum_quarantine_person; i++) {
            if (all_person[i]->health_state == 2 || all_person[i]->health_state == 1)
                continue;
            // �������ѧ���ڵ�ǰ��ʱ��ͽ������Ƿ�ᱻ��Ⱦ
            Building* this_building = all_building[all_person[i]->track[h]];
            double p = this_building->change_in_infection_likelihood+total_infection_likelyhood;
            if(ifpcr) p+=0.00003;
            int tot = this_building->getInfectedNumber();
            if (tot == 0)
                p = 0; // ��ǰ����������û�и�Ⱦ�ߣ���Ⱦ����Ϊ0
            else if (1 <= tot && tot <= 50)
                p += 0.0001; // ��ǰ������������1-50����Ⱦ�ߣ���Ⱦ����+0.0001
            else if (51 <= tot && tot <= 100)
                p += 0.0003; // ��ǰ������������51-100����Ⱦ�ߣ���Ⱦ����+0.0002
            else if (101 <= tot && tot <= 200)
                p += 0.0005; // ��ǰ������������100-200����Ⱦ�ߣ���Ⱦ����+0.0004
            else if (201 <= tot && tot <= 300)
                p += 0.0007; // ��ǰ������������200-300����Ⱦ�ߣ���Ⱦ����+0.0005
            else if (301 <= tot && tot <= 500)
                p += 0.002; // ��ǰ������������200-300����Ⱦ�ߣ���Ⱦ����+0.0005
            else if (501 <= tot && tot <= 1000)
                p += 0.005; // ��ǰ������������200-300����Ⱦ�ߣ���Ⱦ����+0.0005
            else
                p += 0.007; // ��ǰ������������300�����ϵĸ�Ⱦ�ߣ���Ⱦ����+0.0007
            uniform_real_distribution<> real_distub(0, 1);
            double rand_p = real_distub(engine);
            if (rand_p <= p) {
                all_person[i]->is_now_infected = true; // ������Ⱦ��
                sum_ill_person++;
                sum_healthy_person--;
                new_infected++;
            }
        }
        //printf("in %d o'clock, %d people was infected.\n", h, new_infected);
        for (int i = 0; i < sum_healthy_person + sum_ill_person + sum_quarantine_person; i++) {
            // ��ö�����л������ƶ���ѧ��
            if (all_person[i]->health_state == 2)
                continue;
            // �����߸����˲�����ȥ������
            all_building[all_person[i]->track[h]]->peopleArrived(-1, all_person[i]); // һ��ѧ���뿪���⽨��
            if (all_person[i]->health_state == 1)
                all_building[all_person[i]->track[h]]->infectedPeopleArrived(-1); // һ������Ⱦ��ѧ���뿪�˵�ǰ�Ľ�����
            if (all_person[i]->is_now_infected) {
                all_person[i]->health_state = 1; // ���Ѿ�����Ⱦ
                all_person[i]->is_now_infected = false;
            }
        }
    }
        if(ifpcr)
        {
            win->a_text(QString::fromUtf8( "昨日新增")+QString::fromUtf8(to_string(new_infected))+QString::fromUtf8("人感染"));
        }

}

void Game::startQuarantine() {
    // 开始进行隔离
    double p = 0.01;
    if(ifpcr)
        p+=0.04;
    if(ifResearchOnVirusDone)
        p+=0.1;
    int cnt=0,cnt1=0;
    // 不必修改被隔离的人的轨迹，因为在开始传播里面会直接避免他们乱奔跑
    for (int i = 0; i < sum_healthy_person + sum_ill_person + sum_quarantine_person; i++) {
        if (ifResearchOnVirusDone&&all_person[i]->health_state == 2) {
            all_person[i]->quarantine_day++;
            if (all_person[i]->quarantine_day >= 14) {
                all_person[i]->health_state = 0;
                sum_quarantine_person--;
                sum_healthy_person++;
                cnt1++;
            }
            continue;
        }
        if (all_person[i]->health_state == 0||all_person[i]->health_state == 2)
            continue;
        uniform_real_distribution<> real_distub(0, 1);
        double rand_p = real_distub(engine);
        if (rand_p <= p) {
            all_person[i]->health_state = 2;
            sum_quarantine_person++;
            sum_ill_person--;
            cnt++;
        }
    }
    if(cnt!=0&&cnt1!=0)
    win->a_text(QString::fromUtf8( "昨日有")+QString::fromUtf8(to_string(cnt))+QString::fromUtf8("名感染者被隔离")
                +QString::fromUtf8( "  有")+QString::fromUtf8(to_string(cnt1))+QString::fromUtf8("名隔离患者康复"));
    else if(cnt!=0&&cnt1==0)
    win->a_text(QString::fromUtf8( "昨日有")+QString::fromUtf8(to_string(cnt))+QString::fromUtf8("名感染者被隔离"));
}
void Game::updateAllSatisfaction() {
    // 如果被感染了，每天满意度掉0.5
    // 如果被隔离了，每天满意度再掉0.4
    // 如果康复了，每天满意度0.5
    for (int i = 0; i < sum_healthy_person + sum_ill_person + sum_quarantine_person; i++) {
        if (all_person[i]->health_state == 1) {
            all_person[i]->satisfaction -= 0.5;
        }
        else if (all_person[i]->health_state == 2) {
            all_person[i]->satisfaction -= 0.9;
        }
        else {
            all_person[i]->satisfaction += 0.5;
        }
    }
}
void Game::nextDay() {
    // �ѵ�ǰ����������һ��
    int this_month_days = 30;
    if (month == 4 || month == 6 || month == 9 || month == 1)
        this_month_days = 30;
    else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
        this_month_days = 31;
    else {
        // ��ǰ�Ƕ���
        if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0))
            this_month_days = 29;
        else
            this_month_days = 28;
    }

    day++;
    if (day >= this_month_days) {
        day = 1;
        month++;
        if (month >= 12) {
            month = 1;
            year++;
        }
    }
}
void Game::updateTrack() {
    for (int i = 0; i < sum_healthy_person + sum_ill_person + sum_quarantine_person; i++) {
        int before_idx = all_person[i]->track[0]; // ��ǰ�ڵĽ�����ı��
        for (int h = 0; h < 24; h++) {
            if (all_building[all_person[i]->track[h]]->isDormitoryShutDown()) {
                // ����һ�����е��г̶���Ϊ�����ᣬ�����˳�ѭ��
                int idx = all_person[i]->track[h];
                for (int h_hat = 0; h_hat < 24; h_hat++) {
                    all_person[i]->track[h_hat] = idx;
                }
                break;
            }
            else if (all_building[all_person[i]->track[h]]->isShutDown()) {
                all_person[i]->track[h] = before_idx; // �����Ҫȥ�Ľ����ﱻ�ر��ˣ���ô���ȴ���ԭ���Ľ����ﵱ��
            }
            else {
                // ���Ҫȥ�Ľ�����û�б��ر�
                before_idx = all_person[i]->track[h];
            }
        }
    }
}
int Game::getquarantine()
{
    return sum_quarantine_person;
}
int Game::getSeason() {
    if (month == 3 || month == 4 || month == 5)
        return 1;
    else if (month == 6 || month == 7 || month == 8)
        return 2;
    else if (month == 9 || month == 10 || month == 11)
        return 3;
    else
        return 4;
}

//Person �� | �� ��
Person::Person() {
    satisfaction = 90;
    health_state = 0;
    quarantine_day = 0;
    is_now_infected = false;
    memset(track, -1, sizeof(track));
}
void Person::updateSatisfaction(double delta) {
    satisfaction += delta;
}
double Person::getSatisfaction() {
    return satisfaction;
}
Building::Building(int _kind, int _idx, Game* _g) :g(_g)
{
    total_number_of_available = 0;
    memset(policy_state, 0, sizeof(policy_state)); // һ��ʼȫ���ǲ����õ�����
    level = 1; // ��ʼ���еĽ�������1��
    kind = _kind;
    idx = _idx;
    // �װ嶨Ϊ�Դ�Ⱦ������Ӱ��
    change_in_infection_likelihood = 0;
    // һ��ʼÿ����������2��
    action_point_per_day = 0;

    // ��������Ϊ10,20
    upgrade_cost[1] = 10;
    upgrade_cost[2] = 20;

    // �Ƿ񱻹ر�
    is_shut_down = false;
    // һ��ʼ����������û����
    total_people = 0;
    // һ��ʼ����������û�и�Ⱦ��
    total_infectd_people = 0;
}
void Building::upgrade() {
    // ��������
    level++;
    // �����п��õ��������¸�ֵ
    for (int i = 0; i < total_number_of_available; i++) {
        if (policy_state[i] == 0 && available_policy[i]->available())
            policy_state[i] = 1;
    }
    if(kind==0)
        updateActionPoint(2); // ������֮���ж���ҲҪ��
    updateChange(-0.00003);
    //printf("��ǰ�Ľ����������ˣ���%d->%d\n", level-1, level);
}
void Building::enactPolcy(int policy_idx) {
    // ��������Ϸ��Ҫ�������ߵĻ���
    policy_state[policy_idx] = 2;
    available_policy[policy_idx]->takeEffect();
    //printf("��ǰ�Ľ����䲼�˷���%d\n", policy_idx);
}
int Building::produceActionPoint() {
    //printf("��ǰ����������%d�ж���\n", action_point_per_day);
    return action_point_per_day;
}
void Building::updateChange(double delta) {
    change_in_infection_likelihood += delta;
}
void Building::updateActionPoint(int delta) {
    action_point_per_day += delta;
}
void Building::shutDown() {
    try {
        if (is_shut_down == true)
            throw -1;
    }
    catch (int e) {
        //printf("��ǰ�Ľ����Ѿ����ر�������\n");
    }
    is_shut_down = true;
    //printf("��ǰ�Ľ����Ѿ����ر���\n");
}
bool Building::isShutDown() {
    return is_shut_down;
}
void Building::addPolicy(Policy* p) {
    available_policy[total_number_of_available] = p;
    total_number_of_available++;
}
void Building::updatePolicyState() {
    // ��ʼ���еĶ�������
    memset(policy_state, 0, sizeof(policy_state));
    // �������е����߸��ĵ�ǰ��״̬
    for (int i = 0; i < total_number_of_available; i++) {
        if (policy_state[i] == 0 && available_policy[i]->available())
            policy_state[i] = 1;
    }
}
// ������Ϸ�е�����Щ����
void Building::setInitialPolicy() {
    // ���ǰװ�����
    addPolicy(new RequireMasks(0, 10, this)); // ������ֵ�����
    addPolicy(new MeasureTemperatureAndScanCode(1, 20, this)); // ����ɨ�������
    addPolicy(new ShutDownBuilding(2, 30, this)); // �رս���������
    updatePolicyState();
}
void Building::peopleArrived(int delta, Person* p) {
    if (delta >= 1) {
        people_in_building[total_people] = p;
    }
    else
        people_in_building[total_people] = NULL;
    total_people += delta;
}
int Building::getLevel() { return level; }
int Building::getkind() { return kind; }
int Building::getaction_point_per_day() {return action_point_per_day;}
int Building::getInfectedNumber() { return total_infectd_people; }
int Building::getTotalNumber() { return total_people; }
void Building::infectedPeopleArrived(int delta) {
    total_infectd_people += delta;
}
void Building::addBaffle() { }
void Building::checkAffairHappen() { }
void Building::updateSatisfaction(double delta) {
    for (int i = 0; i < total_people; i++) {
        people_in_building[i]->updateSatisfaction(delta);
    }
}
bool Building::isDormitoryShutDown() {
    if (kind == 0 && is_shut_down)
        return true;
    return false;
}
bool Building::isWinter() {
    return g->getSeason() == 4;
}
double Building::getSatisfaction() {
    // 得到这个建筑里的总的满意度
    double sum = 0;
    for (int i = 0; i < total_people; i++) {
        sum += people_in_building[i]->getSatisfaction();
    }
    return sum / (total_people + 1);
    // 万一只有0个人就崩溃了
}


void DiningHall::setInitialPolicy() {
    // ����ʳ�õĳ�ʼ����
    addPolicy(new AddBaffle(3, 20, this)); // ���赲�������
    addPolicy(new RequireMasks(0, 20, this)); // ������ֵ�����
    addPolicy(new MeasureTemperatureAndScanCode(1, 30, this)); // ����ɨ�������
    addPolicy(new StopDineIn(4, 40, this)); // ֹͣ��ʳ������
    updatePolicyState();
}
DiningHall::DiningHall(int _idx, int _kind, Game* _g) : Building(_idx, _kind,_g) {
    possible_affairs[0] = new NastyMeals(4, 0.001, this);
    possible_affairs[1] = new Gathering(10, 0.001, this);
    possible_affairs[2] = new ProtesetInShudong(11, 0.01, this);
    possible_affairs[3] = new BrokenOutPersonnel(21, 0.01, this);
    num_of_possible_affairs = 4;
    added_baffle = false;
    updateActionPoint(1);

}
void DiningHall::addBaffle() {
    added_baffle = true;
    //printf("ʳ�üӵ����ˣ�\n");
}
void DiningHall::checkAffairHappen() {
    for (int i = 0; i < num_of_possible_affairs; i++) {
        possible_affairs[i]->happen();
    }
}

TeachingBuilding::TeachingBuilding(int _idx, int _kind, Game* _g) : Building(_idx, _kind, _g) {
    updateActionPoint(1);
    possible_affairs[0] = new ProtesetInShudong(11, 0.03, this);
    possible_affairs[1] = new BrokenOutPersonnel(21, 0.03, this);
    num_of_possible_affairs = 2;
}
void TeachingBuilding::setInitialPolicy() {
    addPolicy(new RequireMasks(0, 20, this)); // ������ֵ�����
    addPolicy(new MeasureTemperatureAndScanCode(1, 30, this)); // ����ɨ�������
    addPolicy(new ShutDownBuilding(2, 40, this)); // �رս���������
    updatePolicyState();
}
void TeachingBuilding::checkAffairHappen() {
    for (int i = 0; i < num_of_possible_affairs; i++) {
        possible_affairs[i]->happen();
    }
}


Lake::Lake(int _idx, int _kind, Game* _g) : Building(_idx, _kind, _g) {
    possible_affairs[0] = new CoupleByLake(0, 0.03, this);
    possible_affairs[1] = new ReadByLake(1, 0.03, this);
    possible_affairs[2] = new ProtesetInShudong(11, 0.03, this);
    number_of_possible_affairs = 3;
}
void Lake::checkAffairHappen() {
    for (int i = 0; i < number_of_possible_affairs; i++) {
        possible_affairs[i]->happen();
    }
}

Gymnasium::Gymnasium(int _idx, int _kind, Game* _g) : Building(_idx, _kind, _g) {
    updateActionPoint(1);
    possible_affairs[0] = new ProtesetInShudong(11, 0.001, this);
    possible_affairs[1] = new Top10(26, 0.04, this);
    num_of_possible_affairs = 2;
}
void Gymnasium::checkAffairHappen() {
    for (int i = 0; i < num_of_possible_affairs; i++) {
        possible_affairs[i]->happen();
    }
}
Playground::Playground(int _idx, int _kind, Game* _g) : Building(_idx, _kind, _g) {
    updateActionPoint(1);
    possible_affairs[0] = new ProtesetInShudong(11, 0.04, this);
    num_of_possible_affairs = 1;
}
void Playground::checkAffairHappen() {
    for (int i = 0; i < num_of_possible_affairs; i++) {
        possible_affairs[i]->happen();
    }
}
Library::Library(int _idx, int _kind, Game* _g) : Building(_idx, _kind, _g) {
    possible_affairs[0] = new OnlineExhibition(2, 0.001, this);
    possible_affairs[1] = new ProtesetInShudong(11, 0.001, this);
    possible_affairs[2] = new BrokenOutPersonnel(21, 0.001, this);
    num_of_possible_affairs = 3;
    updateActionPoint(5);
}
void Library::checkAffairHappen() {
    for (int i = 0; i < num_of_possible_affairs; i++) {
        possible_affairs[i]->happen();
    }
}
Gate::Gate(int _idx, int _kind, Game* _g) : Building(_idx, _kind, _g) {
    possible_affairs[0] = new Detention(25, 0.001, this);
    num_of_possible_affairs = 1;
}
void Gate::checkAffairHappen() {
    for (int i = 0; i < num_of_possible_affairs; i++) {
        possible_affairs[i]->happen();
    }
}
Laboratory::Laboratory(int _idx, int _kind, Game* _g) : Building(_idx, _kind, _g) {
    updateActionPoint(5);
    possible_affairs[0] = new ProtesetInShudong(11, 0.03, this);
    num_of_possible_affairs = 1;
}
void Laboratory::checkAffairHappen() {
    for (int i = 0; i < num_of_possible_affairs; i++) {
        possible_affairs[i]->happen();
    }
}
Hospital::Hospital(int _idx, int _kind, Game* _g) : Building(_idx, _kind, _g) {
    updateActionPoint(-5); // 维持医院需要消耗行动点
    possible_affairs[0] = new LuxuriousIsolationConditions(5, 0.02, this);
    possible_affairs[1] = new InterestingQuarantineLife(6, 0.02, this);
    possible_affairs[2] = new ProtesetInShudong(11, 0.02, this);
    possible_affairs[3] = new BrokenOutPersonnel(21, 0.02, this);
    possible_affairs[4] = new VolunteerLack(22, 0.02, this);
    possible_affairs[5] = new LackOfMedicalResources(23, 0.02, this);
    possible_affairs[6] = new GreatPrevention(24, 0.02, this);
    num_of_possible_affairs = 7;
}
void Hospital::checkAffairHappen() {
    for (int i = 0; i < num_of_possible_affairs; i++) {
        possible_affairs[i]->happen();
    }
}
Dormitory::Dormitory(int _idx, int _kind, Game* _g) : Building(_idx, _kind, _g) {
}
void Dormitory::setInitialPolicy() {
    addPolicy(new RequireMasks(0, 20, this)); // ������ֵ�����
    addPolicy(new TemporaryLockdown(5, 30, this)); // ��ʱ��ص�����
    addPolicy(new ShutDownDormitory(6, 40, this)); // �������¥������
    updatePolicyState(); // �������е�����״̬
    possible_affairs[0] = new BrokenWashingMachine(7, 0.0006, this);
    possible_affairs[1] = new BrokenAirConditioner(8, 0.0006, this);
    possible_affairs[2] = new BrokenWaterHeater(9, 0.0006, this);
    possible_affairs[3] = new ProtesetInShudong(11, 0.0006, this);
    possible_affairs[4] = new SingInDormitory(12, 0.0006, this);
    possible_affairs[5] = new ShushuBegins(13, 0.0006, this);
    possible_affairs[6] = new QuarrelInDormitory(14, 0.0006, this);
    possible_affairs[7] = new UnbearableSnoring(15, 0.0006, this);
    possible_affairs[8] = new Top10InBathroom(16, 0.0006, this);
    possible_affairs[9] = new LearningInDormitory(17, 0.0006, this);
    possible_affairs[10] = new MahjongInDormitory(18, 0.0006, this);
    possible_affairs[11] = new HarmoniousDormitory(19, 0.0006, this);
    possible_affairs[12] = new HealthySleeping(20, 0.0006, this);
    possible_affairs[13] = new BrokenHeater(27, 0.0006, this);
    num_of_possible_affairs = 14;
}
void Dormitory::checkAffairHappen() {
    for (int i = 0; i < num_of_possible_affairs; i++) {
        possible_affairs[i]->happen();
    }
}


Building* Policy::BuildingAttached() {
    return building_attached;
}
Policy::Policy(int _idx, int _cost, Building* _b) {
    idx = _idx;
    cost = _cost;
    building_attached = _b;
}
void Policy::takeEffect() { }
void Policy::printPolicy() { }
bool Policy::available() { return true; }

RequireMasks::RequireMasks(int _idx, int _cost, Building* _b) : Policy(_idx, _cost, _b) { }
void RequireMasks::takeEffect() {
    BuildingAttached()->updateChange(-0.00003); // ȡ������ִ�����ЧӦΪ
    BuildingAttached()->updateActionPoint(1); // ÿ��������ж�������1
}
bool RequireMasks::available() {
    // ֻҪ��ǰ��һ���Ľ������Ϳ��Բ����������
    if (BuildingAttached()->getLevel() >= 1)
        return true;
    return false;
}
void RequireMasks::printPolicy() {
    //printf("��ǰ��Ҫ��������ֵ����ߣ�\n");
}

MeasureTemperatureAndScanCode::MeasureTemperatureAndScanCode(int _idx, int _cost, Building* _b) : Policy(_idx, _cost, _b) { }
void MeasureTemperatureAndScanCode::takeEffect() {
    BuildingAttached()->updateChange(-0.00002); // ȡ����ɨ���ЧӦΪ-10%
    BuildingAttached()->updateActionPoint(2); // ÿ��������ж�������2
}
bool MeasureTemperatureAndScanCode::available() {
    // ��ǰ�Ƕ����������Ϳ��Բ����������
    if (BuildingAttached()->getLevel() >= 2)
        return true;
    return false;
}
void MeasureTemperatureAndScanCode::printPolicy() {
    //printf("��ǰ�ǲ���ɨ������ߣ�\n");
}

ShutDownBuilding::ShutDownBuilding(int _idx, int _cost, Building* _b) : Policy(_idx, _cost, _b) { }
void ShutDownBuilding::takeEffect() {
    BuildingAttached()->updateChange(-0.00005); // ȡ�رս�����ЧӦΪ-100%
    BuildingAttached()->updateActionPoint(3); // ÿ��������ж�������3
    BuildingAttached()->shutDown(); // ͬʱ�رյ�ǰ�Ľ���
}
bool ShutDownBuilding::available() {
    // ����һ�������Ľ�������
    if (BuildingAttached()->getLevel() >= 3)
        return true;
    return false;
}
void ShutDownBuilding::printPolicy() {
    //printf("��ǰ�ǹرս��������� \n");
}

AddBaffle::AddBaffle(int _idx, int _cost, Building* _b) : Policy(_idx, _cost, _b) { }
void AddBaffle::takeEffect() {
    BuildingAttached()->updateChange(-0.0001); // ������������ЧӦΪ-5%
    BuildingAttached()->updateActionPoint(1); // ���ӵ��ж�����Ϊ1
    BuildingAttached()->addBaffle(); // ���赲��
}
bool AddBaffle::available() {
    // ����һ��һ������
    if (BuildingAttached()->getLevel() >= 1)
        return true;
    return false;
}
void AddBaffle::printPolicy() {
    //printf("��ǰ�����赲������� \n");
}

StopDineIn::StopDineIn(int _idx, int _kind, Building* _b) : Policy(_idx, _kind, _b) { }
void StopDineIn::takeEffect() {
    BuildingAttached()->updateChange(-0.00003); // ȡֹͣ��ʳ��ЧӦΪ-100%
    BuildingAttached()->updateActionPoint(3); // ÿ��������ж�������3
    BuildingAttached()->shutDown();
}
bool StopDineIn::available() {
    if (BuildingAttached()->getLevel() >= 3)
        return true;
    return false;
}
void StopDineIn::printPolicy() {
    //printf("��ǰ��ֹͣ��ʳ������ \n");
}

TemporaryLockdown::TemporaryLockdown(int _idx, int _kind, Building* _b) : Policy(_idx, _kind, _b) { }
void TemporaryLockdown::takeEffect() {
    BuildingAttached()->updateChange(-0.00003); // ��ʱ��ص�ЧӦΪ-20%
    BuildingAttached()->updateActionPoint(2); // ÿ��������ж�������Ϊ2
}
bool TemporaryLockdown::available() {
    if (BuildingAttached()->getLevel() >= 2)
        return true;
    return false;
}
void TemporaryLockdown::printPolicy() {
    //printf("��ǰ����ʱ��ص����� \n");
}

ShutDownDormitory::ShutDownDormitory(int _idx, int _kind, Building* _b) : Policy(_idx, _kind, _b) { }
void ShutDownDormitory::takeEffect() {
    BuildingAttached()->updateChange(0.00002); // ��������¥������ЧӦΪ+40%
    BuildingAttached()->updateActionPoint(-2); // ÿ��������ж���-2
    BuildingAttached()->shutDown();
}
bool ShutDownDormitory::available() {
    if (BuildingAttached()->getLevel() >= 3)
        return true;
    return false;
}
void ShutDownDormitory::printPolicy() {
    //printf("��ǰ�Ƿ�����ҵ����� \n");
}

Do_pcr::Do_pcr(int _idx, int _kind,Game* game, Building* _b) : Policy(_idx, _kind, _b),g(game) { }
void Do_pcr::takeEffect() {
    g->pcr();
    g->cost_ap(cost);
    printPolicy();
}
bool Do_pcr::available() {
    if (g->getpcr_state())//每天只能颁布一次
        return false;
    else
        return true;
}
void Do_pcr::printPolicy() {
    g->win->a_text(QString::fromUtf8( "进行了全员核酸检测，希望不要有太多新增病例"));
    if(ever_done==false)
    {
        ever_done=true;
        g->win->e_happen(2);
    }
}

ResearchOnVirus::ResearchOnVirus(int _idx, int _kind, Game* game, Building* _b) :Policy(_idx, _kind, _b), g(game) {}
void ResearchOnVirus::takeEffect() {
    g->startResearchOnVirus();
    g->cost_ap(cost);
    printPolicy();
}
bool ResearchOnVirus::available() {
    return !g->getResearchOnVirus_state();
}
void ResearchOnVirus::printPolicy() {
    g->win->a_text(QString::fromUtf8( "开始进行科研专项，这是和病毒在赛跑！"));
}

SuspendCampusTour::SuspendCampusTour(int _idx, int _kind, Game* game, Building* _b) :Policy(_idx, _kind, _b), g(game) {}
void SuspendCampusTour::takeEffect() {
    g->suspendCampusTour();
    for (int i = 0;i <= 70;i++) {
        if (g->all_building[i]->change_in_infection_likelihood >= 0.00001) {
            g->all_building[i]->updateChange(-0.00001);
        }
    }
    g->cost_ap(cost);
    printPolicy();
}
bool SuspendCampusTour::available() {
    return !g->getCampusTour_state();
}
void SuspendCampusTour::printPolicy() {
    g->win->a_text(QString::fromUtf8( "校园参观已经暂停"));
}

PostponeStartOfSchool::PostponeStartOfSchool(int _idx, int _kind, Game* game, Building* _b) :Policy(_idx, _kind, _b), g(game) {}
void PostponeStartOfSchool::takeEffect() {
    g->postponeStartOfSchool();
    for (int i = 0;i <= 70;i++) {
        if (g->all_building[i]->change_in_infection_likelihood >= 0.00001) {
            g->all_building[i]->updateChange(-0.00001);
        }
    }
    g->cost_ap(cost);
    printPolicy();
}
void PostponeStartOfSchool::printPolicy()
{
g->win->a_text(QString::fromUtf8( "经过研究，学校决定实行错峰开学"));
}
bool Game::getPostponeStartOfSchool_state()
{
    return this->postponeStartOfSchool_state;
}
bool PostponeStartOfSchool::available() {
    return !g->getPostponeStartOfSchool_state();
}

ProvideDesktopVideo::ProvideDesktopVideo(int _idx, int _kind, Game* game, Building* _b) :Policy(_idx, _kind, _b), g(game) {};

void ProvideDesktopVideo::takeEffect() {
    g->provideDesktopVideo();
    for (int i = 0;i <= 70;i++) {
        g->all_building[i]->updateSatisfaction(50);
    }
    g->cost_ap(cost);
    printPolicy();
}
bool Game::getProvideDesktopVideo_state()
{
    return provideDesktopVideo_state;
}
bool ProvideDesktopVideo::available() {
    return !g->getProvideDesktopVideo_state();
}
void ProvideDesktopVideo::printPolicy() {
    g->win->a_text(QString::fromUtf8( "学校为全体学生以及教职工申请了视频会议账号，这或许是网课的先兆"));
}

StartOnlineCourse::StartOnlineCourse(int _idx, int _kind, Game* game, Building* _b) :Policy(_idx, _kind, _b), g(game) {};

void StartOnlineCourse::takeEffect() {
    g->startOnlineCourse();
    for (int i = 0;i <= 70;i++) {
        if (g->all_building[i]->change_in_infection_likelihood >= 0.00001) {
            g->all_building[i]->updateChange(-0.00001);
        }
        g->all_building[i]->updateSatisfaction(50);
    }
    g->cost_ap(cost);
    printPolicy();
}
bool StartOnlineCourse::available() {
    return !g->getOnlineCourse_state()&&g->getProvideDesktopVideo_state();
}
void StartOnlineCourse::printPolicy() {
    g->win->a_text(QString::fromUtf8( "疫情影响下，学校决定全面开始网上授课"));
}

StartPF::StartPF(int _idx, int _kind, Game* game, Building* _b) :Policy(_idx, _kind, _b), g(game) {};

void StartPF::takeEffect() {
    g->startPF();
    for (int i = 0;i <= 70;i++) {
        g->all_building[i]->updateSatisfaction(50);
    }
    g->cost_ap(cost);
    printPolicy();
}
bool StartPF::available() {
    return !g->getPF_state()&&g->getOnlineCourse_state();
}
void StartPF::printPolicy() {
    g->win->a_text(QString::fromUtf8( "经过研究，学校决定本学期学生可以自选pf"));
}


Affair::Affair(int _idx, double _p, Building* _b) {
    idx = _idx;
    probability_of_occurrence = _p;
    happened_place = _b;
}
double Affair::getProb() {
    return probability_of_occurrence;
}
Building* Affair::getPlace() {
    return happened_place;
}
void Affair::takeEffect() { }
void Affair::printAffair() { }
void Affair::happen() { }

CoupleByLake::CoupleByLake(int _idx, double _p, Building* _b) : Affair(_idx, _p, _b) { }
void CoupleByLake::happen() {
    uniform_real_distribution<> rdt(0, 1);
    double rand_p = rdt(engine);
    if (rand_p < getProb())
        takeEffect();
}
void CoupleByLake::takeEffect() {
    // δ�����ߵ�С�����¼��������+2
    // �����ٶ�+10%
    getPlace()->updateChange(0.00001);
    // ^ ����Ҫд�����+2��
    // ��ǰ������������˵������+2
    getPlace()->updateSatisfaction(5);
    printAffair();
    //system("pause");
}
void CoupleByLake::printAffair() {
    getPlace()->g->win->e_happen(this->idx);
    //printf("��ǰ��δ�����ߵ�С�����¼�\n");
}

ReadByLake::ReadByLake(int _idx, double _p, Building* _b) : Affair(_idx, _p, _b) { }
void ReadByLake::happen() {
    uniform_real_distribution<> rdt(0, 1);
    double rand_p = rdt(engine);
    if (rand_p < getProb())
        takeEffect();
}
void ReadByLake::takeEffect() {
    // δ�����Ϻö����¼��������ٶ�+10%,�����+2
    getPlace()->updateChange(0.00001);
    // ^����Ҫд�����+2
    getPlace()->updateSatisfaction(5);
    printAffair();
    //system("pause");
}
void ReadByLake::printAffair() {
    getPlace()->g->win->e_happen(this->idx);
}

OnlineExhibition::OnlineExhibition(int _idx, double _p, Building* _b) : Affair(_idx, _p, _b) { }
void OnlineExhibition::happen() {
    uniform_real_distribution<> rdt(0, 1);
    double rand_p = rdt(engine);
    if (rand_p < getProb())
        takeEffect();
}
void OnlineExhibition::takeEffect() {
    getPlace()->updateSatisfaction(5);
    printAffair();
    //system("pause");
}
void OnlineExhibition::printAffair() {
    getPlace()->g->win->e_happen(this->idx);
}

NastyMeals::NastyMeals(int _idx, double _p, Building* _b) : Affair(_idx, _p, _b) { }
void NastyMeals::happen() {
    uniform_real_distribution<> rdt(0, 1);
    double rand_p = rdt(engine);
    if (rand_p < getProb())
        takeEffect();
}
void NastyMeals::takeEffect() {
    getPlace()->updateSatisfaction(-10);
    printAffair();
}
void NastyMeals::printAffair() {
    getPlace()->g->win->e_happen(this->idx);
}

LuxuriousIsolationConditions::LuxuriousIsolationConditions(int _idx, double _p, Building* _b) : Affair(_idx, _p, _b) { }
void LuxuriousIsolationConditions::happen() {
    uniform_real_distribution<> rdt(0, 1);
    double rand_p = rdt(engine);
    if (rand_p < getProb())
        takeEffect();
}
void LuxuriousIsolationConditions::takeEffect() {
    getPlace()->updateSatisfaction(10);
    printAffair();
}
void LuxuriousIsolationConditions::printAffair() {
    getPlace()->g->win->e_happen(this->idx);
}

InterestingQuarantineLife::InterestingQuarantineLife(int _idx, double _p, Building* _b) : Affair(_idx, _p, _b) { }
void InterestingQuarantineLife::happen() {
    uniform_real_distribution<> rdt(0, 1);
    double rand_p = rdt(engine);
    if (rand_p < getProb())
        takeEffect();
}
void InterestingQuarantineLife::takeEffect() {
    getPlace()->updateSatisfaction(5);
    printAffair();
}
void InterestingQuarantineLife::printAffair() {
    getPlace()->g->win->e_happen(this->idx);
}

BrokenWashingMachine::BrokenWashingMachine(int _idx, double _p, Building* _b) : Affair(_idx, _p, _b) { }
void BrokenWashingMachine::happen() {
    uniform_real_distribution<> rdt(0, 1);
    double rand_p = rdt(engine);
    if (rand_p < getProb())
        takeEffect();
}
void BrokenWashingMachine::takeEffect() {
    getPlace()->updateSatisfaction(-20);
    printAffair();
}
void BrokenWashingMachine::printAffair() {
    getPlace()->g->win->e_happen(this->idx);
}

BrokenAirConditioner::BrokenAirConditioner(int _idx, double _p, Building* _b) : Affair(_idx, _p, _b) { }
void BrokenAirConditioner::happen() {
    uniform_real_distribution<> rdt(0, 1);
    double rand_p = rdt(engine);
    if (rand_p < getProb())
        takeEffect();
}
void BrokenAirConditioner::takeEffect() {
    getPlace()->updateSatisfaction(-5);
    printAffair();
}
void BrokenAirConditioner::printAffair() {
    getPlace()->g->win->e_happen(this->idx);
}

BrokenWaterHeater::BrokenWaterHeater(int _idx, double _p, Building* _b) : Affair(_idx, _p, _b) { }
void BrokenWaterHeater::happen() {
    uniform_real_distribution<> rdt(0, 1);
    double rand_p = rdt(engine);
    if (rand_p < getProb())
        takeEffect();
}
void BrokenWaterHeater::takeEffect() {
    getPlace()->updateSatisfaction(-5);
    printAffair();
}
void BrokenWaterHeater::printAffair() {
    getPlace()->g->win->e_happen(this->idx);
}

Gathering::Gathering(int _idx, double _p, Building* _b) : Affair(_idx, _p, _b) { }
void Gathering::happen() {
    uniform_real_distribution<> rdt(0, 1);
    double rand_p = rdt(engine);
    if (rand_p < getProb())
        takeEffect();
}
void Gathering::takeEffect() {
    getPlace()->updateChange(0.00001);
    getPlace()->updateSatisfaction(-10);
    printAffair();
}
void Gathering::printAffair() {
    getPlace()->g->win->e_happen(this->idx);
}

ProtesetInShudong::ProtesetInShudong(int _idx, double _p, Building* _b) : Affair(_idx, _p, _b) { }
void ProtesetInShudong::happen() {
    uniform_real_distribution<> rdt(0, 1);
    double rand_p = rdt(engine);
    if (rand_p < getProb())
        takeEffect();
}
void ProtesetInShudong::takeEffect() {
    getPlace()->updateSatisfaction(-2.5);
    printAffair();
}
void ProtesetInShudong::printAffair() {
    getPlace()->g->win->e_happen(this->idx);
}

SingInDormitory::SingInDormitory(int _idx, double _p, Building* _b) : Affair(_idx, _p, _b) { }
void SingInDormitory::happen() {
    uniform_real_distribution<> rdt(0, 1);
    double rand_p = rdt(engine);
    if (getPlace()->getSatisfaction() < 50)
        rand_p /= 2;
    if (rand_p < getProb())
        takeEffect();
}
void SingInDormitory::takeEffect() {
    getPlace()->updateSatisfaction(-5);
    printAffair();
}
void SingInDormitory::printAffair() {
    getPlace()->g->win->e_happen(this->idx);
}

ShushuBegins::ShushuBegins(int _idx, double _p, Building* _b) : Affair(_idx, _p, _b) { }
void ShushuBegins::happen() {
    uniform_real_distribution<> rdt(0, 1);
    double rand_p = rdt(engine);
    if (getPlace()->getSatisfaction() < 50)
        rand_p /= 2;
    if (rand_p < getProb())
        takeEffect();
}
void ShushuBegins::takeEffect() {
    getPlace()->updateSatisfaction(-5);
    printAffair();
}
void ShushuBegins::printAffair() {
    getPlace()->g->win->e_happen(this->idx);
}

QuarrelInDormitory::QuarrelInDormitory(int _idx, double _p, Building* _b) : Affair(_idx, _p, _b) { }
void QuarrelInDormitory::happen() {
    uniform_real_distribution<> rdt(0, 1);
    double rand_p = rdt(engine);
    if (getPlace()->getSatisfaction() < 50)
        rand_p /= 2;
    if (rand_p < getProb())
        takeEffect();
}
void QuarrelInDormitory::takeEffect() {
    getPlace()->updateSatisfaction(-5);
    printAffair();
}
void QuarrelInDormitory::printAffair() {
    getPlace()->g->win->e_happen(this->idx);
}

UnbearableSnoring::UnbearableSnoring(int _idx, double _p, Building* _b) : Affair(_idx, _p, _b) { }
void UnbearableSnoring::happen() {
    uniform_real_distribution<> rdt(0, 1);
    double rand_p = rdt(engine);
    if (rand_p < getProb())
        takeEffect();
}
void UnbearableSnoring::takeEffect() {
    getPlace()->updateSatisfaction(-5);
    printAffair();
}
void UnbearableSnoring::printAffair() {
    getPlace()->g->win->e_happen(this->idx);
}

Top10InBathroom::Top10InBathroom(int _idx, double _p, Building* _b) : Affair(_idx, _p, _b) { }
void Top10InBathroom::happen() {
    uniform_real_distribution<> rdt(0, 1);
    double rand_p = rdt(engine);
    if (rand_p < getProb())
        takeEffect();
}
void Top10InBathroom::takeEffect() {
    getPlace()->updateSatisfaction(5);
    printAffair();
}
void Top10InBathroom::printAffair() {
    getPlace()->g->win->e_happen(this->idx);
}

LearningInDormitory::LearningInDormitory(int _idx, double _p, Building* _b) : Affair(_idx, _p, _b) { }
void LearningInDormitory::happen() {
    uniform_real_distribution<> rdt(0, 1);
    double rand_p = rdt(engine);
    if (rand_p < getProb())
        takeEffect();
}
void LearningInDormitory::takeEffect() {
    getPlace()->updateSatisfaction(5);
    printAffair();
}
void LearningInDormitory::printAffair() {
    getPlace()->g->win->e_happen(this->idx);
}

MahjongInDormitory::MahjongInDormitory(int _idx, double _p, Building* _b) : Affair(_idx, _p, _b) { }
void MahjongInDormitory::happen() {
    uniform_real_distribution<> rdt(0, 1);
    double rand_p = rdt(engine);
    if (rand_p < getProb())
        takeEffect();
}
void MahjongInDormitory::takeEffect() {
    getPlace()->updateSatisfaction(5);
    printAffair();
}
void MahjongInDormitory::printAffair() {
    getPlace()->g->win->e_happen(this->idx);
}

HarmoniousDormitory::HarmoniousDormitory(int _idx, double _p, Building* _b) : Affair(_idx, _p, _b) { }
void HarmoniousDormitory::happen() {
    uniform_real_distribution<> rdt(0, 1);
    double rand_p = rdt(engine);
    if (rand_p < getProb())
        takeEffect();
}
void HarmoniousDormitory::takeEffect() {
    getPlace()->updateSatisfaction(5);
    printAffair();
}
void HarmoniousDormitory::printAffair() {
    getPlace()->g->win->e_happen(this->idx);
}

HealthySleeping::HealthySleeping(int _idx, double _p, Building* _b) : Affair(_idx, _p, _b) { }
void HealthySleeping::happen() {
    uniform_real_distribution<> rdt(0, 1);
    double rand_p = rdt(engine);
    if (rand_p < getProb())
        takeEffect();
}
void HealthySleeping::takeEffect() {
    getPlace()->updateSatisfaction(5);
    printAffair();
}
void HealthySleeping::printAffair() {
    getPlace()->g->win->e_happen(this->idx);
}

BrokenOutPersonnel::BrokenOutPersonnel(int _idx, double _p, Building* _b) : Affair(_idx, _p, _b) { }
void BrokenOutPersonnel::happen() {
    uniform_real_distribution<> rdt(0, 1);
    double rand_p = rdt(engine);
    if (rand_p < getProb())
        takeEffect();
}
void BrokenOutPersonnel::takeEffect() {
    getPlace()->updateSatisfaction(-5);
    printAffair();
}
void BrokenOutPersonnel::printAffair() {
    getPlace()->g->win->e_happen(this->idx);
}

VolunteerLack::VolunteerLack(int _idx, double _p, Building* _b) : Affair(_idx, _p, _b) { }
void VolunteerLack::happen() {
    uniform_real_distribution<> rdt(0, 1);
    double rand_p = rdt(engine);
    if (rand_p < getProb())
        takeEffect();
}
void VolunteerLack::takeEffect() {
    getPlace()->updateSatisfaction(-5);
    printAffair();
}
void VolunteerLack::printAffair() {
    getPlace()->g->win->e_happen(this->idx);
}

LackOfMedicalResources::LackOfMedicalResources(int _idx, double _p, Building* _b) : Affair(_idx, _p, _b) { }
void LackOfMedicalResources::happen() {
    uniform_real_distribution<> rdt(0, 1);
    double rand_p = rdt(engine);
    if (getPlace()->getInfectedNumber() > 500)
        rand_p /= 2;
    if (rand_p < getProb())
        takeEffect();
}
void LackOfMedicalResources::takeEffect() {
    getPlace()->updateSatisfaction(-5);
    printAffair();
}
void LackOfMedicalResources::printAffair() {
    getPlace()->g->win->e_happen(this->idx);
}

GreatPrevention::GreatPrevention(int _idx, double _p, Building* _b) : Affair(_idx, _p, _b) { }
void GreatPrevention::happen() {
    uniform_real_distribution<> rdt(0, 1);
    double rand_p = rdt(engine);
    if (rand_p < getProb() && getPlace()->getInfectedNumber() < 500 )
        takeEffect();
}
void GreatPrevention::takeEffect() {
    getPlace()->updateSatisfaction(5);
    printAffair();
}
void GreatPrevention::printAffair() {
    getPlace()->g->win->e_happen(this->idx);
}

Detention::Detention(int _idx, double _p, Building* _b) : Affair(_idx, _p, _b) { }
void Detention::happen() {
    uniform_real_distribution<> rdt(0, 1);
    double rand_p = rdt(engine);
    if (rand_p < getProb())
        takeEffect();
}
void Detention::takeEffect() {
    getPlace()->updateSatisfaction(-5);
    printAffair();
}
void Detention::printAffair() {
    getPlace()->g->win->e_happen(this->idx);
}

Top10::Top10(int _idx, double _p, Building* _b) : Affair(_idx, _p, _b) { }
void Top10::happen() {
    uniform_real_distribution<> rdt(0, 1);
    double rand_p = rdt(engine);
    if (rand_p < getProb())
        takeEffect();
}
void Top10::takeEffect() {
    getPlace()->updateChange(0.00001);
    getPlace()->updateSatisfaction(5);
    printAffair();
}
void Top10::printAffair() {
    getPlace()->g->win->e_happen(this->idx);
}

BrokenHeater::BrokenHeater(int _idx, double _p, Building* _b) : Affair(_idx, _p, _b) { }
void BrokenHeater::happen() {
    if (getPlace()->isWinter()) {
        uniform_real_distribution<> rdt(0, 1);
        double rand_p = rdt(engine);
        if (rand_p < getProb())
            takeEffect();
    }
}
void BrokenHeater::takeEffect() {
    getPlace()->updateSatisfaction(-5);
    printAffair();
}
void BrokenHeater::printAffair() {
    getPlace()->g->win->e_happen(this->idx);
}
