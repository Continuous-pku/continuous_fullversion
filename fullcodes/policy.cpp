#include "policy.h"
#include"pchoice.h"
#include "ui_policy.h"
#include"mainw.h"
#include"pchoice.h"
#include"QSoundEffect"

policy::policy(mainw *parent) :
    QWidget(parent),
    ui(new Ui::policy),
    p(parent)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    //把窗口背景设置为透明
    setAttribute(Qt::WA_TranslucentBackground);
    setGeometry((parent->width()-926)/2,(parent->height()-483)/2,926,483);
    son=new pchoice(this);
    son->close();
    son->setGeometry((width()-406)/2,(height()-419)/2,406,419);

    connect(ui->hesuan,SIGNAL(clicked()),this,SLOT(hesuan_clicked()));


    //QPixmap pix;
    //pix.load("qrc:/new/pics/resouce/policy.png",0,Qt::AvoidDither);   //如果没有将图片添加为资源文件，此处路径更改为完整路径
    //resize(pix.size());
    //setMask(QBitmap(pix.mask()));
    //resize(809,455);

    //this->setModal
}


policy::~policy()
{
    delete son;
    delete ui;
}

void policy::showits()
{
    if(p->game->getProvideDesktopVideo_state())
        ui->cover3->setGeometry(370,180,0,101);
    else
        ui->cover3->setGeometry(370,180,231,101);
    if(p->game->getOnlineCourse_state())
        ui->cover4->setGeometry(340,60,0,81);
    else
        ui->cover4->setGeometry(340,60,291,81);
    if(son->p!=NULL)
    {
        son->set_items(son->p);
    }
}

void policy::hesuan_clicked()
{
    son->set_items(p->game->get_policy(0));
    son->show();
}


void policy::on_exit_clicked()
{
    p->act=false;
    p->showitems();
    close();
}


void policy::on_keyan_clicked()
{
    son->set_items(p->game->get_policy(1));
    son->show();
}


void policy::on_canguan_clicked()
{
    son->set_items(p->game->get_policy(2));
    son->show();
}


void policy::on_kaixue_clicked()
{
    son->set_items(p->game->get_policy(3));
    son->show();
}


void policy::on_shipin_clicked()
{
    son->set_items(p->game->get_policy(4));
    son->show();
}


void policy::on_wangke_clicked()
{
    son->set_items(p->game->get_policy(5));
    son->show();
}


void policy::on_pf_clicked()
{
    son->set_items(p->game->get_policy(6));
    son->show();
}

