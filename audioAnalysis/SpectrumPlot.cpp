#include "SpectrumPlot.h"

#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>
#include <QTransform>

#include <qmath.h>

#define FFT_SIZE            8192

#define MAX_GAIN_DB         20
#define MAX_ATTENUATION_DB  20

#define MAX_GAIN            pow(10.0, MAX_GAIN_DB/20)
#define MIN_GAIN            pow(10.0, -MAX_ATTENUATION_DB/20)

#define GAIN_IN_DB

SpectrumPlot::SpectrumPlot(QQuickItem *parent) :
    QQuickItem(parent),
    _sampleRate(44100),
    _fft_plan(0),
    _fftReady(0),
    _size(FFT_SIZE)
{
    setFlag(ItemHasContents, true);

    _signal.clear();
    _window.clear();
    for(int i=0; i<_size; i++){
        _signal.append(0.0f);
        _window.append(0.5f*(1-qCos(2*M_PI*i/(_size-1))));
    }

    #ifdef GAIN_IN_DB
    for(int i=0; i<_size/2; i++)
        _buffer[i] = -MAX_ATTENUATION_DB;
    #else
    for(int i=0; i<_size/2; i++)
        _buffer[i] = 0.0;
    #endif

    configFFT();

    startTimer(16);
}

SpectrumPlot::~SpectrumPlot()
{
    fftw_destroy_plan(_fft_plan);
    fftw_free(_fft_in);
    fftw_free(_fft_out);
    fftw_cleanup();
}

void SpectrumPlot::configFFT()
{
    _fft_outlen = _size/2;
    _fft_in = (double *)fftw_malloc(sizeof(double)*_size);
    _fft_out = (fftw_complex *)fftw_malloc(sizeof(fftw_complex)*(_fft_outlen+1));
    _fft_plan = fftw_plan_dft_r2c_1d(_size, _fft_in, _fft_out, FFTW_ESTIMATE);
}

void SpectrumPlot::timerEvent(QTimerEvent *event)
{
    (void) event;

    update();
}

void SpectrumPlot::process(float *buffer, int frames)
{
    for (int i=0; i<frames; i++) {
//        _signal.append(buffer[i*2]);
        _signal.append(buffer[i]);
    }

    while (_signal.size()>_size)
        _signal.dequeue();

    for (int i=0; i<_size; i++)
        _fft_in[i] = _signal.at(i)*_window.at(i);

    fftw_execute(_fft_plan);

    float mag;
    for (int i=0; i<_fft_outlen; i++)
    {
        #ifdef GAIN_IN_DB
        mag = 20*log10(sqrt(_fft_out[i][0] * _fft_out[i][0] + _fft_out[i][1] * _fft_out[i][1]));

        if(mag > MAX_GAIN_DB) mag = MAX_GAIN_DB;
        if(mag < -MAX_ATTENUATION_DB) mag = -MAX_ATTENUATION_DB;
        #else
        mag = sqrt(_fft_out[i][0] * _fft_out[i][0] + _fft_out[i][1] * _fft_out[i][1]);

        if(mag > MAX_GAIN) mag = MAX_GAIN;
        if(mag < MIN_GAIN) mag = 0.0;
        #endif

        _buffer[i] = mag;
    }
}

QSGNode* SpectrumPlot::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *)
{
    QSGTransformNode *transformNode = 0;
    QSGGeometryNode *geometryNode = 0;
    QSGGeometry *geometry = 0;
    QSGFlatColorMaterial *material = 0;

    double height = boundingRect().height();
    double width = boundingRect().width();

    QTransform transform = QTransform().translate(0, height).scale(1, -1);

    int verticesNumber = _fft_outlen;

    if (!oldNode)
    {
        transformNode = new QSGTransformNode();
        transformNode->setMatrix(QMatrix4x4(transform));

        geometryNode = new QSGGeometryNode;

        geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), verticesNumber);
        geometry->setLineWidth(1);
        geometry->setDrawingMode(GL_LINE_STRIP);

        geometryNode->setGeometry(geometry);
        geometryNode->setFlag(QSGNode::OwnsGeometry);

        material = new QSGFlatColorMaterial;
        material->setColor(Qt::white);

        geometryNode->setMaterial(material);
        geometryNode->setFlag(QSGNode::OwnsMaterial);

        transformNode->appendChildNode(geometryNode);
    }
    else
    {
        transformNode = static_cast<QSGTransformNode*>(oldNode);
        transformNode->setMatrix(QMatrix4x4(transform));
        geometryNode = static_cast<QSGGeometryNode*>(transformNode->childAtIndex(0));
        ((QSGFlatColorMaterial*) geometryNode->material())->setColor(Qt::white);

        geometry = geometryNode->geometry();
        geometry->allocate(verticesNumber);
    }

    QSGGeometry::Point2D *vertices = geometry->vertexDataAsPoint2D();

    float x,y;
    for (int i=0; i<verticesNumber; i++)
    {
        #ifdef GAIN_IN_DB
        x = i*width/(verticesNumber-1.f);
        y = height*(_buffer[i]+MAX_ATTENUATION_DB)/(MAX_GAIN_DB+MAX_ATTENUATION_DB);
        #else
        x = i*width/(verticesNumber-1.f);
        y = height*_buffer[i]/MAX_GAIN;
        #endif

        if(y < 0) y = 0;
        if(y > height) y = height;

        vertices[i].set(x,y);
    }

    geometryNode->markDirty(QSGNode::DirtyGeometry);
    geometryNode->markDirty(QSGNode::DirtyMaterial);

    return transformNode;
}
