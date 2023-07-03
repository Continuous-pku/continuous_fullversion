#ifndef BUILDINGS_H
#define BUILDINGS_H

#include <QWidget>
#include"class.h"
#include"build_info.h"

class QTreeWidgetItem;
class mainw;
class QSoundEffect;

namespace Ui {
class buildings;
}

class buildings : public QWidget
{
    Q_OBJECT

public:
    explicit buildings(Game* game, mainw *parent = nullptr);
    ~buildings();
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    QPushButton *pob[4],po1,po2,po3,po4;
    Policy *po[10];
    void show_policy_up(Building * b,int i);
    void goto_build(int i);
    Game* g;
    mainw* _parent;
    QStringList options;
    build_info info;

private slots:
    void on_treeWidget_itemPressed(QTreeWidgetItem *item, int column);

    void on_pushButton_clicked();
    void po1_clicked();
    void po2_clicked();
    void po3_clicked();
    void po4_clicked();

    void on_level_up_clicked();

private:
    bool outl=false;
    Ui::buildings *ui;

    Building* ptr;
    void seti(Building* b);
    void set_level(int i);
    void show_buttons(Building *b);
    void show_info();

    QStringList ops;
    QLabel a[4];
    QSoundEffect* sound;
};

#endif // BUILDINGS_H
