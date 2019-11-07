#ifndef KICK_H
#define KICK_H

#include "Instrument.h"

#include "Envelope.h"
#include "Sine.h"
#include "DampedSine.h"
#include "WhiteNoise.h"

#include "Lowpass.h"

class Kick : public Instrument
{
    Q_OBJECT

public:
    explicit Kick(QObject* parent=nullptr);

    double step();

public slots:
    void tap();

    void setTone(double tone);

    Envelope* ampEnvelope();
    void setAmpAttack(double attack);
    void setAmpDecay(double release);
    void setAmpAttackCurve(double curve);
    void setAmpDecayCurve(double curve);

    //temporary
    double ampAttackDefault();
    double ampDecayDefault();
    double ampAttackCurveDefault();
    double ampDecayCurveDefault();

private:
    Synthesizer* _actuator;
    Synthesizer* _source;
};

#endif // KICK_H
