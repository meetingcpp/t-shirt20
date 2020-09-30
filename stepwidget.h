#ifndef STEPWIDGET_H
#define STEPWIDGET_H

#include <QWidget>
#include <QPainter>
#include <functional>

//#include "penroseshapegroup.h"
#include "concretetypes.h"

namespace Ui {
class StepWidget;
}

class StepWidget : public QWidget
{
    Q_OBJECT

    using paintcb = std::function<void(QPainter&)>;
    t_shapegroup sg;
    int counter = 0,limit =20;
public:
    explicit StepWidget(t_shapegroup&& shapes, QWidget *parent = nullptr);
    ~StepWidget();

    //void setDopaint(const paintcb &value);

private slots:
    void on_btn_levelup_clicked();

    void on_btn_exportsvg_clicked();

private:
    Ui::StepWidget *ui;
};

#endif // STEPWIDGET_H
