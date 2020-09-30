#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <variant>

#include <QMainWindow>

#include "concretetypes.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QImage filter;
    ShapeType mode=ShapeType::RASTER;
    penrose::PenroseShapeGroup psg;
    t_shapegroup shapes;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionReset_triggered();

    void on_actionSet_Markimage_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
