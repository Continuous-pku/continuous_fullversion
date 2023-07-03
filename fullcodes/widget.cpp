
#include "widget.h"
#include "ui_widget.h"
#include"QStyleOption"
#include"QPainter"
#include"video.h"
#include"mainw.h"
#include<QVideoWidget>
#include<QMediaPlayer>
#include<QMouseEvent>
#include"tutor.h"
#include"QSoundEffect"
#include"QTimer.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    tut=new tutor(this);
    tut->close();
    sound=new QSoundEffect(this);
    sound->setVolume(0.1f);
    sound->setSource(QUrl("qrc:/new/pics/resouce/sound/begin_page.wav"));
    sound->play();
    s=new save_and_load(this);
    s->showits();
    s->close();
}

Widget::~Widget()
{
    delete tut;
    delete sound;
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption o;
    o.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
    QWidget::paintEvent(event);
}

void Widget::on_pushButton_2_clicked()
{
    close();
}


void Widget::on_pushButton_released()
{
    //video* t=new video(1);
    //t->player->setSource(QUrl("qrc:/new/pics/resouce/load.mp4"));
    //t->player->play();
    //t->showFullScreen();
    //while(true)
    //{
    //    if(t->player->mediaStatus()==QMediaPlayer::EndOfMedia) break;
    //    QCoreApplication::processEvents();
    //}
    sound->stop();
    mainw *w=new mainw(this,width(),height());
    w->show();
    //t->close();
    w->init_();
    w->showitems();
    w->back->play();
    //t->close();
    //delete t;
    close();
}


void Widget::on_pushButton_3_clicked()
{
    tut->setGeometry((width()-tut->width())/2,(height()-tut->height())/2,tut->width(),tut->height());
    tut->show();
}

void Widget::play_bgm()
{
    sound->play();
}

void Widget::on_pushButton_4_clicked()
{
    s->setGeometry((width()-s->width())/2,(height()-s->height())/2,s->width(),s->height());
    s->show();
}

