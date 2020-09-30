#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <algorithm>

#include <qfiledialog.h>
#include <QThreadPool>
#include <QTextLayout>
#include <QGlyphRun>
#include <QPolygon>

#include <QDebug>

#include "pixelgrouprunner.h"
#include "stepwidget.h"
#include "svgexportwidget.h"
#include "pixelgroup.h"
#include "shapegroup.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qRegisterMetaType<PixelModel>();
    //ui->penrosewidget->resetTiling();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionReset_triggered()
{
    //ui->penrosewidget->resetTiling();
    update();
}

void MainWindow::on_actionSet_Markimage_triggered()
{
    QString file = QFileDialog::getOpenFileName(this,"Open Mask Image","~/","(*.jpg *.png)");
    if(!file.isEmpty())
    {
        filter = QImage(file);
        auto pgr = new PixelGroupRunner(filter,this);
        QThreadPool::globalInstance()->start(pgr );
        connect(pgr,&PixelGroupRunner::finished,this,[this](const PixelModel& m){
            t_shapegroup shapes;
            switch (mode) {
                case ShapeType::PENROSE:
                    shapes = penrose::PenroseShapeGroup{};
                break;
                case ShapeType::RASTER:
                    shapes = ShapeGroup<cpp20tshirt::RasterizedShape>{};
                break;
            }
                //penrose::PenroseShapeGroup psg;
                m.visit([&shapes](auto& pg){
                    //psg.addShape(penrose::PenroseShape(std::move(pg)));
                    std::visit([&pg](auto& v){
                        using T = std::decay_t<decltype(v)>;
                        if constexpr (std::is_same_v<T, penrose::PenroseShapeGroup>)
                          v.addShape(penrose::PenroseShape(std::move(pg)));
                        else if constexpr (std::is_same_v<T, ShapeGroup<cpp20tshirt::RasterizedShape>>)
                          v.addShape(cpp20tshirt::RasterizedShape(std::move(pg)));
                    },shapes);
                });
            ui->tabWidget->addTab(new StepWidget(std::move(shapes),ui->tabWidget),QString("Mask %1").arg(ui->tabWidget->count()));
        });
    }
}
