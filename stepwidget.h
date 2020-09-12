#ifndef STEPWIDGET_H
#define STEPWIDGET_H

#include <QWidget>
#include <QPainter>
#include <functional>

#include "penroseshapegroup.h"

namespace Ui {
class StepWidget;
}

class StepWidget : public QWidget
{
    Q_OBJECT

    using paintcb = std::function<void(QPainter&)>;
    paintcb dopaint;
    penrose::PenroseShapeGroup psg;
public:
    explicit StepWidget(penrose::PenroseShapeGroup&& psga, QWidget *parent = 0);
    ~StepWidget();

    void setDopaint(const paintcb &value);

private slots:
    void on_btn_levelup_clicked();

    void on_btn_exportsvg_clicked();

private:
    Ui::StepWidget *ui;
};

#endif // STEPWIDGET_H
