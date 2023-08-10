#include "drawwidget.h"
#include <QtGui>
#include <QPen>
/*实现能够响应鼠标事件进行绘图功能的窗体类 DrawWidget*/
DrawWidget::DrawWidget(QWidget *parent) : QWidget(parent)
{


    setAutoFillBackground(true);  //对窗体背景色的设置
    setPalette(QPalette(Qt::white));
    pix = new QPixmap(size());   //此QPixmap对象用于准备随时接收绘制的内容
    pix->fill(Qt::white);  //填充背景色为白色
    setMinimumSize(600,400);  //设置绘制窗体的最小尺寸

}

//setStyle() 函数接收主窗口传来的线型风格参数， setWidth() 函数接收主窗口传来的线宽参数
//值， setColor() 函数接收主窗口传来的画笔颜色值。
void DrawWidget::setStyle(int s) {

    style = s;
}

void DrawWidget::setWidth(int w){

    weight = w;
}

void DrawWidget::setColor(QColor c) {

    color = c;
}

//重定义鼠标按下事件 mousePressEvent() , 在按下鼠标按键时，记录当前的鼠标位置值startPo
void DrawWidget::mousePressEvent(QMouseEvent *e){

    startPos = e->pos();
}

//重定义鼠标移动事件 mouseMoveEvent()
void DrawWidget::mouseMoveEvent(QMouseEvent *e){

    QPainter *painter = new QPainter;  //新建QPainter对象
    QPen pen;  //新建QPen对象
    pen.setStyle((Qt::PenStyle)style);  //设置画笔的线型， style 表示当前选择的线型是Qt: :PenStyle 枚举数据中的第几个元素。
    pen.setWidth(weight);  //画笔线的宽度
    pen.setColor(color);  //画笔的颜色
    painter->begin(pix);   //: QPixmap 对象为 QPaintDevice 参数绘制。在构造一个 QPainter 对象时，就立即开始对绘画设备进行绘制。
    painter->setPen(pen);  //将QPen对象应用到绘制对象中
    //绘制从startPos到鼠标当前位置的直线
    painter->drawLine(startPos, e->pos());
    painter->end();
    startPos = e->pos();   //更新鼠标当前位置，为下次绘制做准备
    update();   //重绘绘制区窗体

}

//重绘函数 paintEventO完成绘制区窗体的更新工作，只需调用 drawPixmap() 函数将用千接收
//绘制的 QPixmap 对象绘制在绘制区窗体控件上即可。
void DrawWidget::paintEvent(QPaintEvent *){

    QPainter painter(this);
    painter.drawPixmap(QPoint(0,0), *pix);
}

//调整绘制区大小函数 resizeEvent(),在窗体尺寸变化时应及时调整用千绘制的 QPixmap 对象的大小
void DrawWidget::resizeEvent(QResizeEvent *event){

    if(height()>pix->height()||width()>pix->width()){

        QPixmap *newPix = new QPixmap(size());  //创建一个新的QPixmap对象
        newPix->fill(Qt::white);  //填充颜色为白色背景色
        QPainter p(newPix);
        p.drawPixmap(QPoint(0, 0), *pix);  //在newPix中绘制原pix中的内容
        pix = newPix;     //将newPix赋值给pix作为新的绘制图形接收对象
    }

    QWidget::resizeEvent(event);
}

//清除
void DrawWidget::clear(){

    QPixmap *clearPix = new QPixmap(size());
    clearPix->fill(Qt::white);
    pix = clearPix;
    update();

}


