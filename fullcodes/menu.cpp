#include "menu.h"
#include "ui_menu.h"
#include"QStyleOption"
#include"QPainter"
#include"QMouseEvent"
#include"QDebug"
#include"save_and_load.h"
#include"mainw.h"

menu::menu(mainw *_parent) :
    QWidget(_parent),
    ui(new Ui::menu)
{
    parent=_parent;
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    setGeometry((parent->width()-420)/2,(parent->height()-463)/2,420,463);
}

menu::~menu()
{
    delete ui;
}

void menu::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption o;
    o.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
    QWidget::paintEvent(event);
}

void menu::mousePressEvent(QMouseEvent *event)
{
    QPointF pl=event->globalPosition();
    int x=pl.x(),y=pl.y();
    QRect tep=this->geometry();
    x=x-tep.x();
    y=y-tep.y();

    //qDebug()<<x<<' '<<y;

    if(x<=0||y<=0||x>=width()||y>=height())
    {
        close();
    }
}

void menu::on_pushButton_3_clicked()
{
    close();
}


void menu::on_pushButton_2_clicked()
{
    close();
    parent->close();
    delete this;
}


void menu::on_pushButton_clicked()
{
    save_and_load* sl=new save_and_load(parent->game,parent);
    sl->showits();
    sl->setGeometry((parent->width()-sl->width())/2,(parent->height()-sl->height())/2,sl->width(),sl->height());
    sl->show();
}


void menu::on_exit_clicked()
{
    close();
}

