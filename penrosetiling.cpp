#include "penrosetiling.h"

#include <QDebug>

namespace penrose {

bool goToNextLevel(const Triangle& t)
{
    /*double abx = std::abs(t.a.imag() - t.b.imag());
    double aby = std::abs(t.a.real() - t.b.real());
    if(std::abs(abx-aby) < 5)//distance is less then 5 pixel
        return false;*/
    return true;
}

const double goldenratio = (1 + sqrt(5))/2;

void divide(std::vector<Triangle>& sub,const Triangle &t, TilingType tilingtype)
{
    if(tilingtype == TilingType::NORMAL)
    {
        if(t.color == Color::RED)
        {
            //if(goToNextLevel(t))
            {
            auto p = t.a + (t.b-t.a) / goldenratio;
            sub.push_back({Color::RED,t.c,p,t.b});
            sub.push_back({Color::BLUE,p,t.c,t.a});
            }
        }
        else if(t.color == Color::BLUE)
        {
            //if(goToNextLevel(t))
            {
            auto q = t.b + (t.a - t.b) / goldenratio;
            auto r = t.b + (t.c - t.b) / goldenratio;
            sub.push_back({Color::BLUE,r,t.c,t.a});
            sub.push_back({Color::BLUE,q,r,t.b});
            sub.push_back({Color::RED,r,q,t.a});
            }
        }
    }
    else
    {
        if(t.color == Color::RED)
        {
            //if(goToNextLevel(t))
            {
            auto q = t.a + (t.b-t.a) / goldenratio;
            auto r = t.b + (t.c - t.b) / goldenratio;
            sub.push_back({Color::BLUE,r,q,t.b});
            sub.push_back({Color::RED,q,t.a,r});
            sub.push_back({Color::RED,t.c,t.a,r});
            }
        }
        else if(t.color == Color::BLUE)
        {
            //if(goToNextLevel(t))
            {
            auto p = t.c + (t.a - t.c) / goldenratio;
            sub.push_back({Color::BLUE,t.b,p,t.a});
            sub.push_back({Color::RED,p,t.c,t.b});
            }
        }
    }
}

std::vector<Triangle> divide(const Triangle &t,TilingType tilingtype)
{
    std::vector<Triangle> sub;
    divide(sub,t,tilingtype);
    return sub;
}

void PenroseTiling::setSize(double value)
{
    size = value;
}

TilingType PenroseTiling::getTilingtype() const
{
    return tilingtype;
}

void PenroseTiling::setTilingtype(const TilingType &value)
{
    tilingtype = value;
}

PenroseTiling::PenroseTiling(double size):size(size)
{

}

void PenroseTiling::levelup()
{
    std::vector<Triangle> vec;
    for(const auto& t: triangles)
        divide(vec,t,tilingtype);
    triangles = vec;
}

void PenroseTiling::resetTiling()
{
    triangles.clear();
    double pi = M_PI;
    if(tilingtype == TilingType::NORMAL)
    {
        for(int i =0; i < 10; i++)
        {
            Triangle t;
            t.b = std::polar(size,(2*i-1)* pi / 10);
            t.c = std::polar(size,(2*i+1)* pi / 10);
            if(i % 2 == 0)
                std::swap(t.b,t.c);
            t.a = 0i;
            t.color = Color::RED;
            triangles.push_back(t);
        }
    }
    else
    {
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
}

}
