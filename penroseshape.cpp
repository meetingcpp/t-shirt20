#include "penroseshape.h"

#include <QDebug>
#include <QLine>
#include <random>
namespace penrose {

PenroseShape::PenroseShape(PixelGroup &&pg):group(std::move(pg))
{
    penrosetiling.setSize(group.getCircumference()+std::rand()%200+250);
    //auto r = penrosetiling
    penrosetiling.setTilingtype(std::rand()%2?TilingType::NORMAL:TilingType::NORMAL);
    penrosetiling.resetTiling();
}

void PenroseShape::step()
{
    /*auto is_not_in_refrect = [this](const Triangle& t){
        return group.isInRefRect(t);
    };
    penrosetiling.filter(is_not_in_refrect);*/

    /*auto is_in_group = [this](int x, int y){return group.isInGroup(Point(x,y));};
    auto triangle_in_group = [&is_in_group](const Triangle& t)
    {
        return is_in_group(t.a.real(),t.a.imag()) && is_in_group(t.b.real(),t.b.imag()) && is_in_group(t.c.real(),t.c.imag());
    };*/

    auto find_fitting_triangle = [this](const Triangle& t)
    {
        auto vec = divide(t);
        for(const auto& t : vec)
        {
            if(!triangle_in_group(t))
                return false;
        }
        std::vector<Triangle> v;
        for(const auto& t : vec)
        {
            divide(v,t);
            divide(v,t,TilingType::DARTS);
        }
        for(const auto& t : v)
        {
            if(!triangle_in_group(t))
                return false;
        }
        std::vector<Point> pvec= {{static_cast<int>(t.a.real()),static_cast<int>(t.a.imag())},{static_cast<int>(t.b.real()),static_cast<int>(t.b.imag())},{static_cast<int>(t.c.real()),static_cast<int>(t.c.imag())}};
        //auto rect = groupRect(pvec);
        //if(rect.height() > 15 && rect.width() > 20)
        //    return false;
        placed.push_back(t);
        return true;
    };
    penrosetiling.filter(find_fitting_triangle);
    penrosetiling.levelup();
}

bool PenroseShape::is_in_group(int x, int y)
{
    return group.isInGroup(Point(x,y));;
}

bool PenroseShape::triangle_in_group(const Triangle &t)
{
    auto distance = [](auto a, auto b){
        Point pa(a.real(),a.imag()),pb(b.real(),b.imag());
        QLine l(pa,pb);
        return l.dx() < 10 && l.dy() < 10;
    };
    return distance(t.a,t.c) && is_in_group(t.a.real(),t.a.imag()) && is_in_group(t.b.real(),t.b.imag()) && is_in_group(t.c.real(),t.c.imag());
}

}
