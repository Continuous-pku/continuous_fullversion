#include "pchoice.h"
#include "ui_pchoice.h"
#include"QStyleOption"
#include"QPainter"
#include"QMouseEvent"
#include"policy.h"
#include"note.h"


pchoice::pchoice(policy *parent) :
    QWidget(parent),
    ui(new Ui::pchoice)
{
    parent_=parent;
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    ops<<tr("开展全员核酸检测")<<tr("进行病毒研究专项")<<tr("暂停校园参观")<<tr("错峰开学")<<tr("提供视频会议软件")<<tr("开始网课")<<tr("实行P/F制");
    texts<<tr("  进行一次核酸检测，每天都可以进行一次，可以得到当天感染人数的数据，并且可以在当天发现更多病例拉去隔离。但是把大家聚集在一起会不会增加感染的风险？")
        <<tr("  对病毒进行专项研究，用科学手段战胜病毒！进行一段时间的科研攻关，科研项目完成后，大幅度提高感染者治愈率。")
          <<tr("  关闭校园参观渠道，全方位提高校园内所有建筑的疫情防控水平。")
          <<tr("  实行错峰开学制度，全方位降低校园内的病毒感染概率")
          <<tr("  为学生提供视频会议软件，提高学生满意度，同时为网课的进行做好铺垫。")
          <<tr("  开始全面进行网课，学生满意度提高，同时降低学生（尤其在教学楼中）的感染概率")
          <<tr("  实行自选P/F制，因为疫情而学习受到影响（开始摆烂）的鼠鼠有救了！学生满意度大幅上升。");
}

pchoice::~pchoice()
{
    delete ui;
}


void pchoice::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption o;
    o.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
    QWidget::paintEvent(event);
}

void pchoice::on_exit_clicked()
{
    this->close();
}

void pchoice::set_items(Policy* pol)
{
    p=pol;
    ui->title->setText(ops[p->idx-10]);
    ui->txt->setText(texts[p->idx-10]);
    ui->act_cost->setText(QString::fromUtf8(to_string(p->cost)));
    switch(p->idx-10)
    {
    case 0:{ui->picture->setStyleSheet(" border-image: url(:/new/pics/resouce/policis/pictures/hesuan.png)");
        if(!p->available())
            ui->take_effect->setText(tr("今日已经启用"));
        else
            ui->take_effect->setText(tr("启用政策"));
        break;

    }
    case 1:{ui->picture->setStyleSheet(" border-image: url(:/new/pics/resouce/policis/pictures/keyan.png)");
        if(!p->available())
            ui->take_effect->setText(tr("正在进行中"));
        else
            ui->take_effect->setText(tr("启用政策"));
        break;

    }
    case 2:{ui->picture->setStyleSheet(" border-image: url(:/new/pics/resouce/policis/pictures/canguan.png)");
        if(!p->available())
            ui->take_effect->setText(tr("已启用"));
        else
            ui->take_effect->setText(tr("启用政策"));
        break;

    }
    case 3:{ui->picture->setStyleSheet(" border-image: url(:/new/pics/resouce/policis/pictures/kaixue.png)");
        if(!p->available())
            ui->take_effect->setText(tr("已启用"));
        else
            ui->take_effect->setText(tr("启用政策"));
        break;

    }
    case 4:{ui->picture->setStyleSheet(" border-image: url(:/new/pics/resouce/policis/pictures/shipin.png)");
        if(!p->available())
            ui->take_effect->setText(tr("已启用"));
        else
            ui->take_effect->setText(tr("启用政策"));
        break;

    }
    case 5:{ui->picture->setStyleSheet(" border-image: url(:/new/pics/resouce/policis/pictures/wangke.png)");
        if(!p->available())
            ui->take_effect->setText(tr("已启用"));
        else
            ui->take_effect->setText(tr("启用政策"));
        break;

    }
    case 6:{ui->picture->setStyleSheet(" border-image: url(:/new/pics/resouce/policis/pictures/pf.png)");
        if(!p->available())
            ui->take_effect->setText(tr("已启用"));
        else
            ui->take_effect->setText(tr("启用政策"));
        break;

    }
    default:{break;}
    }
    return;
}

void pchoice::on_take_effect_clicked()
{
    if(p->available()&&p->cost<=parent_->p->game->getap())
        p->takeEffect();
    else
    {
        if(p->cost>=parent_->p->game->getap())
        {
            note* n=new note(this);
            n->Note(this,p->cost,500);
            n->show();
        }
        return;
    }
    if(p->idx==10)
        ui->take_effect->setText(tr("今日已经启用"));
    else if(p->idx==11)
        ui->take_effect->setText(tr("正在进行中"));
    else
        ui->take_effect->setText(tr("政策已颁布"));
    parent_->showits();
}

