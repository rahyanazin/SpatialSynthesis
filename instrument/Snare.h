#ifndef SNARE_H
#define SNARE_H

#include "Instrument.h"

#include "Envelope.h"
#include "Sine.h"
#include "DampedSine.h"
#include "WhiteNoise.h"

#include "Lowpass.h"

class Snare : public Instrument
{
    Q_OBJECT

public:
    explicit Snare(QObject* parent=nullptr);

    double step();

public slots:
    void tap();

    //Tone
    void setTone(double tone);

    //Amplitude Envelope
    void setAmpAttack(double attack);
    void setAmpDecay(double decay);
    void setAmpAttackCurve(double curve);
    void setAmpDecayCurve(double curve);
    Envelope* ampEnvelope();

    //temporary
    double ampAttackDefault();
    double ampDecayDefault();
    double ampAttackCurveDefault();
    double ampDecayCurveDefault();


private:
    WhiteNoise* _noise;
    Envelope* _noiseEnvelope;
    Lowpass _noiseFilter;

    Sine* _sine;
    Envelope* _sineEnvelope;
    DampedSine* _dampedSine;
};

#endif // SNARE_H
