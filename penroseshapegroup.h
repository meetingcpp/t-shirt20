#ifndef PENROSESHAPEGROUP_H
#define PENROSESHAPEGROUP_H

#include "penroseshape.h"


namespace penrose {

class PenroseShapeGroup
{
    std::vector<penrose::PenroseShape> group;
public:
    PenroseShapeGroup();
    void addShape(PenroseShape &&ps);
    void step();
    template<class CB>
    void visit(const CB& cb)const
    {
        for(const auto& ps:group)
            cb(ps);
    }
    size_t size()const{return group.size();}
};
}

#endif // PENROSESHAPEGROUP_H
