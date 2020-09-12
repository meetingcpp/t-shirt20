#include "penroseshapegroup.h"


namespace penrose {
PenroseShapeGroup::PenroseShapeGroup()
{

}

void PenroseShapeGroup::addShape( PenroseShape &&ps)
{
    group.emplace_back(std::move(ps));
}

void PenroseShapeGroup::step()
{
    for(auto& ps:group)
        ps.step();
}

}
