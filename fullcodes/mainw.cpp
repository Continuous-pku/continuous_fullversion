#include "mainw.h"
#include "ui_mainw.h"

#include"class.h"
#include"buildings.h"
#include"QSoundEffect"
#include"video.h"

mainw::mainw(Widget *upper,int w,int h, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainw),
    up(upper)
{
    //ui->label->setVisible(false);

    ui->setupUi(this);
    resize(w,h);
    setWindowFlags(Qt::FramelessWindowHint);
    year_month=new QLabel(this);
    day=new QLabel(this);
    ap=new QLabel(this);
    sat=new QLabel(this);
    infect=ui->label;
    //infect=new QLabel(this);
    //infect->set
    game=new Game;
    game->win=this;
    game->gameRun();
    m=new menu(this);
    m->close();
    p=new policy(this);
    p->close();
    b=new buildings(game,this);
    b->info.setGeometry((width()+b->width())/2,(height()-330)/2,256,330);
    b->close();
    e=new QSoundEffect;
    e->setVolume(0.2f);
    back=new QSoundEffect(this);
    back->setVolume(0.2f);
    back->setSource(QUrl("qrc:/new/pics/resouce/sound/back_music.wav"));
    back->setLoopCount(QSoundEffect::Infinite);

    connect(ui->p1,SIGNAL(clicked()),this,SLOT(p1()));
    connect(ui->p2,SIGNAL(clicked()),this,SLOT(p2()));
    connect(ui->p3,SIGNAL(clicked()),this,SLOT(p3()));
    connect(ui->p4,SIGNAL(clicked()),this,SLOT(p4()));
    connect(ui->p5,SIGNAL(clicked()),this,SLOT(p5()));
    connect(ui->p6,SIGNAL(clicked()),this,SLOT(p6()));
    connect(ui->p7,SIGNAL(clicked()),this,SLOT(p7()));
    connect(ui->p8,SIGNAL(clicked()),this,SLOT(p8()));
    connect(ui->p9,SIGNAL(clicked()),this,SLOT(p9()));
    connect(ui->p10,SIGNAL(clicked()),this,SLOT(p10()));
    connect(ui->p11,SIGNAL(clicked()),this,SLOT(p11()));
    connect(ui->p12,SIGNAL(clicked()),this,SLOT(p12()));
    connect(ui->p13,SIGNAL(clicked()),this,SLOT(p13()));
    connect(ui->p14,SIGNAL(clicked()),this,SLOT(p14()));
    connect(ui->p15,SIGNAL(clicked()),this,SLOT(p15()));
}
int mainw::normalize_x(int x)
{
    int w=width();
    x=x*w/1056;
    return x;
}
int mainw::normalize_y(int y)
{
    int h=height();
    //qDebug()<<y;
    y=y*h/621;
    //qDebug()<<y<<' '<<h;
    return y;
}
void mainw::init_()
{
    ui->nextday->setGeometry(normalize_x(900),normalize_y(490),
                                normalize_x(121),normalize_y(101));
    ui->exit->setGeometry(normalize_x(1020),normalize_y(10),
                          normalize_x(31),normalize_y(31));
    ui->menu_->setGeometry(normalize_x(980),normalize_y(10),
                           normalize_x(31),normalize_y(31));
    ui->info_dia->setGeometry(normalize_x(848),normalize_y(108),
                              normalize_x(181),normalize_y(271));
    ui->back->setGeometry(normalize_x(840),normalize_y(100),
                          normalize_x(201),normalize_y(291));
    ui->slog_->setGeometry(normalize_x(387),normalize_y(12),
                           normalize_x(287),normalize_y(50));
    ui->act->setGeometry(normalize_x(30),normalize_y(490),
                         normalize_x(121),normalize_y(101));
    if(act==2)
    {
        ui->pc->setGeometry(normalize_x(780),normalize_y(90),
                            normalize_x(41),normalize_y(71));
        ui->bu->setGeometry(normalize_x(735),normalize_y(110),
                            normalize_x(41),normalize_y(71));
    }
    else if(act==1)
    {
        ui->pc->setGeometry(normalize_x(780),normalize_y(110),
                            normalize_x(41),normalize_y(71));
        ui->bu->setGeometry(normalize_x(735),normalize_y(90),
                            normalize_x(41),normalize_y(71));
    }
    else
    {
        ui->pc->setGeometry(normalize_x(790),normalize_y(90),
                            normalize_x(0),normalize_y(101));
        ui->bu->setGeometry(normalize_x(730),normalize_y(90),
                            normalize_x(0),normalize_y(101));
    }
    QPushButton* p[30]{ui->p1,ui->p2,ui->p3,ui->p4,ui->p5,ui->p6,ui->p7,ui->p8,ui->p9,ui->p10,ui->p11,ui->p12,ui->p13,ui->p14,ui->p15};
    for(int i=0;i<=14;++i)
    {
        p[i]->setGeometry(normalize_x(p[i]->x()),normalize_y(p[i]->y()),
                          normalize_x(p[i]->width()),normalize_y(p[i]->height()));
    }
}
void mainw::showitems()
{
    //qDebug()<<"building!"<<game->getBuilding(0)->getLevel();

    QFont font;
    font.setFamily("等线");
    font.setPointSize(24);

    ui->nextday->setGeometry(normalize_x(900),normalize_y(490),
                                normalize_x(121),normalize_y(101));
    ui->exit->setGeometry(normalize_x(1020),normalize_y(10),
                          normalize_x(31),normalize_y(31));
    ui->menu_->setGeometry(normalize_x(980),normalize_y(10),
                           normalize_x(31),normalize_y(31));

    //这里act==1表示正在升级建筑，2表示正在发布政策，要显示窗口切换按钮
    if(act==2)
    {
        if(ui->pc->width()==0)
        {
            ui->pc->setGeometry(normalize_x(780),normalize_y(90),
                                normalize_x(41),normalize_y(71));
            ui->bu->setGeometry(normalize_x(735),normalize_y(110),
                                normalize_x(41),normalize_y(71));
        }
        else
        {
            b1=ui->bu;
            b2=ui->pc;
            go_up();
            go_down();
        }
    }
    else if(act==1)
    {
        if(ui->pc->width()==0)
        {
            ui->pc->setGeometry(normalize_x(780),normalize_y(110),
                                normalize_x(41),normalize_y(71));
            ui->bu->setGeometry(normalize_x(735),normalize_y(90),
                                normalize_x(41),normalize_y(71));
        }
        else
        {
            b1=ui->pc;
            b2=ui->bu;
            go_up();
            go_down();
        }
    }
    else
    {
        ui->pc->setGeometry(normalize_x(790),normalize_y(90),
                            normalize_x(0),normalize_y(101));
        ui->bu->setGeometry(normalize_x(730),normalize_y(90),
                            normalize_x(0),normalize_y(101));
    }



    year_month->setGeometry(normalize_x(55),normalize_y(80),normalize_x(121),normalize_y(31));
    year_month->setText(QString::fromUtf8(game->yam.c_str()));
    year_month->setStyleSheet("color:white;");
    year_month->setFont(font);
    year_month->show();

    day->setText(to_string(game->getdate()).c_str());
    if(game->getdate()>=10)
        day->setGeometry(normalize_x(75),normalize_y(140),normalize_x(81),normalize_y(61));
    else
        day->setGeometry(normalize_x(93),normalize_y(140),normalize_x(81),normalize_y(61));
    day->setStyleSheet("color:white;");
    font.setPointSize(72);
    day->setFont(font);
    day->show();

    sat->setText(to_string(game->getsat()).c_str());
    sat->setGeometry(normalize_x(240),normalize_y(23),normalize_x(80),normalize_y(21));
    sat->setStyleSheet("color:black;");
    font.setPointSize(22);
    sat->setFont(font);
    sat->show();

    showap();

    infect->setGeometry(normalize_x(657-game->getill()*257/40000-game->getquarantine()*257/40000),normalize_y(21),normalize_x(game->getill()*257/40000+2),normalize_y(26));
    ui->quara->setGeometry(normalize_x(657-game->getquarantine()*257/40000),normalize_y(21),normalize_x(game->getquarantine()*257/40000),normalize_y(26));
}

