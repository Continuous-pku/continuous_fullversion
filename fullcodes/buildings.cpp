#include "buildings.h"
#include "ui_buildings.h"
#include"QStyleOption"
#include"QPainter"
#include"QMouseEvent"
#include"QDebug"
#include<string>
#include<qstringlist.h>
#include"mainw.h"
#include"build_info.h"
#include"note.h"
#include"QSoundEffect"

buildings::buildings(Game* game, mainw *parent) :
    QWidget(parent),
    g(game),
    _parent(parent),
    ui(new Ui::buildings)
{
    //qDebug()<<"building!"<<game->getBuilding(0)->getLevel();
    //下面是左框信息初始化
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    //把窗口背景设置为透明
    setAttribute(Qt::WA_TranslucentBackground);
    setGeometry((parent->width()-926)/2,(parent->height()-483)/2,926,483);
    options << tr("1号宿舍楼")<< tr("2号宿舍楼")<< tr("3号宿舍楼")<< tr("4号宿舍楼")<< tr("5号宿舍楼")<< tr("6号宿舍楼")
            << tr("7号宿舍楼")<< tr("8号宿舍楼")<< tr("9号宿舍楼")<< tr("10号宿舍楼")<< tr("11号宿舍楼")<< tr("12号宿舍楼")
            << tr("13号宿舍楼")<< tr("14号宿舍楼")<< tr("15号宿舍楼")<< tr("16号宿舍楼")<< tr("17号宿舍楼")<< tr("18号宿舍楼")
            << tr("19号宿舍楼")<< tr("20号宿舍楼")<< tr("21号宿舍楼")<< tr("22号宿舍楼")<< tr("23号宿舍楼")<< tr("24号宿舍楼")
            << tr("25号宿舍楼")<< tr("26号宿舍楼")<< tr("27号宿舍楼")<< tr("28号宿舍楼")<< tr("29号宿舍楼")<< tr("30号宿舍楼")
            << tr("31号宿舍楼")<< tr("32号宿舍楼")<< tr("33号宿舍楼")<< tr("34号宿舍楼")<< tr("35号宿舍楼")<< tr("36号宿舍楼")
            << tr("37号宿舍楼")<< tr("38号宿舍楼")<< tr("39号宿舍楼")<< tr("40号宿舍楼")<< tr("41号宿舍楼")<< tr("42号宿舍楼")
            << tr("43号宿舍楼")<< tr("44号宿舍楼")<< tr("45号宿舍楼")<< tr("农园食堂")<< tr("艺院食堂")<< tr("家园食堂")
            << tr("勺园食堂")<< tr("学一食堂")<< tr("学五食堂")<< tr("第一教学楼")<< tr("第二教学楼")<< tr("第三教学楼")
            << tr("第四教学楼")<< tr("理科教学楼")<< tr("文史楼")<< tr("地学楼")<< tr("图书馆")<< tr("医学部")
            << tr("五四操场")<< tr("五四体育馆")<< tr("邱徳拔体育馆")<< tr("未名湖")<< tr("理科实验楼")<< tr("东门")
            << tr("南门")<< tr("西门")<< tr("西南门")<< tr("东南门")<< tr("东北门");

    //下面是右侧框初始化
    pob[0]=&po1;
    pob[1]=&po2;
    pob[2]=&po3;
    pob[3]=&po4;
    ptr=g->getBuilding(0);
    //qDebug()<<"building!"<<game->getBuilding(0)->getLevel();

    ops << tr("要求佩戴口罩")<< tr("测温扫码")<< tr("关闭建筑")<< tr("设置挡板")<< tr("停止堂食")<< tr("临时封控")<< tr("封闭宿舍");
    for(int i=0;i<ptr->total_number_of_available;++i)
    {
        po[i]=ptr->available_policy[i];
    }

    connect(&po1,SIGNAL(clicked()),this,SLOT(po1_clicked()));
    connect(&po2,SIGNAL(clicked()),this,SLOT(po2_clicked()));
    connect(&po3,SIGNAL(clicked()),this,SLOT(po3_clicked()));
    connect(&po4,SIGNAL(clicked()),this,SLOT(po4_clicked()));

    ui->name->setText(options[ptr->idx]);
    info.setParent(parent);
    info.close();
    seti(ptr);
    show_buttons(ptr);
    set_level(ptr->getLevel());
    show_info();
    //info.show();

    for(int i=0;i<4;++i)
    {
        a[i].close();
    }

    sound=new QSoundEffect(this);
    sound->setVolume(0.25f);

    //初始时指向1号宿舍楼
}


buildings::~buildings()
{
    delete sound;
    delete ui;
}

