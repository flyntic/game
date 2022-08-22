#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    pos= QPair<int,int>(0,0);
    ui->setupUi(this);
    this->resize(600,600);          /// Задаем размеры виджета, то есть окна
    this->setFixedSize(600,600);    /// Фиксируем размеры виджета

    scene = new QGraphicsScene();   /// Инициализируем графическую сцену
    triangle = new Triangle();      /// Инициализируем треугольник

    ui->graphicsView->setScene(scene);  /// Устанавливаем графическую сцену в graphicsView
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    /// Устанавливаем сглаживание
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по вертикали
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по горизонтали

    scene->setSceneRect(-250,-250,500,500); /// Устанавливаем область графической сцены

    scene->addLine(-250,0,250,0,QPen(Qt::black));   /// Добавляем горизонтальную линию через центр
    scene->addLine(0,-250,0,250,QPen(Qt::black));   /// Добавляем вертикальную линию через центр

    /* Дополнительно нарисуем органичение территории в графической сцене */
    scene->addLine(-250,-250, 250,-250, QPen(Qt::black));
    scene->addLine(-250, 250, 250, 250, QPen(Qt::black));
    scene->addLine(-250,-250,-250, 250, QPen(Qt::black));
    scene->addLine( 250,-250, 250, 250, QPen(Qt::black));

    scene->addItem(triangle);   /// Добавляем на сцену треугольник
    triangle->setPos(0,0);      /// Устанавливаем треугольник в центр сцены

    /* Инициализируем таймер и вызываем слот обработки сигнала таймера
     * у Треугольника 20 раз в секунду.
     * Управляя скоростью отсчётов, соответственно управляем скоростью
     * изменения состояния графической сцены
     * */
    timer = new QTimer();
    connect(timer, &QTimer::timeout, triangle, &Triangle::slotGameTimer);
    timer->start(1000 / 50);

    connect(triangle, &Triangle::TriangleMoved, this, &Widget::drawLine);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::drawLine(QPair<int, int> pos_new,QColor color,int width)
{
    scene->addLine(pos.first,pos.second,pos_new.first,pos_new.second,QPen(QBrush(color),width));
    pos=pos_new;
}

