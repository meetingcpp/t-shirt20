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

void StepWidget::setDopaint(const paintcb &value)
{
    dopaint = value;
}

StepWidget::StepWidget(penrose::PenroseShapeGroup &&psga, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StepWidget), psg(std::move(psga))
{
    ui->setupUi(this);
    ui->canvas->setDopaint([this](QPainter& painter){
        QBrush black(Qt::black);
        painter.setBackground(black);
        painter.setRenderHint(QPainter::Antialiasing);
        //painter.translate(painter.window().center());
        QPainterPath path;
        painter.setPen(Qt::NoPen);
        psg.visit([&path](const auto& ps){
            ps.visit([&path,&ps](const auto& t){
                if(t.color == penrose::Color::RED)
                    addTriangleToPath(path,ps.translate(t.a),ps.translate(t.b),ps.translate(t.c));
            });
        });
        painter.fillPath(path,QBrush{QColor{Qt::red}});
        path= QPainterPath{};
        psg.visit([&path](const auto& ps){
            ps.visit([&path,&ps](const auto& t){
                if(t.color == penrose::Color::BLUE)
                    addTriangleToPath(path,ps.translate(t.a),ps.translate(t.b),ps.translate(t.c));
            });
        });
        painter.fillPath(path,QBrush{QColor{Qt::blue}});
        path = QPainterPath{};
        psg.visit([&path](const auto& ps){
            ps.visit([&path,&ps](const auto& t){
                path.moveTo(ps.translate(t.c));
                path.lineTo(ps.translate(t.a));
                path.lineTo(ps.translate(t.b));
            });
        });
        painter.strokePath(path,QPen(QBrush{QColor{Qt::black}},1));//*/
    });
}

StepWidget::~StepWidget()
{
    delete ui;
}

void StepWidget::on_btn_levelup_clicked()
{
    psg.step();
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
