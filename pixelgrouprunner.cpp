#include "pixelgrouprunner.h"

#include <QDebug>

PixelGroupRunner::PixelGroupRunner(QImage img, QObject *parent) : QObject(parent),img(img)
{

}

void PixelGroupRunner::run()
{
    int h = img.height();
    int w = img.width();
    size_t white = 0;
    for(int x = 0; x < w;x++)
    {
        for(int y = 0; y < h; y++)
        {
            if(img.pixelColor(x,y)==Qt::white)
            {
                model.addPoint(QPoint(x,y));
                ++white;
            }
        }
    }
    qDebug() << white << "white pixels";
    white = 0;
    model.visit([&white](const auto& v){
        white += v.size();
    });
    qDebug() << white << "white group pixels";
    emit finished(model);
}

void PixelModel::addPoint(const Point &p)
{
    auto nvec = neighbors(p);
    using vrt = std::vector<std::vector<pixelgroup>::iterator>;
    vrt found_in_groups;
    auto find_in_groups = [this,&found_in_groups](const Point& p){
        auto it = groups.begin();
        for(;it != groups.end();++it)
        {
            if(!it->empty() && std::binary_search(it->begin(),it->end(),p))
                found_in_groups.push_back(it);
        }
    };

    for(const auto& cp: nvec)
        find_in_groups(cp);
    if(found_in_groups.empty())//not found, new group
    {
        groups.push_back(pixelgroup{p});
        //groups.back().reserve(50);//groups are expected to grow
    }
    else if(found_in_groups.size() == 1)//only one group, add
    {
        insertInto(*found_in_groups.front(),p);
    }
    else if(found_in_groups.size()>1)// merge groups
    {
        pixelgroup pg;
        size_t s=0;
        insertInto(*found_in_groups[0],p);
        for(auto& it:found_in_groups)
            s+= it->size();
        for(auto& it:found_in_groups)
        {
            if(pg.empty())
                std::swap(pg,*it);
            else
            {
                for(auto& c:*it)
                {
                    insertInto(pg,c);
                }
                //std::copy(it->begin(),it->end(),std::back_inserter(pg));
            }
            it->clear();
        }
        groups.emplace_back(std::move(pg));//*/
        auto back = groups.back();
        auto it = std::remove_if(groups.begin(),groups.end(),[](const auto& v){return v.empty();});
        groups.erase(it,groups.end());
    }
    else
        qDebug() << "failed for " <<p;
}

void PixelModel::addPointSlow(const Point &p)
{
    auto nvec = neighbors(p);
    using vrt = std::vector<std::vector<pixelgroup>::iterator>;
    vrt found_in_groups;
    auto find_in_groups = [this,&found_in_groups](const Point& p){
        auto it = groups.begin();
        for(;it != groups.end();++it)
        {
            if(!it->empty() && std::find(it->begin(),it->end(),p)!= it->end())
                found_in_groups.push_back(it);
        }
    };
    for(const auto& cp: nvec)
        find_in_groups(cp);
    if(found_in_groups.empty())//not found, new group
        groups.push_back(pixelgroup{p});
    else if(found_in_groups.size() == 1)//only one group, add
        found_in_groups.front()->push_back(p);
    else if(found_in_groups.size()>1)// merge groups
    {
        pixelgroup pg;
        size_t s=0;
        found_in_groups[0]->push_back(p);
        for(auto& it:found_in_groups)
            s+= it->size();
        for(auto& it:found_in_groups)
        {
            if(pg.empty())
                std::swap(pg,*it);
            else
                std::copy(it->begin(),it->end(),std::back_inserter(pg));
            it->clear();
        }
        groups.emplace_back(std::move(pg));//*/
        auto it = std::remove_if(groups.begin(),groups.end(),[](const auto& v){return v.empty();});
        groups.erase(it,groups.end());
    }
    else
        qDebug() << "failed for " <<p;
}

std::vector<Point> PixelModel::neighbors(const Point &p)
{
    //123
    //8x4
    //765
    std::vector<Point> n;
    n.reserve(8);
    int x = p.x(), y = p.y();
    if(y > 0)
    {
        if(x > 0)
            n.emplace_back(x-1,y-1);//1
        n.emplace_back(x,y-1);//2
        n.emplace_back(x+1,y-1);//3
    }
    n.emplace_back(x+1,y);//4
    /*n.emplace_back(x+1,y+1);//5
    n.emplace_back(x,y+1);//6
    if(x > 0)
    {
        n.emplace_back(x-1,y+1);//7
        n.emplace_back(x-1,y);//8
    }*/
    return n;
}

void insertInto(pixelgroup &pg, const Point &p)
{
    auto it = std::upper_bound(pg.begin(),pg.end(),p);
    pg.insert(it,p);
}
