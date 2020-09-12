#include "penrosecanvas.h"
#include <QPainterPath>
#include <QPainter>
#define _USE_MATH_DEFINES
#include <cmath>

#include <QDebug>

const double goldenratio = (1 + sqrt(5))/2;

void divide(std::vector<Triangle>& sub,const Triangle &t)
{
    if(false && std::rand()%2==0)
    {
    if(t.color == Color::RED)
    {
        auto p = t.a + (t.b-t.a) / goldenratio;
        sub.push_back({Color::RED,t.c,p,t.b});
        sub.push_back({Color::BLUE,p,t.c,t.a});
    }
    else if(t.color == Color::BLUE)
    {
        auto q = t.b + (t.a - t.b) / goldenratio;
        auto r = t.b + (t.c - t.b) / goldenratio;
        sub.push_back({Color::BLUE,r,t.c,t.a});
        sub.push_back({Color::BLUE,q,r,t.b});
        sub.push_back({Color::RED,r,q,t.a});
    }
    }
    else
    {
    if(t.color == Color::RED)
    {
        auto q = t.a + (t.b-t.a) / goldenratio;
        auto r = t.b + (t.c - t.b) / goldenratio;
        sub.push_back({Color::BLUE,r,q,t.b});
        sub.push_back({Color::RED,q,t.a,r});
        sub.push_back({Color::RED,t.c,t.a,r});
    }
    else if(t.color == Color::BLUE)
    {
        auto p = t.c + (t.a - t.c) / goldenratio;
        sub.push_back({Color::BLUE,t.b,p,t.a});
        sub.push_back({Color::RED,p,t.c,t.b});
    }
    }
}


PenroseCanvas::PenroseCanvas(QWidget *parent) : QWidget(parent)
{

}

void PenroseCanvas::resetTiling()
{
    triangles.clear();
    double pi = M_PI;
    int h = rect().height(),w = rect().width();
    double size = std::sqrt(h*h + w*w);
    qDebug() << h << w << size;
    for(int i =0; i < 10; i++)
    {
        Triangle t;
        t.a = std::polar(size,(2*i-1)* pi / 10);
        t.c = std::polar(size,(2*i+1)* pi / 10);
        if(i % 2 == 0)
            std::swap(t.a,t.c);
        t.b = 0i;
        t.color = Color::RED;
        triangles.push_back(t);
    }
}

void PenroseCanvas::levelup()
{
    std::vector<Triangle> vec;
    for(const auto& t: triangles)
        divide(vec,t);
    triangles = vec;
}

void PenroseCanvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(painter.window().center());
    QPainterPath path;
    painter.setPen(Qt::NoPen);
    for(const auto& t: triangles)
    {
        if(t.color == Color::RED)
            addTriangleToPath(path,t);
    }
    painter.fillPath(path,QBrush{QColor{Qt::red}});
    path= QPainterPath{};
    for(const auto& t: triangles)
    {
        if(t.color == Color::BLUE)
            addTriangleToPath(path,t);
    }
    painter.fillPath(path,QBrush{QColor{Qt::blue}});
    path = QPainterPath{};
    for(const auto& t: triangles)
    {
        path.moveTo(t.c.real(),t.c.imag());
        path.lineTo(t.a.real(),t.a.imag());
        path.lineTo(t.b.real(),t.b.imag());
    }
    painter.strokePath(path,QPen(QBrush{QColor{Qt::black}},0.5));
}

void PenroseCanvas::addTriangleToPath(QPainterPath &path, const Triangle &t)
{
    path.moveTo(t.a.real(),t.a.imag());
    path.lineTo(t.b.real(), t.b.imag());
    path.lineTo(t.c.real(),t.c.imag());
    path.closeSubpath();
}


