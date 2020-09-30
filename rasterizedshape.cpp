#include "rasterizedshape.h"

#include <QDebug>

namespace cpp20tshirt
{
int RasterizedShape::getRectsize() const
{
    return rectsize;
}

int RasterizedShape::getGap() const
{
    return gap;
}

RasterizedShape::RasterizedShape(PixelGroup&& pg):group(std::move(pg))
{

}

void RasterizedShape::step()
{
    auto rect = group.getRefrect();
    //qDebug() << group.getRefpoint() << rect;
    int w = rect.width();
    int h = rect.height();
    int rs = rectsize + gap;
    for(int wi = 0; wi < w; wi += rs)
    {
        for(int hi = 0; hi < h; hi += rs)
        {
            Point p(wi,hi);
            if(group.isLocalPointInGroup(p))
                anchors.push_back(group.translatePoint(p));
            else //if(false)
            {
                Point rt(wi+rs,hi);
                if(group.isLocalPointInGroup(rt))
                    anchors.push_back(group.translatePoint(p));
                else if(Point rb(wi+rs,hi+rs);group.isLocalPointInGroup(rb))
                    anchors.push_back(group.translatePoint(p));
                else if(Point lb(wi,hi+rs);group.isLocalPointInGroup(lb))
                    anchors.push_back(group.translatePoint(p));
            }
        }
    }
}
}
