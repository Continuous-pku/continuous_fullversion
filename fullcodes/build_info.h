#ifndef BUILD_INFO_H
#define BUILD_INFO_H

#include <QWidget>
#include"class.h"
#include"QStyleOption"
#include"QPainter"

namespace Ui {
class build_info;
}

class build_info : public QWidget
{
    Q_OBJECT

public:
    explicit build_info(QWidget *parent = nullptr);
    Building *b;
    ~build_info();
    void show_p(int idx,QString name,int cost);
    void show_i();
    void paintEvent(QPaintEvent *event);

private:
    Ui::build_info *ui;
    QLabel l[5];
};

#endif // BUILD_INFO_H
