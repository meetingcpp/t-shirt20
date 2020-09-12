#ifndef RASTERIZEDSHAPE_H
#define RASTERIZEDSHAPE_H

#include "pixelgroup.h"

namespace cpp20tshirt
{

class RasterizedShape
{
    PixelGroup group;
public:
    RasterizedShape(PixelGroup&& pg);
    void step();
    template<class CB>
    void visit(const CB& cb)const
    {

    }
};

}
#endif // RASTERIZEDSHAPE_H
