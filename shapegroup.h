#ifndef SHAPEGROUP_H
#define SHAPEGROUP_H

#include <vector>

enum ShapeType{
    PENROSE,RASTER
};

template<class Shape>
class ShapeGroup
{
   std::vector<Shape> group;
public:
   void addShape(Shape&& s){group.emplace_back(std::move(s));}
   void step(){
       for(auto& shape:group)
           shape.step();
   }
   template<class CB>
   void visit(const CB& cb)const
   {
       for(const auto& ps:group)
           cb(ps);
   }
   auto size()const{return group.size();}
   auto front()const{return group.front();}
};

#endif // SHAPEGROUP_H
