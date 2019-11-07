#ifndef SPECTRUMPLOT_H
#define SPECTRUMPLOT_H

#include <QQuickItem>
#include <QQuickPaintedItem>
#include <QQueue>

#include <fftw3.h>
#define FFT_SIZE 8192

class SpectrumPlot : public QQuickItem
{
    Q_OBJECT

public:
    SpectrumPlot(QQuickItem *parent=0);
    ~SpectrumPlot();

    QSGNode* updatePaintNode(QSGNode *, UpdatePaintNodeData *);

    void process(float *buffer, int frames);

    void setSampleRate(float sampleRate);
protected:
    void timerEvent(QTimerEvent *event);

private:
    int _size;
    float _sampleRate;

    void configFFT();

    QQueue<float> _signal;
    QVector<float> _window;
    float _buffer[FFT_SIZE/2];

    double* _fft_in;
    fftw_complex* _fft_out;
    fftw_plan _fft_plan;
    int _fft_outlen;
    bool _fftReady;
};

#endif // SPECTRUMPLOT_H
