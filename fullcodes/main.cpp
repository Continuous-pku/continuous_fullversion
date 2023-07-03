
#include "widget.h"
#include <QApplication>
#include"video.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    //mainw m;

    video* v=new video(0,&w);
    v->player->play();
    v->showFullScreen();
    w.showFullScreen();
    v->raise();

    return a.exec();
}
