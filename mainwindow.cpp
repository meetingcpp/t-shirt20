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
            penrose::PenroseShapeGroup psg;
            m.visit([this,&psg](const auto& pg){
                psg.addShape(penrose::PenroseShape(std::move(pg)));
            });
            ui->tabWidget->addTab(new StepWidget(std::move(psg),ui->tabWidget),QString("Mask %1").arg(ui->tabWidget->count()));
        });
    }
}
