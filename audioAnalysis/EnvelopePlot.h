#ifndef ENVELOPEPLOT_H
#define ENVELOPEPLOT_H

#include <QQuickItem>
#include <QQuickPaintedItem>

#include "Envelope.h"

class EnvelopePlot : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(Envelope* envelope READ envelope WRITE setEnvelope NOTIFY envelopeChanged)

public:
    EnvelopePlot(QQuickItem *parent=0);
    ~EnvelopePlot();

    Envelope* envelope();
    void setEnvelope(Envelope *envelope);

    void paint(QPainter *painter);

signals:
    void envelopeChanged();

private:
    Envelope* _envelope;

    double _releaseState;
    bool _sr;
};

#endif // ENVELOPEPLOT_H

