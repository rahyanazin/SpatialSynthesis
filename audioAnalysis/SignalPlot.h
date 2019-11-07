#ifndef SIGNALPLOT_H
#define SIGNALPLOT_H

#include <QQuickItem>
#include <QQuickPaintedItem>
#include <QQueue>

class SignalPlot : public QQuickItem
{
    Q_OBJECT

public:
    SignalPlot(QQuickItem *parent=0);
    ~SignalPlot();

    QSGNode* updatePaintNode(QSGNode *, UpdatePaintNodeData *);

    void process(float *buffer, int frames);

protected:
    void timerEvent(QTimerEvent *event);

private:
    QQueue<float> _buffer;
};

#endif // SIGNALPLOT_H
