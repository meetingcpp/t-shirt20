#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "penroseshapegroup.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QImage filter;
    penrose::PenroseShapeGroup psg;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionReset_triggered();

    void on_actionSet_Markimage_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
