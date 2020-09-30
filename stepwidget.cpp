#include "stepwidget.h"
#include "ui_stepwidget.h"

#include <QPainterPath>
#include <QPainter>
#include <QFileDialog>
#include <QSvgGenerator>

#include <QDebug>

//painting helpers
void addTriangleToPath(QPainterPath &path, const QPoint& a, const QPoint& b, const QPoint& c)
{
    path.moveTo(a);
    path.lineTo(b);
    path.lineTo(c);
    path.closeSubpath();
}

/*void StepWidget::setDopaint(const paintcb &value)
{
    dopaint = value;
}*/

StepWidget::StepWidget(t_shapegroup &&shapes, QWidget *parent) :
    QWidget(parent), sg(std::move(shapes)),
    ui(new Ui::StepWidget)
{
    ui->setupUi(this);
    //ui->canvas->setDopaint();
    std::visit([this](const auto& v){
        using T = std::decay_t<decltype(v)>;
        if constexpr (std::is_same_v<T, penrose::PenroseShapeGroup>)
        {
            ui->canvas->setDopaint([this](QPainter& painter){
                auto psg = std::get<penrose::PenroseShapeGroup>(sg);
                QBrush black(Qt::black);
                painter.setBackground(black);
                painter.setRenderHint(QPainter::Antialiasing);
                //painter.translate(painter.window().center());
                QPainterPath path;
                painter.setPen(Qt::NoPen);
                //std::visit([&path](auto& psg){
                psg.visit([&path](const auto& ps){
                    ps.visit([&path,&ps](const auto& t){
                        if(t.color == penrose::Color::RED)
                            addTriangleToPath(path,ps.translate(t.a),ps.translate(t.b),ps.translate(t.c));
                    });
                });//},sg);
                painter.fillPath(path,QBrush{QColor{Qt::red}});
                path= QPainterPath{};

                //std::visit([&path](auto& psg){
                psg.visit([&path](const auto& ps){
                    ps.visit([&path,&ps](const auto& t){
                        if(t.color == penrose::Color::BLUE)
                            addTriangleToPath(path,ps.translate(t.a),ps.translate(t.b),ps.translate(t.c));
                    });
                });//},sg);
                painter.fillPath(path,QBrush{QColor{Qt::blue}});
                path = QPainterPath{};
                //std::visit([&path](const auto& psg){
                    psg.visit([&path](const auto& ps){
                    ps.visit([&path,&ps](const auto& t){
                        path.moveTo(ps.translate(t.c));
                        path.lineTo(ps.translate(t.a));
                        path.lineTo(ps.translate(t.b));
                    });
                });//},sg);
                painter.strokePath(path,QPen(QBrush{QColor{Qt::black}},1));//*/
            });
        }
        else if constexpr (std::is_same_v<T, ShapeGroup<cpp20tshirt::RasterizedShape>>)
        {
            ui->canvas->setDopaint([this](QPainter& painter){
                    auto shapegroup = std::get<ShapeGroup<cpp20tshirt::RasterizedShape>>(sg);
                    int rectsize = 4,gap = 2;
                    if(shapegroup.size()>0)
                    {
                        rectsize = shapegroup.front().getRectsize();
                        gap = shapegroup.front().getGap();
                    }
                    QBrush black(Qt::black);
                    painter.setBackground(black);
                    painter.setRenderHint(QPainter::Antialiasing);
                    painter.setPen(QPen{QColor{Qt::black},static_cast<double>(gap)});
                    painter.setBrush(QBrush{QColor{Qt::blue}});
                    //std::visit([&path](const auto& psg){
                    shapegroup.visit([&painter,rectsize](const auto& ps){
                        ps.visit([&painter,&ps,rectsize](const auto& p){
                            painter.drawRect(p.x(),p.y(),rectsize,rectsize);
                        });
                    });
                });
        }
    },sg);
}

StepWidget::~StepWidget()
{
    delete ui;
}

void StepWidget::on_btn_levelup_clicked()
{
    if(++counter < limit)
      std::visit([](auto& v){v.step();qDebug() << "step";},sg);
    update();
}

void StepWidget::on_btn_exportsvg_clicked()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Save SVG"), "~", tr("SVG files (*.svg)"));

    if (path.isEmpty())
        return;

    QSvgGenerator generator;
    generator.setFileName(path);
    generator.setSize(QSize(1000, 600));
    generator.setViewBox(QRect(0, 0, 1000, 600));
    generator.setTitle(tr("Meeting C++ SVG T-shirt export"));
    generator.setDescription(tr("Created with Qt SVG Generator "));

    QPainter painter;
    painter.begin(&generator);
    ui->canvas->getDopaint()(painter);
    painter.end();
}
