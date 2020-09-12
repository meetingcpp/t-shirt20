#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <functional>

class QPainter;

class Canvas : public QWidget
{
    Q_OBJECT
    using paintcb = std::function<void(QPainter&)>;
    paintcb dopaint;
public:
    explicit Canvas(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent* );


    void setDopaint(const paintcb &value);

    const paintcb& getDopaint() const;

signals:

public slots:
};

#endif // CANVAS_H
