#ifndef SIGNALPLOT_H
#define SIGNALPLOT_H

#include <QQuickItem>
#include <QQuickPaintedItem>
#include <QQueue>

class SignalPlot : public QQuickItem
{
    Q_OBJECT

public:
    enum{red,blue,yellow};
    SignalPlot(QQuickItem *parent=0);
    ~SignalPlot();

    QSGNode* updatePaintNode(QSGNode *, UpdatePaintNodeData *);

    void setColor(int color);

    void process(float *buffer, int frames);

protected:
    void timerEvent(QTimerEvent *event);

private:
    QQueue<float> _buffer;
    Qt::GlobalColor _color;
};

#endif // SIGNALPLOT_H
