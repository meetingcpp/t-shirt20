#ifndef CONCRETETYPES_H
#define CONCRETETYPES_H

#include <variant>
#include "shapegroup.h"
#include "penroseshapegroup.h"
#include "rasterizedshape.h"

using t_shapegroup = std::variant<penrose::PenroseShapeGroup,ShapeGroup<cpp20tshirt::RasterizedShape>>;

#endif // CONCRETETYPES_H
