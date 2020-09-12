#include "canvas.h"

#include <QPainter>

void Canvas::setDopaint(const paintcb &value)
{
    dopaint = value;
}

const Canvas::paintcb &Canvas::getDopaint() const
{
    return dopaint;
}

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{

}

void Canvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(dopaint)
        dopaint(painter);
}
