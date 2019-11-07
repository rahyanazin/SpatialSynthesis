#ifndef HIHAT_H
#define HIHAT_H

#include "Instrument.h"

#include "WhiteNoise.h"
#include "Bandpass.h"

class HiHat : public Instrument
{
    Q_OBJECT

public:
    explicit HiHat(QObject* parent=nullptr);

    double step();

public slots:
    void tap();

    //Tone
    void setTone(double tone);

    //Resonane
    void setParam(double resonance);
    QString paramID();


    //Amplitude Envelope
    Envelope* ampEnvelope();
    void setAmpAttack(double attack);
    void setAmpDecay(double decay);
    void setAmpAttackCurve(double curve);
    void setAmpDecayCurve(double curve);

    //temporary
    double toneDefault();
    double paramDefault();
    double ampAttackDefault();
    double ampDecayDefault();
    double ampDecayCurveDefault();
    double ampAttackCurveDefault();

protected:
    WhiteNoise* _whiteNoise;
    Bandpass* _bandpass;

    Envelope* _noiseEnvelope;
};

#endif // HIHAT_H
