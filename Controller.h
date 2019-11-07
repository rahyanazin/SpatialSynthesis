#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QVector>

#include <rtaudio/RtAudio.h>

#include "Synthesizer.h"
#include "SpatialSound.h"

#include "SignalPlot.h"
#include "SpectrumPlot.h"

class Controller : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Synthesizer* synth READ synth CONSTANT)
    Q_PROPERTY(SpatialSound* spatialSound READ spatialSound CONSTANT)
    Q_PROPERTY(SignalPlot* signalPlot READ signalPlot WRITE setSignalPlot NOTIFY signalPlotChanged)
    Q_PROPERTY(SpectrumPlot* spectrumPlot READ spectrumPlot WRITE setSpectrumPlot NOTIFY spectrumPlotChanged)

public:
    explicit Controller(QObject* parent=nullptr);
    ~Controller();

    void process(float* output, int frames);

    Synthesizer* synth();
    SpatialSound* spatialSound();

    SignalPlot* signalPlot();
    void setSignalPlot(SignalPlot* signalPlot);
    SpectrumPlot* spectrumPlot();
    void setSpectrumPlot(SpectrumPlot* spectrumPlot);

signals:
    void signalPlotChanged();
    void spectrumPlotChanged();
    void runningChanged();

public slots:
    //Streaming
    void start();
    void stop();

private:
    RtAudio* _audio;
    RtAudio::StreamParameters _streamOutput;

    SignalPlot* _signalPlot;
    SpectrumPlot* _spectrumPlot;

    Synthesizer* _synth;
    SpatialSound* _spatialSound;

    unsigned int _bufferSize;
    int _channels;
    int _sampleRate;
};

#endif // CONTROLLER_H
