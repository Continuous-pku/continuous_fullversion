#ifndef MAINW_H
#define MAINW_H

#include <QWidget>
#include "ui_mainw.h"
#include"event_.h"
#include"QStyleOption"
#include"QPainter"
#include"QMouseEvent"
#include"menu.h"
#include"policy.h"
#include<cstring>
#include<QTimer>
#include"widget.h"

class Game;
class buildings;
class menu;
class policy;
class QSoundEffect;

namespace Ui {
class mainw;
}

class mainw : public QWidget
{
    Q_OBJECT

public:
    explicit mainw(Widget *upper,int w,int h,QWidget *parent = nullptr);
    ~mainw();
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    QString yearmonth;
    int normalize_x(int x);
    int normalize_y(int y);
    void a_text(QString s);
    void showitems();
    void showap();
    void e_happen(int idx);
    void init_();

    Game* game;
    QLabel*year_month,*day,*sat,*ap,*infect;
    buildings* b;
    int act=0;

    int days=0;
    QSoundEffect* back,*e;

private slots:
    void on_nextday_clicked();

    void on_exit_clicked();

    void on_menu__clicked();

    void on_pc_clicked();

    void on_bu_clicked();

    void on_act_clicked();

    void p1();
    void p2();
    void p3();
    void p4();
    void p5();
    void p6();
    void p7();
    void p8();
    void p9();
    void p10();
    void p11();
    void p12();
    void p13();
    void p14();
    void p15();

    void button_outlook();
    void go_up();
    void go_down();

private:
    Ui::mainw *ui;
    bool end=false;
    Widget* up;
    menu *m;
    policy *p;
    void timerun();
    int state_=0;
    QPushButton* b1=NULL,*b2=NULL;
    int i1=0,i2=0;
};

#endif // MAINW_H
