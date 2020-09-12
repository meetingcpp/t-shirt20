#ifndef SVGEXPORTWIDGET_H
#define SVGEXPORTWIDGET_H

#include <QWidget>
#include <functional>

namespace Ui {
class SVGExportWidget;
}

class SVGExportWidget : public QWidget
{
    Q_OBJECT
    using paintcb = std::function<void(QPainter&)>;
    paintcb dopaint;
public:
    explicit SVGExportWidget(QWidget *parent = 0);
    ~SVGExportWidget();

    void setDopaint(const paintcb &value);

private slots:
    void on_btn_svg_clicked();

private:
    Ui::SVGExportWidget *ui;
};

#endif // SVGEXPORTWIDGET_H
