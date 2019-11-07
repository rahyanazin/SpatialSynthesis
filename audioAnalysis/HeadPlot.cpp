#include "HeadPlot.h"

#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>
#include <QTransform>

#include <qmath.h>

#define VERTICES 1024*8

#define MAX_GAIN_REFERENCE 20.0 //max value in dB represented in Plot

HeadPlot::HeadPlot(QQuickItem *parent) :
    QQuickItem(parent),
    _head(0)
{
    setFlag(ItemHasContents, true);
}

HeadPlot::~HeadPlot()
{
}

void HeadPlot::setFilter(Head *head)
{
    _head = head;

    update();
}

QSGNode *HeadPlot::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *)
{
    QSGTransformNode *transformNode = 0;
    QSGGeometryNode *geometryNode = 0;
    QSGGeometry *geometry = 0;
    QSGFlatColorMaterial *material = 0;

    double height = boundingRect().height();
    double width = boundingRect().width();

    QTransform transform = QTransform().translate(0, height/2.0).scale(1, -1);

    int verticesNumber = VERTICES*2;

    if (!oldNode)
    {
        transformNode = new QSGTransformNode();
        transformNode->setMatrix(QMatrix4x4(transform));

        geometryNode = new QSGGeometryNode;

        geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), verticesNumber);
        geometry->setLineWidth(2);
        geometry->setDrawingMode(QSGGeometry::DrawPoints);

        geometryNode->setGeometry(geometry);
        geometryNode->setFlag(QSGNode::OwnsGeometry);

        material = new QSGFlatColorMaterial;
        material->setColor(Qt::blue);

        geometryNode->setMaterial(material);
        geometryNode->setFlag(QSGNode::OwnsMaterial);

        transformNode->appendChildNode(geometryNode);
    }
    else
    {
        transformNode = static_cast<QSGTransformNode*>(oldNode);
        transformNode->setMatrix(QMatrix4x4(transform));
        geometryNode = static_cast<QSGGeometryNode*>(transformNode->childAtIndex(0));
        ((QSGFlatColorMaterial*) geometryNode->material())->setColor(Qt::blue);

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

    double x, omega;
    double y_left, y_right;
    double gain_left, gain_right;
    double dBgainNormalized_left, dBgainNormalized_right;

    double omega0 = 0.00285; //2.0*M_PI*20.0/((double)_sampleRate);

    for (int i=0; i<verticesNumber/2; i++)
    {
        if(_head) {
            x = (double) i*width/(verticesNumber/2-1.0); //varying x from 0 to width
            omega = omega0*pow(M_PI/omega0, (double)i/(verticesNumber/2-1.0)); //varying from 0 to PI

            //Left
            gain_left = _head->transferFunction_left(omega); //gain = |Hz(omega))|
            dBgainNormalized_left = 20.0*log10(abs(gain_left))/MAX_GAIN_REFERENCE; //gain in dBs normalized
            if(dBgainNormalized_left > 1.0) dBgainNormalized_left = 1.0;
            if(dBgainNormalized_left < -1.0) dBgainNormalized_left = -1.0;
            y_left = dBgainNormalized_left*height/2.0;

            //Right
            gain_right = _head->transferFunction_right(omega); //gain = |Hz(omega))|
            dBgainNormalized_right = 20.0*log10(abs(gain_right))/MAX_GAIN_REFERENCE; //gain in dBs normalized
            if(dBgainNormalized_right > 1.0) dBgainNormalized_right = 1.0;
            if(dBgainNormalized_right < -1.0) dBgainNormalized_right = -1.0;
            y_right = dBgainNormalized_right*height/2.0;

            ((QSGFlatColorMaterial*) geometryNode->material())->setColor(Qt::blue);
            vertices[2*i].set(x,(float) y_left);
            ((QSGFlatColorMaterial*) geometryNode->material())->setColor(Qt::yellow);
            vertices[2*i+1].set(x,(float) y_right);
        }

        else {
            ((QSGFlatColorMaterial*) geometryNode->material())->setColor(Qt::blue);
            vertices[2*i].set(x,0);
            ((QSGFlatColorMaterial*) geometryNode->material())->setColor(Qt::yellow);
            vertices[2*i+1].set(x,0);
        }
    }

    geometryNode->markDirty(QSGNode::DirtyGeometry);
    geometryNode->markDirty(QSGNode::DirtyMaterial);

    return transformNode;
}
