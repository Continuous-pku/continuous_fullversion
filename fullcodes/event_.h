#ifndef EVENT__H
#define EVENT__H

#include <QWidget>

namespace Ui {
class Event_;
}

class Event_ : public QWidget
{
    Q_OBJECT

public:
    explicit Event_(int _idx, QWidget *parent = nullptr);
    ~Event_();
    QStringList txts,re;
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

private slots:
    void on_con_clicked();

private:
    Ui::Event_ *ui;
    int idx;
};

#endif // EVENT__H
