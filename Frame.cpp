#include "mainwindow.h"
#include<QPixmap>
void Frame::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rectangle =boundingRect();
    QBrush brush;
    QPixmap pixmap("F:/Hundred Project/Simulation/frame.png");
    brush = pixmap;

    painter->fillRect(rectangle,brush);
}
QRectF Frame::boundingRect() const
{
    return QRectF(0,0,110,101);
}