void mainw::a_text(QString p)
{
    QString tep=ui->infom->text();
    tep=QString::fromUtf8(game->yam.c_str())+QString::fromUtf8(to_string(game->getdate()))+' '+QString::fromUtf8("日")+' '+p+'\n'+'\n'+tep;
    ui->infom->setText(tep);
    return;
}

void mainw::showap(){

    QFont font;
    font.setPointSize(22);
    font.setFamily("等线");
    ap->setText(to_string(game->getap()).c_str());
    ap->setGeometry(normalize_x(70),normalize_y(23),normalize_x(200),normalize_y(21));
    ap->setFont(font);
    ap->show();
}

void mainw::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption o;
    o.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
    QWidget::paintEvent(event);
}

mainw::~mainw()
{
    delete b;
    delete p;
    delete m;
    delete ui;
    delete back;
    delete game;
}

void mainw::button_outlook()
{
    int i=state_;
    switch (i) {
    case 0:{ui->nextday->setStyleSheet(" border-image: url(:/new/pics/resouce/Time/0.png)");break;}
    case 1:{ui->nextday->setStyleSheet(" border-image: url(:/new/pics/resouce/Time/1.png)");break;}
    case 2:{ui->nextday->setStyleSheet(" border-image: url(:/new/pics/resouce/Time/2.png)");break;}
    case 3:{ui->nextday->setStyleSheet(" border-image: url(:/new/pics/resouce/Time/3.png)");break;}
    case 4:{ui->nextday->setStyleSheet(" border-image: url(:/new/pics/resouce/Time/4.png)");break;}
    case 5:{ui->nextday->setStyleSheet(" border-image: url(:/new/pics/resouce/Time/5.png)");break;}
    case 6:{ui->nextday->setStyleSheet(" border-image: url(:/new/pics/resouce/Time/6.png)");break;}
    case 7:{ui->nextday->setStyleSheet(" border-image: url(:/new/pics/resouce/Time/7.png)");break;}
    case 8:{ui->nextday->setStyleSheet(" border-image: url(:/new/pics/resouce/Time/8.png)");break;}
    case 9:{ui->nextday->setStyleSheet("nextday{border-image: url(:/new/pics/resouce/Time/9.png)};"
                                   "nextday:hover{border-image:url(:/new/pics/resouce/next_day_click.png)}");break;}
    default: break;
    }
    state_++;
    timerun();
    return;
}

