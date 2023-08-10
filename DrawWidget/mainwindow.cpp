#include "mainwindow.h"
#include <QToolBar>
#include <QColorDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    drawWidget = new DrawWidget;  //新建对象
    setCentralWidget(drawWidget);  //新建的对象作为主窗口的中央窗体
    createToolBar();    //实现一个工具栏
    setMinimumSize(600, 400); //主窗口最小尺寸
    ShowStyle();  //初始化线型，设置控件中的当前值作为初始值
    drawWidget->setWidth(widthSpinBox->value());  //初始化线宽
    drawWidget->setColor(Qt::black);  //初始化颜色
}

//工具栏
void MainWindow::createToolBar(){

    QToolBar *toolBar = addToolBar("Tool");  //为主窗口新建一个工具栏对象
    styleLabel = new QLabel(tr("线型风格："));  //创建线型风格选择控件
    styleComboBox = new QComboBox;
    styleComboBox->addItem(tr("SolidLine"),
                           static_cast<int>(Qt::SolidLine));
    styleComboBox->addItem(tr("DashLine"),
                           static_cast<int>(Qt::DashLine));
    styleComboBox->addItem(tr("DotLine"),
                           static_cast<int>(Qt::DotLine));
    styleComboBox->addItem(tr("DashDotLine"),
                           static_cast<int>(Qt::DashDotLine));
    styleComboBox->addItem(tr("DashDotDotLine"),
                           static_cast<int>(Qt::DashDotDotLine));
    connect(styleComboBox, SIGNAL(activated(int)), this, SLOT(ShowStyle()));


    widthLabel = new QLabel(tr("线宽："));  //创建线宽选择控件
    widthSpinBox = new QSpinBox;
    connect(widthSpinBox, SIGNAL(valueChanged(int)), drawWidget, SLOT(setWidth(int)));

    colorBtn = new QToolButton;   //创建颜色选择控件
    QPixmap pixmap(20,20);
    pixmap.fill(Qt::black);
    colorBtn->setIcon(QIcon(pixmap));
    connect(colorBtn, SIGNAL(clicked()), this, SLOT(ShowColor()));

    clearBtn = new QToolButton;  //创建"清除"按钮
    clearBtn->setText(tr("清除"));
    connect(clearBtn, SIGNAL(clicked()), drawWidget, SLOT(clear()));

    toolBar->addWidget(styleLabel);
    toolBar->addWidget(styleComboBox);
    toolBar->addWidget(widthLabel);
    toolBar->addWidget(widthSpinBox);
    toolBar->addWidget(colorBtn);
    toolBar->addWidget(clearBtn);


}

//变线型参数的槽函数 ShowStyle(), 通过调用 DrawWidget 类的 setStyle() 函数将当前线型
//选择控件中的线型参数传给绘制区
void MainWindow::ShowStyle(){

    drawWidget->setStyle(styleComboBox->itemData(
                             styleComboBox->currentIndex(), Qt::UserRole).toInt());
}

//设置画笔颜色的槽函数 ShowColor(), 通过调用 DrawWidget 类的 setColor() 函数将用户在标准颜色对话框中选择的颜色值传给绘制
void MainWindow::ShowColor(){

    QColor color = QColorDialog::getColor(static_cast<int> (Qt::black), this);
    //使用标准颜色对话框获得一个颜色值
    if(color.isValid()){
        //将新选的颜色传给绘制区，用于改变画笔的颜色
        drawWidget->setColor(color);
        QPixmap p(20,20);
        p.fill(color);
        colorBtn->setIcon(QIcon(p));  //更新颜色选择按钮上的颜色显示
    }
}

MainWindow::~MainWindow()
{
}

