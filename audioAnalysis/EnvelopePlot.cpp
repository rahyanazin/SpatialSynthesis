#include "EnvelopePlot.h"

#include <QMatrix>
#include <QPainter>

#include <qdebug.h>

EnvelopePlot::EnvelopePlot(QQuickItem *parent) :
    QQuickPaintedItem(parent),
    _envelope(0),
    _releaseState(0.0),
    _sr(false)
{
    setFlag(ItemHasContents, true);    

    _envelope = new Envelope();
}

EnvelopePlot::~EnvelopePlot()
{
}

void EnvelopePlot::paint(QPainter *painter)
{
    if(!_envelope) return;

    double width=boundingRect().width();
    double height=boundingRect().height();

    QColor penColor = Qt::white;

    QPen pen;
    pen.setWidth(1);
    pen.setColor(penColor);
    painter->setPen(pen);

    QMatrix m;
    m.translate(0,height);
    m.scale(1, -1);
    painter->setMatrix(m);

    //double adr = _envelope->attack()+_envelope->decay()+_envelope->release();
    double adr = _envelope->attack()+_envelope->release();

    double sustainFactor = 0.0;//0.1+0.9*(1.0-adr/2.0);

    double iSustainFactor = 1.0-sustainFactor;

    //double sustainWidth = sustainFactor*width;

    double attackWidth = 0.0;
    //double decayWidth = 0.0;
    double releaseWidth = 0.0;
    if(adr != 0.0)
    {
        attackWidth = iSustainFactor*width*_envelope->attack()/adr;
        //decayWidth = iSustainFactor*width*_envelope->decay()/adr;
        releaseWidth = iSustainFactor*width*_envelope->release()/adr;
    }

    QPoint last(0.0,0.0);
    QPoint aux = last;

    //Attack View
    for(double i=0; i<=1; i+=0.001)
    {
        double x = i*attackWidth;
        double y = height*_envelope->attackStepPlot(i);
        aux = QPoint(x, y);
        painter->drawLine(last, aux);
        last = aux;
    }
    painter->drawLine(last, QPoint(last.x(), 0.0));

    //Decay View
    /*double decayX0 = last.x();
    for(double i=0.0; i<=1.0; i+=0.001)
    {
        double x = decayX0 + i*decayWidth;
        double y = height*_envelope->decayStep(i);
        aux = QPoint(x, y);
        painter->drawLine(last, aux);
        last = aux;
    }

    //dotted line
    for(double i=last.y(); i>=0.0; i-=5.0)
    {
        aux = QPoint(last.x(), i);
        painter->drawPoint(aux);
    }

    //Sustain View
    //double sustainX0 = last.x();
    aux = QPoint(last.x()+sustainWidth, last.y());
    painter->drawLine(last, aux);
    last = aux;

    //painter->drawLine(last, QPoint(width/2.0, height/2.0));

    //dotted line
    for(double i=last.y(); i>=0.0; i-=5.0)
    {
        aux = QPoint(last.x(), i);
        painter->drawPoint(aux);
    }*/

    //Release View
    double releaseX0 = last.x();
    for(double i=0; i<=1; i+=0.001)
    {
        double x = releaseX0 + i*releaseWidth;
        double y = height*_envelope->releaseStepPlot(i);
        aux = QPoint(x, y);
        painter->drawLine(last, aux);
        last = aux;
    }
}

Envelope *EnvelopePlot::envelope()
{
    return _envelope;
}

void EnvelopePlot::setEnvelope(Envelope* envelope = nullptr)
{
    if (envelope) {
        _envelope = envelope;

        update();

        connect(_envelope, SIGNAL(paramsChanged()), SLOT(update()));
    }
}