void mainw:: timerun()
{
    if(state_!=10)
        QTimer::singleShot(100, this, SLOT(button_outlook()));
    else
        state_=0;
}

void mainw::mousePressEvent(QMouseEvent *event)
{
    if(end)
    {
        up->show();
        up->play_bgm();
        this->close();
        delete this;
    }
    //QPointF pl=event->globalPosition();
    //int w=width(),h=height();
    //int x=pl.x(),y=pl.y();
    //normalize
    //x=x*1056/w;
    //y=y*621/h;
}

void mainw::go_up()
{
    if(i1==11)
    {
        i1=0;
        return;
    }
    else
    {
        //qDebug()<<b1->x();
        b1->setGeometry(b1->x(),normalize_y(90+2*i1),
                        normalize_x(41),normalize_y(71));
        b1->show();
        ++i1;
        QTimer::singleShot(25, this, SLOT(go_up()));
    }
}

void mainw::go_down()
{
    if(i2==11)
    {
        i2=0;
        return;
    }
    else
    {
        b2->setGeometry(b2->x(),normalize_y(110-2*i2),
                        normalize_x(41),normalize_y(71));
        b2->show();
        ++i2;
        QTimer::singleShot(25, this, SLOT(go_down()));
    }
}

void mainw::on_nextday_clicked()
{
    if(state_!=0) return;
    timerun();
    int i=game->start_newday();
    ++days;
    p->showits();
    if(i==1)
    {
        QLabel* l=new QLabel;
        l->setText(tr("所有感染者均已康复。你成功守护了学校！！！"));
        l->setParent(this);
        l->setStyleSheet(" border-image: url(:/new/pics/resouce/notice.png)");
        l->setGeometry(width()/2-400/2,height()/2-100,400,200);
        l->show();
        video* v=new video(3);
        v->showFullScreen();
        v->player->play();
        v->button->raise();
        end=true;
    }
    else if(i==-1)
    {
        QLabel* l=new QLabel;
        QString str;
        l->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        str=tr("你坚持了")+QString::fromUtf8(std::to_string(days))+tr("天，游戏结束！鼠标单击以返回开始界面，");
        l->setText(str);
        l->setParent(this);
        l->setStyleSheet(" border-image: url(:/new/pics/resouce/notice.png)");
        l->setGeometry(width()/2-400/2,height()/2-200/2,400,200);
        l->show();
        video* v=new video(2);
        v->showFullScreen();
        v->player->play();
        v->button->raise();
        end=true;
    }
}


