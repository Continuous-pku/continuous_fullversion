
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"save_and_load.h"


class tutor;
class QSoundEffect;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget

{
    Q_OBJECT
    friend class save_and_load;

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void paintEvent(QPaintEvent *event);
    void play_bgm();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_released();

    void on_pushButton_3_clicked();


    void on_pushButton_4_clicked();

private:
    Ui::Widget *ui;
    tutor* tut;
    QSoundEffect* sound;
    save_and_load* s;
};

#endif // WIDGET_H
