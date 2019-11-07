#ifndef CYMBALS_H
#define CYMBALS_H

#include "Instrument.h"

#include "Envelope.h"

#include "Square.h"
#include "Sine.h"

#include "Bandpass.h"
#include "Highpass.h"

class Cymbals : public Instrument
{
    Q_OBJECT

public:
    explicit Cymbals(QObject* parent=nullptr);

    void setSampleRate(int sampleRate);

    void setModulationIndex(float modulationIndex);
    void setModulatorFrequency(float modulatorFrequency);
    void setCarrierFrequency(float carrierFrequency);

    void setActuatorTone(float tone);
    void setActuatorDuration(float duration);

    void setSignalTone(float tone);
    void setSignalDecay(float decay);

    //void setSaturation(float saturation);

    void impulse();

    double step();

private:
    int _sampleRate;

    Square _modulator;
    Square _carrier;
    Sine _sineWave;

    float _modulationIndex;
    float _modulatorFrequency;
    float _carrierFrequency;

    Envelope _actuatorEnvelope;
    Envelope _signalEnvelope;
    Envelope _envelope;

    Bandpass _bandpass;
    Highpass _highpass;
};

#endif // CYMBALS_H
