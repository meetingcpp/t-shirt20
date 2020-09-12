#ifndef PENROSESHAPE_H
#define PENROSESHAPE_H

#include "penrosetiling.h"
#include "pixelgroup.h"

namespace penrose {
class PenroseShape
{
    std::vector<Triangle> placed;
    PixelGroup group;
    PenroseTiling penrosetiling;
public:
    PenroseShape(PixelGroup &&pg);
    void step();
    template<class CB>
    void visit(const CB& cb)const
    {
        for(const auto& p:placed)
            cb(p);
    }
    Point translate(const complex& c)const
    {
        return group.translatePoint(c);
    }
};
}


#endif // PENROSESHAPE_H
