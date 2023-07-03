#ifndef NOTE_H
#define NOTE_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QList>
#include"QGraphicsOpacityEffect"

#define TIMER_INTERVAL_MS   25
#define NOTICE_DEF_DELAY_CNT     (1000/TIMER_INTERVAL_MS)
#define TRANSPARENT_MAX_VAL 1.0
#define TRANSPARENT_CUT_VAL 0.1
#define SIZE_SCALE  0.8
#define PATCH_HEIGHT    10

namespace Ui {
class note;
}

class note : public QWidget
{
    Q_OBJECT

public:
    void Note(QWidget *parent, int c, const int delay_ms = 2000);
    void Note(QWidget *parent, QString c, const int delay_ms = 2000);
    explicit note(QWidget *parent = nullptr);
    ~note();
    void paintEvent(QPaintEvent *event);

private:
    void SetMesseage(int c, int delay_ms);
    void SetMesseage(QString c, int delay_ms);
    void ChangeSize();
    QGraphicsOpacityEffect *pOpacityEffect;

public slots:
    void OnTimerTimeout();

private:
    QWidget *mParentPtr;
    QTimer  *mTimerPtr;
    int mTimerCount;
    double mTransparentVal;
    Ui::note *ui;
};

#endif // NOTE_H
