#ifndef PENROSECANVAS_H
#define PENROSECANVAS_H

#include <QWidget>

#include <complex>

using complex = std::complex<double>;

enum class Color{RED,BLUE};
struct Triangle
{
    Color color;
    complex a,b,c;
};

void divide(std::vector<Triangle>& sub,const Triangle &t);

class PenroseCanvas : public QWidget
{
    Q_OBJECT
    //double goldenratio = (1.0 + sqrt(5))/2.0;
    std::vector<Triangle> triangles;
    void paintEvent(QPaintEvent *);
    void addTriangleToPath(QPainterPath &path, const Triangle &t);
public:
    explicit PenroseCanvas(QWidget *parent = nullptr);
    void resetTiling();
    void levelup();
    //void strokeTriangles(QPainterPath& path)
signals:

public slots:
};

#endif // PENROSECANVAS_H
