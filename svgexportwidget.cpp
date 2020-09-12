#include "svgexportwidget.h"
#include "ui_svgexportwidget.h"

#include <QPainterPath>
#include <QPainter>
#include <QFileDialog>
#include <QSvgGenerator>

#include <QDebug>

void SVGExportWidget::setDopaint(const paintcb &value)
{
    dopaint = value;
    ui->canvas->setDopaint(dopaint);
}

SVGExportWidget::SVGExportWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SVGExportWidget)
{
    ui->setupUi(this);
}

SVGExportWidget::~SVGExportWidget()
{
    delete ui;
}

void SVGExportWidget::on_btn_svg_clicked()
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
