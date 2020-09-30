#ifndef RASTERIZEDSHAPE_H
#define RASTERIZEDSHAPE_H

#include "pixelgroup.h"

namespace cpp20tshirt
{

class RasterizedShape
{
    PixelGroup group;
    std::vector<Point> anchors;
    int rectsize = 8;
    int gap = 3;
public:
    RasterizedShape(PixelGroup&& pg);
    void step();
    template<class CB>
    void visit(const CB& cb)const
    {
        for(const auto& p:anchors)
            cb(p);
    }
    int getRectsize() const;
    int getGap() const;
};

}
#endif // RASTERIZEDSHAPE_H