void buildings::seti(Building* b)
{


    if(b->kind==0)
        ui->picture->setStyleSheet(" border-image: url(:/new/pics/resouce/buildings/image/dormitory.png)");
    else if(b->kind==1)
    {
        if(b->idx==45)
            ui->picture->setStyleSheet(" border-image: url(:/new/pics/resouce/buildings/image/nongyuand.png)");
        else if(b->idx==46)
            ui->picture->setStyleSheet(" border-image: url(:/new/pics/resouce/buildings/image/yiyuand.png)");
        else if(b->idx==47)
            ui->picture->setStyleSheet(" border-image: url(:/new/pics/resouce/buildings/image/jiayuand.png)");
        else if(b->idx==48)
            ui->picture->setStyleSheet(" border-image: url(:/new/pics/resouce/buildings/image/shaoyuand.png)");
        else if(b->idx==49)
            ui->picture->setStyleSheet(" border-image: url(:/new/pics/resouce/buildings/image/xueyi.png)");
        else if(b->idx==50)
            ui->picture->setStyleSheet(" border-image: url(:/new/pics/resouce/buildings/image/xuewu.png)");
    }
    else if(b->kind==2)
    {
        if(b->idx==51)
            ui->picture->setStyleSheet(" border-image: url(:/new/pics/resouce/buildings/image/yijiao.png)");
        else if(b->idx==52)
            ui->picture->setStyleSheet(" border-image: url(:/new/pics/resouce/buildings/image/erjiao.png)");
        else if(b->idx==53)
            ui->picture->setStyleSheet(" border-image: url(:/new/pics/resouce/buildings/image/sanjiao.png)");
        else if(b->idx==54)
            ui->picture->setStyleSheet(" border-image: url(:/new/pics/resouce/buildings/image/sijiao.png)");
        else if(b->idx==55)
            ui->picture->setStyleSheet(" border-image: url(:/new/pics/resouce/buildings/image/lijiao.png)");
        else if(b->idx==56||b->idx==57)
            ui->picture->setStyleSheet(" border-image: url(:/new/pics/resouce/buildings/image/wenshi.png)");
    }
    else if(b->kind==3)
        ui->picture->setStyleSheet(" border-image: url(:/new/pics/resouce/buildings/image/library.png)");
    else if(b->kind==4)
        ui->picture->setStyleSheet(" border-image: url(:/new/pics/resouce/buildings/image/hospital.png)");
    else if(b->kind==5)
        ui->picture->setStyleSheet(" border-image: url(:/new/pics/resouce/buildings/image/playground.png)");
    else if(b->kind==6)
    {

        if(b->idx==61)
            ui->picture->setStyleSheet(" border-image: url(:/new/pics/resouce/buildings/image/54.png)");
        else
            ui->picture->setStyleSheet(" border-image: url(:/new/pics/resouce/buildings/image/qdb.png)");
    }
    else if(b->kind==7)
        ui->picture->setStyleSheet(" border-image: url(:/new/pics/resouce/buildings/image/lake.png)");
    else if(b->kind==8)
        ui->picture->setStyleSheet(" border-image: url(:/new/pics/resouce/buildings/image/liyi.png)");
    else if(b->kind==9)
    {
        if(b->idx==66)
            ui->picture->setStyleSheet(" border-image: url(:/new/pics/resouce/buildings/image/northgate.png)");
        else if(b->idx==67)
            ui->picture->setStyleSheet(" border-image: url(:/new/pics/resouce/buildings/image/westgate.png)");
        else if(b->idx==68)
            ui->picture->setStyleSheet(" border-image: url(:/new/pics/resouce/buildings/image/southwestgate.png)");
        else if(b->idx==69||b->idx==70)
            ui->picture->setStyleSheet(" border-image: url(:/new/pics/resouce/buildings/image/southeastgate.png)");
        else
            ui->picture->setStyleSheet(" border-image: url(:/new/pics/resouce/buildings/image/eastgate.png)");
    }
}

void buildings::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption o;
    o.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
    QWidget::paintEvent(event);
}


void buildings::mousePressEvent(QMouseEvent *event)
{

}

