#ifndef TOM_H
#define TOM_H

#include "Instrument.h"

#include "Envelope.h"
#include "DampedSine.h"
#include "Sine.h"
#include "WhiteNoise.h"

#include "Lowpass.h"

class Tom : public Instrument
{
    Q_OBJECT

public:
    explicit Tom(QObject* parent=nullptr);

    double step();

public slots:
    void tap();

    //Tone
    void setTone(double tone);

    //Amplitude Envelope
    Envelope* ampEnvelope();
    void setAmpAttack(double decay);
    void setAmpDecay(double decay);
    void setAmpAttackCurve(double decay);
    void setAmpDecayCurve(double decay);

    //temporary
    double ampAttackDefault();
    double ampDecayDefault();
    double ampAttackCurveDefault();
    double ampDecayCurveDefault();

private:
    Sine* _sine;
    Envelope* _sineEnvelope;
};

#endif // TOM_H
