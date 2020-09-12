#include <QTextLayout>
#include <QGlyphRun>
#include <QPolygon>

#include <QDebug>

#include "pixelgrouprunner.h"
#include "stepwidget.h"
#include "svgexportwidget.h"

// this code was written for a specific task, and is not used anymore.
// may it rest in this place until parts of it are revisited in an uncertain future

void drawCircularText(QPainter& painter,QPen& pen,QFont font,const QString& text,int x, int y, int diameter,qreal percentfactor = 0.5,
                      qreal start_in_percent=0, bool reverse = false)
{
    painter.setPen(pen);

    QPainterPath path(QPointF(0.0, 0.0));
    path.addEllipse(x,y,diameter,diameter);
    if(reverse)
        path = path.toReversed();

    //draw the circle
    //painter.drawPath(path);

    //Make the painter ready to draw chars
    //
    painter.setFont(font);
    painter.setPen(pen);

    QFontMetrics fmetrics(font,painter.device());
    auto textwidth = fmetrics.width(text);
    std::vector<double> increase(text.size());
    size_t i =0;
    for(auto&c : text)
    {
        increase[i++]= fmetrics.width(c) / (textwidth/100.0)/100.0;
    }
    auto avgwidth = (std::accumulate(increase.begin(),increase.end(),0.0)/ increase.size() )*percentfactor;
    qreal percentIncrease = (qreal) 1.0/text.size()*percentfactor;

    for ( i = 0; i < text.size(); i++ ) {
        if(i > 0)
        {
            //auto inc = ( (increase[i]+increase[i-1])/2 - percentIncrease)*percentfactor;
            auto inc = (avgwidth + (increase[i-1]/2))*percentfactor;
            start_in_percent += inc;// inc > avgwidth ? inc > avgwidth*1.1 ? avgwidth*1.1 : inc : avgwidth;
        }
        if(start_in_percent > 1.0)
        {
            qDebug() << "start_in_percent is over 1.0:" << start_in_percent;
            start_in_percent -= 1.0;
        }
qDebug() << avgwidth<< increase[i]<< text[(int)i] << start_in_percent;
        QPointF point = path.pointAtPercent(start_in_percent);
        qreal angle = path.angleAtPercent(start_in_percent);   // Clockwise is negative

        painter.save();
        // Move the virtual origin to the point on the curve
        painter.translate(point);
        // Rotate to match the angle of the curve
        // Clockwise is positive so we negate the angle from above
        painter.rotate(-angle);
        // Draw a line width above the origin to move the text above the line
        // and let Qt do the transformations
        painter.drawText(QPoint(0, -pen.width()),QString(text[(int)i]));
        //if(glyphruns.size() < (int)i)
        //painter.drawGlyphRun(QPoint(0, -pen.width()),glyphruns[i]);
        painter.restore();
    }
}

auto drawEvenHexagon(QPainter& painter, int x, int y, int diameter)
{
    QPainterPath path;
    path.addEllipse(x,y,diameter,diameter);
    double ratio = 1.0/6.0;
    double start = 1/12.0;
    auto startpoint = path.pointAtPercent(start);
    QPolygon poly;
    poly.append(startpoint.toPoint());
    for(int i =0; i < 5;++i)
    {
        start += ratio;
        poly.append(path.pointAtPercent(start).toPoint());
    }
    painter.drawPolygon(poly);
    return poly;
}

void drawCircularTextCounterClockWise(QPainter& painter,QPen& pen,QFont font, QString text,int x, int y, int diameter,qreal percentfactor = 0.5,
                      qreal start_in_percent=0)
{
    painter.setPen(pen);
    /*auto rev = text.toStdString();
    std::reverse(rev.begin(),rev.end());
    text = text.fromStdString(rev);*/

    QPainterPath path(QPointF(0.0, 0.0));
    path.addEllipse(x,y,diameter,diameter);

    //draw the circle
    //painter.drawPath(path);
    path = path.toReversed();

    //Make the painter ready to draw chars
    painter.setFont(font);

    qreal percentIncrease = (qreal) 1.0/text.size()*percentfactor;

    for ( int i = 0; i < text.size(); i++ ) {
        start_in_percent += percentIncrease;
        if(start_in_percent > 1.0)
        {
            qDebug() << "start_in_percent is over 1.0:" << start_in_percent;
            start_in_percent -= 1.0;
        }

        QPointF point = path.pointAtPercent(start_in_percent);
        qreal angle = path.angleAtPercent(start_in_percent);   // Clockwise is negative
        //auto pd = painter.device();
        //painter.end();
        //auto img = drawTextOnPixmap(QString(text[i]),font,font.pixelSize()).mirrored(true,true);

        //painter.begin(pd);
        painter.save();

        // Move the virtual origin to the point on the curve
        painter.translate(point);
        // Rotate to match the angle of the curve
        // Clockwise is positive so we negate the angle from above
        painter.rotate(-angle);
        // Draw a line width above the origin to move the text above the line
        // and let Qt do the transformations
        painter.drawText(QPoint(0, -pen.width()),QString(text[i]));
        //painter.drawImage(QPointF(0, -font.pixelSize()),img);
        painter.restore();
    }
}





/*std::srand(std::time(nullptr));
auto* svgwidget = new SVGExportWidget(ui->tabWidget);
svgwidget->setDopaint([](QPainter& painter){
    QBrush black(Qt::black);
    painter.setBackground(black);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(black);
    QPen pen(Qt::black);
    int startx = 0,starty = 0;
    int lenght = 600;
    int centerx = lenght/ 2;
    int centery = lenght/ 2;
    QPoint center(centerx,centery);
    painter.drawRect(startx,starty,lenght,lenght);

    //painter.drawEllipse(startx +300,starty+100,400,400);
    QPen textpen(Qt::white);
    QFont font = painter.font();
    font.setPixelSize(40);
    font.setBold(true);
    drawCircularText(painter,textpen,font," Meeting C++ ",75 ,75,450,0.4,0.57);
    drawCircularText(painter,textpen,font,"Certified Library",55 ,55,490,0.4,0.575,true);
    painter.setBrush(QBrush(Qt::white));
    QPolygon hex = drawEvenHexagon(painter, 100, 100,400);

    painter.setBrush(black);
    textpen.setWidth(10);
    painter.setPen(textpen);
    painter.drawEllipse(center,100,100);

    painter.setBrush(QBrush(Qt::white));
    pen.setColor(Qt::white);
    painter.setPen(pen);
    painter.drawEllipse(center,55,55);
    QPolygon poly; poly << center << hex.back() << hex.front();
    painter.drawPolygon(poly);

    painter.setBrush(black);
    textpen.setWidth(10);
    textpen.setColor(Qt::black);
    painter.setPen(textpen);
    font.setPixelSize(72);
    painter.setFont(font);
    auto height =  font.pixelSize()/3;
    painter.drawText(centerx + 70, centery + height,"++");

});
ui->tabWidget->addTab(svgwidget,"logo");*/
