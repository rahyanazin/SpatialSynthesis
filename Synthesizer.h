#ifndef SYNTHESIZER_H
#define SYNTHESIZER_H

#include <QObject>

#include "Sine.h"
#include "Square.h"
#include "WhiteNoise.h"
#include "Head.h"
#include "Lowpass.h"

#include "TransferFunctionPlot.h"


#define DEFAULT_SAMPLE_RATE 44100


class Synthesizer : public QObject
{    
    enum{
        SineWave=0,
        SquareWave=1,
        Noise=2
    };

public:

    Q_OBJECT
    //Synthesis mode
    Q_PROPERTY(int mode READ mode WRITE setMode NOTIFY modeChanged)

public:

    explicit Synthesizer(QObject* parent=nullptr);

    void setSampleRate(int sampleRate);

    int mode();
    void setMode(int mode);

    double step();

public slots:
    //Signal Source
    void setTone(double tone);

    //Noise
    void setResonance(double resonance);

signals:
    void modeChanged();
    void runningChanged();

private:
    int _sampleRate;

    int _mode;

    //Sources
    Sine* _sine;
    Square* _square;
    WhiteNoise* _noise;

    Lowpass* _lowpass;
};

#endif // SYNTHESIZER_H