void mainw::e_happen(int idx){
    Event_*e=new Event_(idx,this);
    e->setGeometry((width()-e->width())/2,(height()-e->height())/2,e->width(),e->height());
    e->show();
    showitems();
}

void mainw::on_exit_clicked()
{
    close();
    delete this;
}


void mainw::on_menu__clicked()
{
    m->show();
    m->raise();
}


void mainw::on_pc_clicked()
{
    p->show();
    p->raise();
    p->showits();
    b->close();
    b->info.close();
    act=2;
    showitems();
}


void mainw::on_bu_clicked()
{
    b->show();
    b->raise();
    b->info.show();
    b->info.raise();
    p->close();
    act=1;
    showitems();
}


void mainw::on_act_clicked()
{
    e->setSource(QUrl("qrc:/new/pics/resouce/sound/phone-dial-01.wav"));
    e->play();
    b->show();
    b->raise();
    b->info.show();
    b->info.raise();
    act=1;
    showitems();
}


void mainw::p1()
{
    b->goto_build(63);
    b->show();
    b->raise();
    b->info.show();
    b->info.raise();
    act=1;
    showitems();
}


void mainw::p2()
{
    b->goto_build(58);
    b->show();
    b->raise();
    b->info.show();
    b->info.raise();
    act=1;
    showitems();
}


void mainw::p3()
{
    b->goto_build(56);
    b->show();
    b->raise();
    b->info.show();
    b->info.raise();
    act=1;
    showitems();
}


void mainw::p4()
{
    b->goto_build(64);
    b->show();
    b->raise();
    b->info.show();
    b->info.raise();
    act=1;
    showitems();
}


void mainw::p5()
{
    b->goto_build(52);
    b->show();
    b->raise();
    b->info.show();
    b->info.raise();
    act=1;
    showitems();
}


void mainw::p6()
{
    b->goto_build(62);
    b->show();
    b->raise();
    b->info.show();
    b->info.raise();
    act=1;
    showitems();
}


void mainw::p7()
{
    b->goto_build(60);
    b->show();
    b->raise();
    b->info.show();
    b->info.raise();
    act=1;
    showitems();
}


void mainw::p8()
{
    b->goto_build(61);
    b->show();
    b->raise();
    b->info.show();
    b->info.raise();
    act=1;
    showitems();
}


void mainw::p15()
{
    b->goto_build(45);
    b->show();
    b->raise();
    b->info.show();
    b->info.raise();
    act=1;
    showitems();
}


void mainw::p9()
{
    b->goto_build(0);
    b->show();
    b->raise();
    b->info.show();
    b->info.raise();
    act=1;
    showitems();
}


void mainw::p13()
{

    b->goto_build(0);
    b->show();
    b->raise();
    b->info.show();
    b->info.raise();
    act=1;
    showitems();
}


void mainw::p14()
{
    b->goto_build(48);
    b->show();
    b->raise();
    b->info.show();
    b->info.raise();
    act=1;
    showitems();
}


void mainw::p12()
{
    b->goto_build(0);
    b->show();
    b->raise();
    b->info.show();
    b->info.raise();
    act=1;
    showitems();
}


void mainw::p11()
{
    b->goto_build(49);
    b->show();
    b->raise();
    b->info.show();
    b->info.raise();
    act=1;
    showitems();
}


void mainw::p10()
{
    b->goto_build(47);
    b->show();
    b->raise();
    b->info.show();
    b->info.raise();
    act=1;
    showitems();
}

