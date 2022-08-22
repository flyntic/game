#include "triangle.h"

#include <algorithm>

Triangle::Triangle(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    angle = 0;     // Задаём угол поворота графического объекта
    setRotation(angle);     // Устанавилваем угол поворота графического объекта
}

Triangle::~Triangle()
{

}

QRectF Triangle::boundingRect() const
{
    return QRectF(-25,-40,50,80);   /// Ограничиваем область, в которой лежит треугольник
}

void Triangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
        QPolygon polygon;   /// Используем класс полигона, чтобы отрисовать треугольник
        /// Помещаем координаты точек в полигональную модель
        if (countAngles==3)
          polygon << QPoint(0,-40) << QPoint(25,40) << QPoint(-25,40);
        else
            polygon << QPoint(25,-40) << QPoint(25,40) << QPoint(-25,40)<< QPoint(-25,-40);
        painter->setBrush(Qt::red);     /// Устанавливаем кисть, которой будем отрисовывать объект
        painter->drawPolygon(polygon);  /// Рисуем треугольник по полигональной модели
        Q_UNUSED(option);
        Q_UNUSED(widget);
}

void Triangle::slotGameTimer()
{   QColor color=QColor(0,0,0);
    static int width=0;
    /* Поочерёдно выполняем проверку на нажатие клавиш
     * с помощью функции асинхронного получения состояния клавиш,
     * которая предоставляется WinAPI
     * */
    if ((width++)>10) width=1;
    int k = (int)(std::min((int)std::abs(angle) % 360, 360 - (int)std::abs(angle) % 360) * 255 / 180);
    color=QColor(255,k,k);

    if(GetAsyncKeyState(VK_LEFT)){
        angle -= 10;        // Задаём поворот на 10 градусов влево
        setRotation(angle); // Поворачиваем объект
    }
    if(GetAsyncKeyState(VK_RIGHT)){
        angle += 10;        // Задаём поворот на 10 градусов вправо
        setRotation(angle); // Поворачиваем объект
    }
    if(GetAsyncKeyState(VK_UP)){
        setPos(mapToParent(0, -5));     /* Продвигаем объект на 5 пискселей вперёд
                                         * перетранслировав их в координатную систему
                                         * графической сцены
                                         * */

        unCountAngles();
      //  color=QColor("green");
    }
    if(GetAsyncKeyState(VK_DOWN)){
        setPos(mapToParent(0, 5));      /* Продвигаем объект на 5 пискселей назад
                                         * перетранслировав их в координатную систему
                                         * графической сцены
                                         * */
     //   color=QColor("yellow");

        unCountAngles();
    }

    /* Проверка выхода за границы поля
     * Если объект выходит за заданные границы, то возвращаем его назад
     * */
    if(this->x() - 10 < -250){
        this->setX(0);
        this->setY(0);
        //this->setX(-240);       // слева
    }
    if(this->x() + 10 > 250){
        this->setX(0);
        this->setY(0);

 //       this->setX(240);        // справа
    }

    if(this->y() - 10 < -250){
        this->setX(0);
        this->setY(0);
//        this->setY(-240);       // сверху
    }
    if(this->y() + 10 > 250){
        this->setX(0);
        this->setY(0);
//        this->setY(240);        // снизу
    }

    emit TriangleMoved(QPair<int,int>(this->x(),this->y()),color,width);
}

void Triangle::unCountAngles()
{
    countAngles=(countAngles==3)?4:3;
}
