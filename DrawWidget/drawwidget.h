#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>
#include <QtGui>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QColor>
#include <QPixmap>
#include <QPoint>
#include <QPainter>
#include <QPalette>


/*类声明中对鼠标事件 mousePressEvent() mouseMoveEvent()
重绘事件paintEvent() 、尺寸变化事件 resizeEvent() 进行了重定义。 setStyle() setWidth() setColor()
函数主要用千为主窗口传递各种与绘图有关的参数。*/
class DrawWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DrawWidget(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);

signals:

public slots:
    void setStyle(int);
    void setWidth(int);
    void setColor(QColor);
    void clear();


private:
    QPixmap *pix;
    QPoint startPos;
    QPoint endPos;
    int style;
    int weight;
    QColor color;


};

#endif // DRAWWIDGET_H
