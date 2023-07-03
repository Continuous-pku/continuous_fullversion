#include "event_.h"
#include "ui_event_.h"
#include"QStyleOption"
#include"QPainter"
#include"QMouseEvent"

Event_::Event_(int _idx, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Event_),
    idx(_idx)
{
    ui->setupUi(this);
    QStringList options;
    options<<tr("未名湖边的小情侣")<<tr("未名湖畔好读书")<<tr("第一次全员核酸检测")
           <<tr("图书馆的线上展览")<<tr("难以下咽的饭菜")<<tr("豪华的隔离条件")
           <<tr("有趣的隔离生活")<<tr("坏掉的洗衣机")<<tr("坏掉的空调")
           <<tr("坏掉的热水器")<<tr("一条被和谐的事件")<<tr("树洞上的乡愁")
           <<tr("宿舍楼里的歌剧魅影")<<tr("“鼠鼠”文学的泛滥")
           <<tr("宿舍楼里的争吵")<<tr("难以忍受的呼噜声")
           <<tr("浴室里的十佳")<<tr("宿舍里的自习室")
           <<tr("宿舍里的麻将室")<<tr("和谐的寝室")
           <<tr("健康的睡眠")<<tr("员工开始崩溃")<<tr("基层志愿者短缺")
           <<tr("医疗资源短缺")<<tr("井然有序的防控")<<tr("处分！")
           <<tr("十佳决赛")<<tr("暖气！该死的"
                   "暖气坏了！");

    txts<<tr("未名湖畔，博雅塔下，正是一番风花雪月。只是不知，亲密无间的接触，是否也会带来疾病传播的风险？")
        <<tr("是日也，天朗气清，惠风和畅，正适合携古籍一二，湖畔执卷而读。")
        <<tr("这是什么？棉签？尝一口。")
        <<tr("图书馆致力于提供电子化的资源，今天一场盛大的线上图书展览会开始了。")
        <<tr("啊忒！What hell is it?食堂今天做的是鸭脖吗！！")
        <<tr("隔离的环境真是太好了，真是太棒了！www但是还是很想回家")
        <<tr("隔离的日子能一起跳广场舞(bushi")
        <<tr("浣熊先生的脏衣机又坏了，我的洗衣桶里全是水，蛤蛤蛤！！！（精神状态很稳定）")
        <<tr("祖传的空调遥控板无了，我怎么开空调啊！！！啪嗒！空调坏了，好了这下不用开了，哈哈哈哈哈哈哈哈哈！！！")
        <<tr("开水间变温泉了。。。")
        <<tr("这是碰都不能碰的滑梯")
        <<tr("dz:呜呜呜想回家啦！！！一直呆在寝室里要疯了！！！字母君快出来安慰dz！！！")
        <<tr("是谁在唱歌？冰冷了心窝！球球大神不要再唱歌啦wwww")
        <<tr("鼠鼠我呀，还是找个下水道躲起来吧www")
        <<tr("你们这些人，都是不懂的，你们不懂得我，不懂得我的文学，不懂得我的痛苦，不懂得我的狂喜，不懂得我的狂怒，不懂得我的狂野，不懂得我的狂放，不懂得我的狂傲，不懂得我的狂躁，不懂得我的狂犬病，不懂得我的狂犬病疫苗，不懂得我的狂犬病疫苗接种!")
        <<tr("哼哼哈嘿~呼呼嘿哈~哈哈哼嘿~嘿嘿蛤蛤~")
        <<tr("浴室中回荡着歌声~谁能拔得头筹？")
        <<tr("早八的铃声响起，宿舍里的十佳们都起床了，键盘声也响了起来。")
        <<tr("东风！九筒！！碰！。。。胡了！！！~~~")
        <<tr("天下英雄者，唯各寝室儿子与吾耳！")
        <<tr("S属性大爆发！Sleeping！！！")
        <<tr("***！就这么几个人怎么可能干完这么多事！！！是哪个**排的班！！！")
        <<tr("-没有人愿意来么？-现在有人来才奇怪吧！")
        <<tr("缺这么多药，缺这么多人，缺这么多物资，你让我们拿什么去防控！")
        <<tr("你们做的好样的！！！")
        <<tr("近日，有学生不服从疫情防控规定，私自离开校园……给予警告处分……")
        <<tr("十佳歌手决赛在邱德拔体育馆举行！请pick你最喜欢的校园歌手吧！")
        <<tr("暖气！！！暖气！！！暖气！！！");

    re<<tr("传播风险增加   学生满意度增加")
         <<tr("传播风险增加   学生满意度增加")
       <<tr("没有什么特殊影响")
       <<tr("学生满意度增加")
       <<tr("学生满意度减少")
       <<tr("学生满意度增加")
       <<tr("学生满意度增加")
       <<tr("学生满意度大幅降低！！！")
       <<tr("www一点也不满意！！！")
       <<tr("学生满意度减少")
       <<tr("学生满意度减少")
       <<tr("学生满意度减少")
       <<tr("学生满意度减少")
       <<tr("学生满意度减少")
       <<tr("学生满意度减少")
       <<tr("睡不着！根本睡不着！")
       <<tr("学生满意度增加！")
       <<tr("学生满意度增加")
       <<tr("学生满意度增加")
       <<tr("学生满意度增加")
       <<tr("学生满意度增加")
       <<tr("传播风险增加 学生满意度减少")
       <<tr("传播风险增加 学生满意度减少")
       <<tr("传播风险增加 学生满意度减少")
       <<tr("传播风险减少 学生满意度增加")
       <<tr("传播风险增加 学生满意度减少")
       <<tr("传播风险增加 学生满意度增加")
       <<tr("学生满意度减少");

    ui->title->setText(options[idx]);
    ui->text->setText(txts[idx]);
    ui->result->setText(re[idx]);

    switch(idx)
    {
    case 0:{ui->pic->setStyleSheet(" border-image: url(:/new/pics/resouce/affair/a0.png)");break;}
    case 1:{ui->pic->setStyleSheet(" border-image: url(:/new/pics/resouce/affair/a1.png)");break;}
    case 2:{ui->pic->setStyleSheet(" border-image: url(:/new/pics/resouce/affair/a2.png)");break;}
    case 3:{ui->pic->setStyleSheet(" border-image: url(:/new/pics/resouce/affair/a3.png)");break;}
    case 4:{ui->pic->setStyleSheet(" border-image: url(:/new/pics/resouce/affair/a4.png)");break;}
    case 5:{ui->pic->setStyleSheet(" border-image: url(:/new/pics/resouce/affair/a5.png)");break;}
    case 6:{ui->pic->setStyleSheet(" border-image: url(:/new/pics/resouce/affair/a6.png)");break;}
    case 7:{ui->pic->setStyleSheet(" border-image: url(:/new/pics/resouce/affair/a7.png)");break;}
    case 8:{ui->pic->setStyleSheet(" border-image: url(:/new/pics/resouce/affair/a8.png)");break;}
    case 9:{ui->pic->setStyleSheet(" border-image: url(:/new/pics/resouce/affair/a9.png)");break;}
    case 10:{ui->pic->setStyleSheet(" border-image: url(:/new/pics/resouce/affair/a10.png)");break;}
    case 11:{ui->pic->setStyleSheet(" border-image: url(:/new/pics/resouce/affair/a11.png)");break;}
    case 12:{ui->pic->setStyleSheet(" border-image: url(:/new/pics/resouce/affair/a12.png)");break;}
    case 13:{ui->pic->setStyleSheet(" border-image: url(:/new/pics/resouce/affair/a13.png)");break;}
    case 14:{ui->pic->setStyleSheet(" border-image: url(:/new/pics/resouce/affair/a14.png)");break;}
    case 15:{ui->pic->setStyleSheet(" border-image: url(:/new/pics/resouce/affair/a15.png)");break;}
    case 16:{ui->pic->setStyleSheet(" border-image: url(:/new/pics/resouce/affair/a16.png)");break;}
    case 17:{ui->pic->setStyleSheet(" border-image: url(:/new/pics/resouce/affair/a17.png)");break;}
    case 18:{ui->pic->setStyleSheet(" border-image: url(:/new/pics/resouce/affair/a18.png)");break;}
    case 19:{ui->pic->setStyleSheet(" border-image: url(:/new/pics/resouce/affair/a19.png)");break;}
    case 20:{ui->pic->setStyleSheet(" border-image: url(:/new/pics/resouce/affair/a20.png)");break;}
    case 21:{ui->pic->setStyleSheet(" border-image: url(:/new/pics/resouce/affair/a21.png)");break;}
    case 22:{ui->pic->setStyleSheet(" border-image: url(:/new/pics/resouce/affair/a22.png)");break;}
    case 23:{ui->pic->setStyleSheet(" border-image: url(:/new/pics/resouce/affair/a23.png)");break;}
    case 24:{ui->pic->setStyleSheet(" border-image: url(:/new/pics/resouce/affair/a24.png)");break;}
    case 25:{ui->pic->setStyleSheet(" border-image: url(:/new/pics/resouce/affair/a25.png)");break;}
    case 26:{ui->pic->setStyleSheet(" border-image: url(:/new/pics/resouce/affair/a26.png)");break;}
    case 27:{ui->pic->setStyleSheet(" border-image: url(:/new/pics/resouce/affair/a27.png)");break;}
    }

}

Event_::~Event_()
{
    delete ui;
}

void Event_::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption o;
    o.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
    QWidget::paintEvent(event);
}

void Event_::mousePressEvent(QMouseEvent *event)
{
    QPointF pl=event->globalPosition();
    int x=pl.x(),y=pl.y();
    QRect tep=this->geometry();
    x=x-tep.x();
    y=y-tep.y();

    //qDebug()<<x<<' '<<y;

    if(x>=450&&x<=580&&y>=10&&y<=50)
    {
        close();
        delete this;
    }
    if(x<=0||y<=0||x>=width()||y>=height())
    {
        close();
        delete this;
    }
}

void Event_::on_con_clicked()
{
    close();
    delete this;
}

