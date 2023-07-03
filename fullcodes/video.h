#include<QMediaPlayer>
#include<QVideoWidget>
#include <QMouseEvent>
#include<QKeyEvent>
//#include<QMediaPlaylist>
#include<QPushButton>
#ifndef VIDEO_H
#define VIDEO_H


#include <QWidget>
#include<widget.h>

class QMediaPlayer;
class QVideoWidget;

class video : public QVideoWidget
{
public:
    video(int s,Widget* p=NULL);
    QMediaPlayer *player;
    int state;
    QPushButton *button;
protected:
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *ev);
private:
    Widget* parent;

private slots:
    void endofv();
    void cls();
signals:

};

#endif // VIDEO_H
