#include "save_and_load.h"
#include "ui_save_and_load.h"
#include"widget.h"
#include"class.h"
#include"qfile"
#include"QSoundEffect"
#include"mainw.h"
#include"buildings.h"

save_and_load::save_and_load(Widget *parent) :
    QWidget(parent),
    ui(new Ui::save_and_load),
    w(parent)
{
    mode=true;
    ui->setupUi(this);
}

save_and_load::save_and_load(Game* g,mainw *parent) :
    QWidget(parent),
    ui(new Ui::save_and_load),
    game(g),
    mw(parent)
{
    mode=false;
    ui->setupUi(this);
}


save_and_load::~save_and_load()
{
    delete ui;
}

void save_and_load::on_exit_clicked()
{
    if(mode==false)
    {
        close();
        delete this;
    }
    else
    close();
}
void save_and_load::showits()
{
    int y,m,d,h,min;
    QLabel* l;
    for(int i=1;i<=3;++i)
    {
        if(i==1) l=ui->l1;
        if(i==2) l=ui->l2;
        if(i==3) l=ui->l3;
    QFile file(QString::fromUtf8("save"+to_string(i)+".txt"));
    if(!file.exists())
    {
        l->setText(tr("空"));
        continue;
    }
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    in>>y;
    in>>m;
    in>>d;
    in>>h;
    in>>min;
    QString tep;
    tep=QString::fromUtf8(to_string(y))+tr("年")+QString::fromUtf8(to_string(m))+tr("月")+QString::fromUtf8(to_string(d))+tr("日");
    if(h<10)
    {
        tep+=' '+QString::fromUtf8(to_string(0))+QString::fromUtf8(to_string(h))+':';
    }
    else
    {
        tep+=' '+QString::fromUtf8(to_string(h))+':';
    }
    if(min<10)
    {
        tep+=QString::fromUtf8(to_string(0))+QString::fromUtf8(to_string(min));
    }
    else
    {
        tep+=QString::fromUtf8(to_string(min));
    }
    l->setText(tep);
    }

}


void save_and_load::on_p1_clicked()
{
    if(mode)
    {
    QFile file(QString::fromUtf8("save"+to_string(1)+".txt"));
    if(!file.exists())
    {
        return;
    }
    w->sound->stop();
    mainw *win=new mainw(w,w->width(),w->height());
    win->showFullScreen();
    win->init_();
    win->game->load(1);
    win->showitems();
    win->back->play();
    win->b->goto_build(0);
    w->close();
    this->close();
    }
    else
    {
    qDebug()<<"first";
    mw->game->save(1);
    qDebug()<<"second";
    showits();
    }
}


void save_and_load::on_p2_clicked()
{
    if(mode)
    {
    QFile file(QString::fromUtf8("save"+to_string(2)+".txt"));
    if(!file.exists())
    {
        return;
    }
    w->sound->stop();
    mainw *win=new mainw(w,w->width(),w->height());
    win->showFullScreen();
    win->init_();
    win->game->load(2);
    win->showitems();
    win->back->play();
    w->close();
    this->close();
    }
    else
    {
    mw->game->save(2);
    showits();
    }

}


void save_and_load::on_p3_clicked()
{
    if(mode)
    {
    QFile file(QString::fromUtf8("save"+to_string(3)+".txt"));
    if(!file.exists())
    {
        return;
    }
    w->sound->stop();
    mainw *win=new mainw(w,w->width(),w->height());
    win->show();
    win->init_();
    win->game->load(3);
    win->showitems();
    win->back->play();
    w->close();
    this->close();
    }
    else
    {
    mw->game->save(3);
    showits();
    }
}

