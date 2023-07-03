
#include "video.h"
#include<QMediaPlayer>
#include<QVideoWidget>
#include <QMouseEvent>
#include <QAudioOutput>
#include"QTime"
#include"QCoreApplication"

video::video(int s,Widget* p):parent(p)
{
    state=s;
    player=new QMediaPlayer;
    QAudioOutput* audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);
    setFocus();
    setWindowFlag(Qt::FramelessWindowHint);
    //resize(802,456);
    player->setVideoOutput(this);
    if(s==0)
        player->setSource(QUrl("qrc:/new/pics/resouce/open.mp4"));
    if(s==1)
        player->setSource(QUrl("qrc:/new/pics/resouce/load.mp4"));
    if(s==2)
    {
        player->setSource(QUrl("qrc:/new/pics/resouce/videos/defeat.mp4"));
        button=new QPushButton(this);
        button->setGeometry(0,0,101,29);
        button->setStyleSheet(" border-image: url(:/new/pics/resouce/skip.png)");
        button->setText(" ");
        connect(button,SIGNAL(clicked()),this,SLOT(cls()));
        button->show();
    }
    if(s==3)
    {
        player->setSource(QUrl("qrc:/new/pics/resouce/videos/success.mp4"));
        button=new QPushButton(this);
        button->setGeometry(0,0,101,29);
        button->setStyleSheet(" border-image: url(:/new/pics/resouce/skip.png)");
        button->setText(" ");
        connect(button,SIGNAL(clicked()),this,SLOT(cls()));
        button->show();
    }
    //player->play();
    //showFullScreen();
    //show();
}

void video::endofv()
{
    close();
    delete this;
}
void video::cls()
{
    close();
    delete this;
}

void video::mousePressEvent(QMouseEvent *event)
{
    if(state==1)
    {
        //close();
        //delete this;
        return;
    }
    if(state==0)
    {
        state=-1;
        player->setSource(QUrl("qrc:/new/pics/resouce/start_page.mp4"));
        player->play();
        while(true)
        {
            if(player->mediaStatus()==QMediaPlayer::EndOfMedia) break;
            QCoreApplication::processEvents();
        }
        parent->show();
        //_sleep(3000);
        close();
        delete this;
        //qDebug()<<tr("happens");
    }
    else if(state==2)
    {
        if(player->mediaStatus()==QMediaPlayer::EndOfMedia)
        {
        close();
        }
    }
    else if(state==3)
    {
        if(player->mediaStatus()==QMediaPlayer::EndOfMedia)
        {
        close();
        }
    }
    return;
}

void video::keyPressEvent(QKeyEvent *ev)
{
    if(state==1)
    {
        //close();
        //delete this;
        return;
    }
    if(state==0)
    {
        state=-1;
        player->setSource(QUrl("qrc:/new/pics/resouce/start_page.mp4"));
        player->play();
        while(true)
        {
            if(player->mediaStatus()==QMediaPlayer::EndOfMedia) break;
            QCoreApplication::processEvents();
        }
        parent->show();
        //_sleep(3000);
        close();
        delete this;
        //qDebug()<<tr("happens");
    }
    return;
}
