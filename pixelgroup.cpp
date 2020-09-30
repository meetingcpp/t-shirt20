#include "pixelgroup.h"
#include <utility>
#include <tuple>

#include <QDebug>
int PixelGroup::getXoff() const
{
    return xoff;
}

int PixelGroup::getYoff() const
{
    return yoff;
}

Point PixelGroup::getRefpoint() const
{
    return refpoint;
}

Rect PixelGroup::getRefrect() const
{
    return refrect;
}

PixelGroup::PixelGroup(const pixelgroup &pg):group(pg)
{
    std::sort(group.begin(),group.end());
    refrect = groupRect(group);
    refpoint = refrect.topLeft();
    xoff = refrect.width()/2;
    yoff = refrect.height()/2;
}

bool PixelGroup::isInGroup(const Point& p)
{
    Point p1(p.x() + xoff+refpoint.x(),p.y()+yoff+refpoint.y());
   // qDebug() << p << p1;
    //auto it = std::lower_bound(group.begin(),group.end(),p1);
    //return refrect.contains(p1) && std::find(group.begin(),group.end(),p1)!= group.end();

    return std::binary_search(group.begin(),group.end(),p1);
}

bool PixelGroup::isLocalPointInGroup(const Point &p)
{
    Point p1(p.x() +refpoint.x(),p.y()+refpoint.y());
    return std::binary_search(group.begin(),group.end(),p1);
}

bool PixelGroup::isInRefRect(const penrose::Triangle &t)
{
    std::vector<Point> pvec= {{static_cast<int>(t.a.real()),static_cast<int>(t.a.imag())},{static_cast<int>(t.b.real()),static_cast<int>(t.b.imag())},{static_cast<int>(t.c.real()),static_cast<int>(t.c.imag())}};
    return refrect.contains(groupRect(pvec));
}

double PixelGroup::getCircumference() const
{
    QRect r = groupRect(group);
    int h = r.height();
    int w = r.width();
    return std::sqrt(h*h + w*w);
}

Rect groupRect(const pixelgroup &pg)
{
    auto xc = [](const Point& p1, const Point& p2){return p1.x() < p2.x();};
    auto yc = [](const Point& p1, const Point& p2){return p1.y() < p2.y();};
    auto xmax = std::max_element(pg.begin(),pg.end(),xc);
    auto xmin = std::min_element(pg.begin(),pg.end(),xc);
    auto ymax = std::max_element(pg.begin(),pg.end(),yc);
    auto ymin = std::min_element(pg.begin(),pg.end(),yc);
    return Rect(Point(xmin->x(),ymin->y()),Point(xmax->x(),ymax->y()));
}


bool operator<(const Point &p1, const Point &p2)
{
    //return std::tie( p1.x(), p1.y() ) < std::tie( p2.x(), p2.y() );
    ///*
    using namespace std::rel_ops;
    //auto pval = [](const auto& p){return p.x() *100000 + p.y();};
    auto pa1 = std::make_pair( p1.x(), p1.y());
    auto pa2 = std::make_pair( p2.x(), p2.y());
    return pa1 < pa2;
    //return pval(p1) < pval(p2);//*/
}
