#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QVector>

#include <rtaudio/RtAudio.h>

#include "Synthesizer.h"
#include "SpatialSound.h"

#include "SignalPlot.h"
#include "SpectrumPlot.h"

#include "CIPIC.h"

class Controller : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    Q_PROPERTY(Synthesizer* synth READ synth CONSTANT)
    Q_PROPERTY(SpatialSound* spatialSound READ spatialSound CONSTANT)
    Q_PROPERTY(SignalPlot* signalLeft READ signalLeft WRITE setSignalLeft NOTIFY signalLeftChanged)
    Q_PROPERTY(SignalPlot* signalRight READ signalRight WRITE setSignalRight NOTIFY signalRightChanged)
    Q_PROPERTY(SpectrumPlot* spectrumLeft READ spectrumLeft WRITE setSpectrumLeft NOTIFY spectrumLeftChanged)
    Q_PROPERTY(SpectrumPlot* spectrumRight READ spectrumRight WRITE setSpectrumRight NOTIFY spectrumRightChanged)

public:
    explicit Controller(QObject* parent=nullptr);
    ~Controller();

    void signalProcess(float *output, float *output_left, float*output_right, int frames);
    void process(float* output, int frames);

    bool running();
    void setRunning(bool running);

    Synthesizer* synth();
    SpatialSound* spatialSound();

    SignalPlot* signalLeft();
    void setSignalLeft(SignalPlot* signalLeft);
    SignalPlot* signalRight();
    void setSignalRight(SignalPlot* signalRight);

    SpectrumPlot* spectrumLeft();
    void setSpectrumLeft(SpectrumPlot* spectrumLeft);
    SpectrumPlot* spectrumRight();
    void setSpectrumRight(SpectrumPlot* spectrumRight);

signals:
    void runningChanged();
    void signalLeftChanged();
    void signalRightChanged();
    void spectrumLeftChanged();
    void spectrumRightChanged();

public slots:
    //Streaming
    void start();
    void stop();

private:
    RtAudio* _audio;
    RtAudio::StreamParameters _streamOutput;

    bool _running;

    SignalPlot* _signalLeft;
    SignalPlot* _signalRight;

    SpectrumPlot* _spectrumLeft;
    SpectrumPlot* _spectrumRight;

    Synthesizer* _synth;
    SpatialSound* _spatialSound;

    unsigned int _bufferSize;
    int _channels;
    int _sampleRate;

    CIPIC* cipic;
};

#endif // CONTROLLER_H
