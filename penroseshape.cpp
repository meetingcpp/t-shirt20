#include "penroseshape.h"

#include <QDebug>
#include <random>
namespace penrose {

PenroseShape::PenroseShape(PixelGroup &&pg):group(std::move(pg))
{
    penrosetiling.setSize(group.getCircumference()+std::rand()%200+300);
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

    auto is_in_group = [this](int x, int y){return group.isInGroup(Point(x,y));};
    auto triangle_in_group = [&is_in_group](const Triangle& t)
    {
        return is_in_group(t.a.real(),t.a.imag()) && is_in_group(t.b.real(),t.b.imag()) && is_in_group(t.c.real(),t.c.imag());
    };

    auto find_fitting_triangle = [this,&triangle_in_group](const Triangle& t)
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
        std::vector<Point> pvec= {{t.a.real(),t.a.imag()},{t.b.real(),t.b.imag()},{t.c.real(),t.c.imag()}};
        auto rect = groupRect(pvec);
        //if(rect.height() > 15 && rect.width() > 20)
        //    return false;
        placed.push_back(t);
        return true;
    };
    penrosetiling.filter(find_fitting_triangle);
    penrosetiling.levelup();
}

}
