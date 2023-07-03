#include "note.h"
#include "ui_note.h"
#include"QStyleOption"
#include"QPainter"

note::note(QWidget *parent) :
    QWidget(parent)
    ,mParentPtr(parent)
    , mTimerPtr(nullptr)
    , mTimerCount(NOTICE_DEF_DELAY_CNT)
    ,ui(new Ui::note)
{
    ui->setupUi(this);
    mTimerPtr = new QTimer();
    setGeometry((parent->width()-275)/2,(parent->height()-132)/2,275,132);
    connect(mTimerPtr, SIGNAL(timeout()), this, SLOT(OnTimerTimeout()), Qt::UniqueConnection);
    pOpacityEffect = new QGraphicsOpacityEffect(this);
}

note::~note()
{
    if (mTimerPtr->isActive()) {
        mTimerPtr->stop();
    }
    delete mTimerPtr;
    delete ui;
    deleteLater();
}

void note::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption o;
    o.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
    QWidget::paintEvent(event);
}

void note::OnTimerTimeout()
{
    --mTimerCount;

    if (0 < mTimerCount) {
        //最后1s开始渐变消失
        if (mTimerCount <= 10 && 0 < mTransparentVal) {
            mTransparentVal -= 0.1;
            if (0 > mTransparentVal) {
                mTransparentVal = 0;
            }
            //控制透明度
            //qDebug()<<mTransparentVal;
            pOpacityEffect->setOpacity(mTransparentVal);
            this->setGraphicsEffect(pOpacityEffect);
        }
    }
    else{
        //显示结束
        mTimerPtr->stop();
        close();
    }
}

void note::SetMesseage(int c, int delay_ms)
{
    ui->num->setText(QString::fromUtf8(std::to_string(c)));
    qDebug()<<"HERE";
    mTimerCount = delay_ms/TIMER_INTERVAL_MS + 1;//延时计数计算
    mTransparentVal = TRANSPARENT_MAX_VAL;
}

void note::SetMesseage(QString c, int delay_ms)
{
    ui->num->setText(c);
    qDebug()<<"HERE";
    mTimerCount = delay_ms/TIMER_INTERVAL_MS + 1;//延时计数计算
    mTransparentVal = TRANSPARENT_MAX_VAL;

}

void note::Note(QWidget *parent, int c, const int delay_ms)
{
    if (mTimerPtr->isActive()) {
        mTimerPtr->stop();
    }

    setParent(parent);
    SetMesseage(c, delay_ms);
    mTimerPtr->start(TIMER_INTERVAL_MS);//开始计数
    //show();
}

void note::Note(QWidget *parent, QString c, const int delay_ms)
{
    if (mTimerPtr->isActive()) {
        mTimerPtr->stop();
    }

    setParent(parent);
    SetMesseage(c, delay_ms);
    mTimerPtr->start(TIMER_INTERVAL_MS);//开始计数
    //show();
}
