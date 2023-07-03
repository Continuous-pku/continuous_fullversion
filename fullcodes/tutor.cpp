#include "tutor.h"
#include "ui_tutor.h"

tutor::tutor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tutor)
{
    ui->setupUi(this);
}

tutor::~tutor()
{
    delete ui;
}

void tutor::show_stuff()
{
    if(state==1)
    {
        ui->last->close();
        ui->next->show();
    }
    else if(state==12)
    {
        ui->last->show();
        ui->next->close();
    }
    else
    {
        ui->last->show();
        ui->next->show();
    }
    switch (state) {
    case 1:{ui->main->setStyleSheet(" border-image: url(:/new/pics/resouce/tutorials/t1.png)");break;}
    case 2:{ui->main->setStyleSheet(" border-image: url(:/new/pics/resouce/tutorials/t2.png)");break;}
    case 3:{ui->main->setStyleSheet(" border-image: url(:/new/pics/resouce/tutorials/t3.png)");break;}
    case 4:{ui->main->setStyleSheet(" border-image: url(:/new/pics/resouce/tutorials/t4.png)");break;}
    case 5:{ui->main->setStyleSheet(" border-image: url(:/new/pics/resouce/tutorials/t5.png)");break;}
    case 6:{ui->main->setStyleSheet(" border-image: url(:/new/pics/resouce/tutorials/t6.png)");break;}
    case 7:{ui->main->setStyleSheet(" border-image: url(:/new/pics/resouce/tutorials/t7.png)");break;}
    case 8:{ui->main->setStyleSheet(" border-image: url(:/new/pics/resouce/tutorials/t8.png)");break;}
    case 9:{ui->main->setStyleSheet(" border-image: url(:/new/pics/resouce/tutorials/t9.png)");break;}
    case 10:{ui->main->setStyleSheet(" border-image: url(:/new/pics/resouce/tutorials/t10.png)");break;}
    case 11:{ui->main->setStyleSheet(" border-image: url(:/new/pics/resouce/tutorials/t11.png)");break;}
    case 12:{ui->main->setStyleSheet(" border-image: url(:/new/pics/resouce/tutorials/t12.png)");break;}
    default: break;
    }
    return;
}

void tutor::on_exit_clicked()
{
    close();
}


void tutor::on_last_clicked()
{
    if(state>1)
        --state;
    show_stuff();
}


void tutor::on_next_clicked()
{
    if(state<12)
        ++state;
    show_stuff();
}

