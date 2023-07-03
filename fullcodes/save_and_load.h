#ifndef SAVE_AND_LOAD_H
#define SAVE_AND_LOAD_H

#include <QWidget>
class Game;
class Widget;
class mainw;

namespace Ui {
class save_and_load;
}

class save_and_load : public QWidget
{
    Q_OBJECT

public:
    explicit save_and_load(Game* g,mainw *parent = nullptr);
    explicit save_and_load(Widget *parent = nullptr);
    ~save_and_load();
    void showits();

private slots:
    void on_exit_clicked();

    void on_p1_clicked();

    void on_p2_clicked();

    void on_p3_clicked();

private:
    Ui::save_and_load *ui;
    Game*game;
    Widget* w;
    mainw* mw;
    bool mode;//mode==false->save mode==true->load
};

#endif // SAVE_AND_LOAD_H
