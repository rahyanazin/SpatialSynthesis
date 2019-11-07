#include "TransferFunctionPlot.h"

#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>
#include <QTransform>

#include <qmath.h>

#define VERTICES 1024*8

#define MAX_GAIN_REFERENCE 20.0 //max value in dB represented in Plot

TransferFunctionPlot::TransferFunctionPlot(QQuickItem *parent) :
    QQuickItem(parent),
    _filter(nullptr),
    _color(Qt::red)
{
    setFlag(ItemHasContents, true);
}

TransferFunctionPlot::~TransferFunctionPlot()
{
}

void TransferFunctionPlot::setFilter(Filter *filter)
{
    _filter = filter;

    update();
}

void TransferFunctionPlot::setColor(int color)
{
    switch(color){
        case red: _color = Qt::red; break;
        case blue: _color = Qt::blue; break;
        case yellow: _color = Qt::yellow; break;
    }
}

QSGNode *TransferFunctionPlot::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *)
{
    QSGTransformNode *transformNode = 0;
    QSGGeometryNode *geometryNode = 0;
    QSGGeometry *geometry = 0;
    QSGFlatColorMaterial *material = 0;

    double height = boundingRect().height();
    double width = boundingRect().width();

    QTransform transform = QTransform().translate(0, height/2.0).scale(1, -1);

    int verticesNumber = VERTICES;

    if (!oldNode)
    {
        transformNode = new QSGTransformNode();
        transformNode->setMatrix(QMatrix4x4(transform));

        geometryNode = new QSGGeometryNode;

        geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), verticesNumber);
        geometry->setLineWidth(2);
        geometry->setDrawingMode(GL_LINE_STRIP);

        geometryNode->setGeometry(geometry);
        geometryNode->setFlag(QSGNode::OwnsGeometry);

        material = new QSGFlatColorMaterial;
        material->setColor(_color);

        geometryNode->setMaterial(material);
        geometryNode->setFlag(QSGNode::OwnsMaterial);

        transformNode->appendChildNode(geometryNode);
    }
    else
    {
        transformNode = static_cast<QSGTransformNode*>(oldNode);
        transformNode->setMatrix(QMatrix4x4(transform));
        geometryNode = static_cast<QSGGeometryNode*>(transformNode->childAtIndex(0));
        ((QSGFlatColorMaterial*) geometryNode->material())->setColor(_color);

        geometry = geometryNode->geometry();
        geometry->allocate(verticesNumber);
    }

    QSGGeometry::Point2D *vertices = geometry->vertexDataAsPoint2D();

    /*
     * Plot: Gain versus Frequency
     *
     * Gain = |H(z)|
     * z = cos(omega) + i*sin(Omega)
     * omega = 2*PI*Frequency/SampleRate
     *
     * OBS: From the definition above, to obtain the Filter (Gain) Frequency Response
     *      for Frequencies in range 0 to Nyquist (SampleRate/2), we just need to plot Gain for
     *      Omega in range 0 to PI
     */

    double x,y;
    double omega, gain, dBgainNormalized;

    double omega0 = 0.00285; //2.0*M_PI*20.0/((double)_sampleRate);

    for (int i=0; i<verticesNumber; i++)
    {
        if(_filter) {
            x = (double) i*width/(verticesNumber-1.0); //varying x from 0 to width

            omega = omega0*pow(M_PI/omega0, (double)i/(verticesNumber-1.0)); //varying from 0 to PI

            gain = _filter->transferFunction(omega); //gain = |Hz(omega))|

            dBgainNormalized = 20.0*log10(abs(gain))/MAX_GAIN_REFERENCE; //gain in dBs normalized

            if(dBgainNormalized > 1.0) dBgainNormalized = 1.0;
            if(dBgainNormalized < -1.0) dBgainNormalized = -1.0;

            y = dBgainNormalized*height/2.0;

            vertices[i].set(x,y);
        }

        else
            vertices[i].set(i*width/(verticesNumber-1),height/2-i*height/(verticesNumber-1));
    }

    geometryNode->markDirty(QSGNode::DirtyGeometry);
    geometryNode->markDirty(QSGNode::DirtyMaterial);

    return transformNode;
}
