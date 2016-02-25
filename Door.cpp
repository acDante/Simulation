 #include "mainwindow.h"
#include<QPixmap>
void Door::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rectangle =boundingRect();
    QBrush brush;
    QPixmap pixmap("F:/Hundred Project/Simulation/door.png");

    if(s==1)
    brush = pixmap;
    if(s==0)
    brush = Qt::white;

    painter->fillRect(rectangle,brush);
}
QRectF Door::boundingRect() const
{
    return QRectF(0,0,72,89);
}

