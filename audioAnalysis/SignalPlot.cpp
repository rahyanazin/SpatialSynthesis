#include "SignalPlot.h"

#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>

#define SNAPSHOT_LENGTH 1024*8

SignalPlot::SignalPlot(QQuickItem *parent) :
    QQuickItem(parent)
{
    setFlag(ItemHasContents, true);

    _buffer.clear();
    for(int i=0; i<SNAPSHOT_LENGTH; i++)
        _buffer.append(0.f);

    startTimer(16);
}

SignalPlot::~SignalPlot()
{
}

void SignalPlot::timerEvent(QTimerEvent *event)
{
    (void) event;

    update();
}

void SignalPlot::process(float *buffer, int frames)
{
    for (int i=0; i<frames; i++)
    {
        _buffer.append(buffer[i]);
        _buffer.dequeue();

        /*_buffer.append(buffer[i*2+1]);
        _buffer.dequeue();*/
    }
}

QSGNode* SignalPlot::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *)
{
    QSGGeometryNode *node = 0;
    QSGGeometry *geometry = 0;
    QSGFlatColorMaterial *material = 0;

    int bufferSize = SNAPSHOT_LENGTH;
    int verticesNumber = bufferSize;

    if (!oldNode)
    {
        node = new QSGGeometryNode;

        geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), verticesNumber);
        geometry->setLineWidth(1);
        geometry->setDrawingMode(GL_LINE_STRIP);

        node->setGeometry(geometry);
        node->setFlag(QSGNode::OwnsGeometry);

        material = new QSGFlatColorMaterial;
        material->setColor(Qt::white);

        node->setMaterial(material);
        node->setFlag(QSGNode::OwnsMaterial);
    }
    else
    {
        node = static_cast<QSGGeometryNode*>(oldNode);

        ((QSGFlatColorMaterial*) node->material())->setColor(Qt::white);

        geometry = node->geometry();
        geometry->allocate(verticesNumber);
    }

    QSGGeometry::Point2D *vertices = geometry->vertexDataAsPoint2D();

    float height = boundingRect().height();
    float width = boundingRect().width();

    float x,y;
    for (int i=0; i<verticesNumber; i++)
    {
        x = i*width/(verticesNumber-1.f);
        y = _buffer.at(i)*height/2;

        vertices[i].set(x,height/2 - y);
    }

    node->markDirty(QSGNode::DirtyGeometry);
    node->markDirty(QSGNode::DirtyMaterial);

    return node;
}
