#ifndef PIXELGROUP_H
#define PIXELGROUP_H
#include <QPoint>
#include <QRect>

#include <deque>

#include "penrosetiling.h"

using Point = QPoint;
using Rect = QRect;
using pixelgroup = std::vector<Point>;

Rect groupRect(const pixelgroup& pg);

bool operator<(const Point& p1, const Point& p2);

class PixelGroup
{
    pixelgroup group;
    Point refpoint;
    Rect refrect;
    int xoff,yoff;
public:
    PixelGroup(const pixelgroup& pg);
    bool isInGroup(const Point &p);
    bool isLocalPointInGroup(const Point &p);
    bool isInRefRect(const penrose::Triangle &t);
    double getCircumference() const;
    auto begin()const{return group.cbegin();}
    auto end()const {return group.cend();}
    int getXoff() const;
    int getYoff() const;
    Point getRefpoint() const;
    template<class complex>
    Point translatePoint(const complex& p)const
    {
        return Point(p.real()+xoff+refpoint.x(),p.imag()+yoff + refpoint.y());
    }
    Point translatePoint(Point& p)const
    {
        return Point(p.x()+refpoint.x(),p.y() + refpoint.y());
    }
    Rect getRefrect() const;
};

#endif // PIXELGROUP_H