//这里用于展示该建筑的所有政策
void buildings::show_buttons(Building *b)
{
    pob[0]->close();
    pob[1]->close();
    pob[2]->close();
    pob[3]->close();

    int l1=0,l2=0,l3=0;
    for(int i=0;i<4;++i)
        a[i].close();
    //qDebug()<<b->total_number_of_available;
    for(int i=0;i<b->total_number_of_available;++i)
    {
        switch(po[i]->idx)
        {
        case 0:{++l1;break;}
        case 1:{++l2;break;}
        case 2:{++l3;break;}
        case 3:{++l1;break;}
        case 4:{++l3;break;}
        case 5:{++l2;break;}
        case 6:{++l3;break;}
        };
    }
    int x=0,y=0;
    for(int i=0;i<b->total_number_of_available;++i)
    {
        switch(po[i]->idx)
        {
        case 0:{x=1;y=393;break;}
        case 1:{x=2;y=355;break;}
        case 2:{x=3;y=317;break;}
        case 3:{x=1;y=393;break;}
        case 4:{x=3;y=317;break;}
        case 5:{x=2;y=355;break;}
        case 6:{x=3;y=317;break;}
        };
        pob[i]->setParent(this);
        pob[i]->setText(ops[po[i]->idx]);
        if(x==1)
        {
            if(l1==1) x=610;
            else if(l1==2) {x=540;l1=-1;}
            else if(l1==-1) x=670;
        }
        else if(x==2)
        {
            if(l2==1) x=610;
            else if(l2==2) {x=540;l1=-1;}
            else if(l2==-1) x=670;
        }
        else if(x==3)
        {
            if(l3==1) x=610;
            else if(l3==2) {x=540;l1=-1;}
            else if(l3==-1) x=670;
        }
        pob[i]->setGeometry(x,y,101,29);
        pob[i]->show();
        a[i].setParent(this);
        a[i].setStyleSheet(" border-image: url(:/new/pics/resouce/have_done.png)");
        a[i].setGeometry(x,y-15,91,61);
        if (b->policy_state[i] == 2)
        {
            a[i].show();
        }
    }

    set_level(ptr->getLevel());

    ui->l3->raise();
    ui->l2->raise();
}

void buildings::set_level(int level)
{
    if(level==1)
        ui->level->setGeometry(451,385,51,41);
    else if(level==2)
        ui->level->setGeometry(451,350,51,76);
    else if(level==3)
        ui->level->setGeometry(451,313,51,113);

    if(ptr->getLevel()==3)
    {
        ui->level_up->setStyleSheet("QPushButton{border-image: url(:/new/pics/resouce/buildings/l_max.png)}");
        ui->l3->setGeometry(530,310,0,45);
        ui->l2->setGeometry(530,350,0,45);
    }

    if(ptr->getLevel()==2)
    {
        ui->level_up->setStyleSheet("#level_up{border-image: url(:/new/pics/resouce/buildings/l_up.png);}"
                                    "#level_up:hover{border-image: url(:/new/pics/resouce/buildings/l_up_c.png);}"
                                    "#level_up:pressed{border-image: url(:/new/pics/resouce/buildings/l_up_h.png);}");
        ui->l3->setGeometry(530,310,241,45);
        ui->l2->setGeometry(530,350,0,45);
    }

    if(ptr->getLevel()==1)
    {
        ui->level_up->setStyleSheet("#level_up{border-image: url(:/new/pics/resouce/buildings/l_up.png);}"
                                    "#level_up:hover{border-image: url(:/new/pics/resouce/buildings/l_up_c.png);}"
                                    "#level_up:pressed{border-image: url(:/new/pics/resouce/buildings/l_up_h.png);}");
        ui->l3->setGeometry(530,310,241,45);
        ui->l2->setGeometry(530,350,241,45);
    }
}

void buildings::goto_build(int t)
{
    ptr=g->getBuilding(t);
    //qDebug()<<options[ptr->idx]<<ptr->getkind()<<ptr->total_number_of_available;
    for(int i=0;i<ptr->total_number_of_available;++i)
    {
        po[i]=ptr->available_policy[i];
    }
    seti(ptr);
    ui->name->setText(options[ptr->idx]);
    show_buttons(ptr);
    set_level(ptr->getLevel());
    show_info();
}

void buildings::on_treeWidget_itemPressed(QTreeWidgetItem *item, int column)
{
    sound->setSource(QUrl("qrc:/new/pics/resouce/sound/click.wav"));
    sound->play();
    QString str =item->text(column);
    int temp=options.indexOf(str);
    if(temp==-1) return;
    goto_build(temp);
    //qDebug()<<"a";
    //qDebug()<<"b";
    /*son=new b_upgrade(tep,str,this);
    //qDebug()<<"c";
    son->setGeometry(this->geometry().x()+320,this->geometry().y(),son->width(),son->height());
    outl=true;
    son->show();
    son->info->setGeometry(this->geometry().x()+320+son->width(),this->geometry().y()+76,son->info->width(),son->info->height());
    son->info->show();*/
}


void buildings::on_pushButton_clicked()
{
    sound->setSource(QUrl("qrc:/new/pics/resouce/sound/click.wav"));
    sound->play();
    info.close();
    _parent->act=false;
    _parent->showitems();
    this->close();
}

void buildings::show_policy_up(Building *build,int i)
{
    info.show_i();
    QString tep=options[build->idx]+tr("已颁布政策")+ops[po[i]->idx]+'\n';
    switch(po[i]->idx)
    {
    case 0:{tep+=tr("场所的防疫能力大幅提升了");break;}
    case 1:{tep+=tr("场所防疫能力小幅提升");break;}
    case 2:{;break;}
    case 3:{tep+=tr("场所防疫能力大幅提升了");break;}
    case 4:{;break;}
    case 5:{;break;}
    }

   g->win->a_text(tep);
}

