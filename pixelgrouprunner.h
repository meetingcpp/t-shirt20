#ifndef PIXELGROUPRUNNER_H
#define PIXELGROUPRUNNER_H

#include <QObject>
#include <QRunnable>
#include <QImage>

#include "pixelgroup.h"

class PixelModel
{
    std::vector<pixelgroup> groups;
    size_t merged =0;
public:
    void addPoint(const Point& p);
    void addPointSlow(const Point& p);
    template<class CB>
    void visit(const CB& cb)const
    {
        for(const auto& pg:groups)
            cb(pg);
    }
    template<class CB>
    void visit( CB& cb)
    {
        for( auto& pg:groups)
            cb(pg);
    }

private:
    std::vector<Point> neighbors(const Point& p);
};

inline void insertInto(pixelgroup& pg,const Point& p);

Q_DECLARE_METATYPE(PixelModel)

class PixelGroupRunner : public QObject, public QRunnable
{
    Q_OBJECT
    PixelModel model;
    QImage img;
public:
    explicit PixelGroupRunner(QImage img,QObject *parent = nullptr);
    void run();

signals:
    void finished(const PixelModel&);

public slots:
};

#endif // PIXELGROUPRUNNER_H
