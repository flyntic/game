#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QShortcut>
#include <QTimer>
#include <QPair>

#include <triangle.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget      *ui;
    QGraphicsScene  *scene;     /// Объявляем графическую сцену
    Triangle        *triangle;  /// и треугольник
    QTimer          *timer;     /* Объявляем игровой таймер, благодаря которому
                                 * будет производиться изменения положения объекта на сцене
                                 * При воздействии на него клавишами клавиатуры
                                 * */
    QPair<int,int> pos;
public slots:
   void drawLine(QPair<int,int> pos,QColor color,int width);
};

#endif // WIDGET_H