void buildings::po1_clicked()
{
   sound->setSource(QUrl("qrc:/new/pics/resouce/sound/click.wav"));
   sound->play();
    //qDebug()<<"po1!";
    if (ptr->policy_state[0] == 0||ptr->policy_state[0] == 2) {
        return;
    }
    else {
        if (g->cost_ap(po[0]->cost))
        {
        ptr->enactPolcy(0);
        if (ptr->isShutDown())
            g->is_building_shut_down = true;

        a[0].show();
        show_policy_up(ptr,0);
        }
        else
        {
        note* n=new note(this);
        n->Note(this,po[0]->cost,500);
        n->show();
        }
    }
    show_info();
}

void buildings::po2_clicked()
{
    sound->setSource(QUrl("qrc:/new/pics/resouce/sound/click.wav"));
    sound->play();
    //qDebug()<<"po1!";
    if (ptr->policy_state[1] == 0||ptr->policy_state[1] == 0) {
        return;
    }
    else {
        if (g->cost_ap(po[1]->cost))
        {
        ptr->enactPolcy(1);
        if (ptr->isShutDown())
            g->is_building_shut_down = true;

        a[1].show();
        show_policy_up(ptr,1);
        }
        else
        {
        note* n=new note(this);
        n->Note(this,po[1]->cost,500);
        n->show();
        }
    }
    show_info();

}

void buildings::po3_clicked()
{
    sound->setSource(QUrl("qrc:/new/pics/resouce/sound/click.wav"));
    sound->play();
    //qDebug()<<"po1!";
    if (ptr->policy_state[2] == 0||ptr->policy_state[2] == 2) {
        return;
    }
    else {
        if (g->cost_ap(po[2]->cost))
        {
        ptr->enactPolcy(2);
        if (ptr->isShutDown())
            g->is_building_shut_down = true;

        a[2].show();
        show_policy_up(ptr,2);
        }
        else
        {
        note* n=new note(this);
        n->Note(this,po[2]->cost,500);
        n->show();
        }
    }
    show_info();

}

void buildings::po4_clicked()
{
    sound->setSource(QUrl("qrc:/new/pics/resouce/sound/click.wav"));
    sound->play();
    //qDebug()<<"po1!";
    if (ptr->policy_state[3] == 0) {
        return;
    }
    else {
        if (g->cost_ap(po[3]->cost))
        {
        ptr->enactPolcy(3);
        if (ptr->isShutDown())
            g->is_building_shut_down = true;

        a[3].show();
        //qDebug()<<"qwq";
        show_policy_up(ptr,3);
        //qDebug()<<"qwqa";
        }
        else
        {
        note* n=new note(this);
        n->Note(this,po[3]->cost,500);
        n->show();
        }
    }
    show_info();
}

void buildings::on_level_up_clicked()
{
    sound->setSource(QUrl("qrc:/new/pics/resouce/sound/click.wav"));
    sound->setVolume(0.05f);
    sound->play();
    if(ptr->getLevel()==3) return;
    if (g->cost_ap(ptr->upgrade_cost[ptr->getLevel()]))
    {
        sound->setSource(QUrl("qrc:/new/pics/resouce/sound/level_up.wav"));
        sound->play();
        g->cost_ap(ptr->upgrade_cost[ptr->getLevel()]);
        ptr->upgrade();
        set_level(ptr->getLevel());
        /*
        if(ptr->getLevel()==3)
        ui->level_up->setText(tr("MAX"));
        if(ptr->getLevel()==3)
        {
        //ui->l3->setGeometry(105,295,0,41);
        //ui->l2->setGeometry(105,342,0,41);
        }

        if(ptr->getLevel()==2)
        {
        //ui->l2->setGeometry(105,342,0,41);
        }*/
        //info->show_i();
        qDebug()<<"play";
        QString tep=options[ptr->idx]+tr("升级到了")+QString::fromUtf8(to_string(ptr->getLevel()))+tr("级");
                      if(ptr->kind==0) tep+='\n'+tr("这个宿舍每天提供的行动力增加了");
        g->win->a_text(tep);
    }
    else{
        note* n=new note(this);
        n->Note(this,ptr->upgrade_cost[ptr->level],500);
        n->show();
    }
    show_info();
}

void buildings::show_info()
{
    info.b=ptr;
    info.show_i();
    for(int i=0;i<ptr->total_number_of_available;++i)
    {
        info.show_p(i+1,ops[po[i]->idx],po[i]->cost);
    }
    //qDebug()<<"avs:"<<ptr->total_number_of_available;
}
