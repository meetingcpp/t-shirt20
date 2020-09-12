#ifndef PENROSETILING_H
#define PENROSETILING_H

#include <vector>
#include <algorithm>
#include <complex>

namespace penrose {

using complex = std::complex<double>;

enum class TilingType{NORMAL,DARTS};

enum class Color{RED,BLUE};
struct Triangle
{
    Color color;
    complex a,b,c;
};

void divide(std::vector<Triangle>& sub, const Triangle &t, TilingType tilingtype=TilingType::NORMAL);

std::vector<Triangle> divide(const Triangle &t,TilingType tilingtype=TilingType::NORMAL);

class PenroseTiling
{
protected:
    std::vector<Triangle> triangles;
    double size = 100.0;
    TilingType tilingtype = TilingType::NORMAL;
public:
    PenroseTiling(double size = 100.0);
    void levelup();
    void resetTiling();
    template<class CB>
    void visitTriangles(const CB& cb)
    {
        for(const auto& t: triangles)
            cb(t);
    }
    template<class CB>
    void filter(const CB& cb)
    {
        auto it = std::remove_if(triangles.begin(),triangles.end(),cb);
        triangles.erase(it,triangles.end());
    }

    void setSize(double value);
    TilingType getTilingtype() const;
    void setTilingtype(const TilingType &value);
    //size_t size()const{return triangles.size();}
};

}

#endif // PENROSETILING_H
