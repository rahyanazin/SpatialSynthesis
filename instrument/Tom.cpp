#include "Tom.h"

#include <math.h>

Tom::Tom(QObject *parent) :
    Instrument(parent)
{
    _name = "Tom";

    //sine
    _sine = new Sine();

    //sine amplitude envelope
    _sineEnvelope = new Envelope();
    _sineEnvelope->setAttack(0.0012);
    _sineEnvelope->setAttackCurve(0.5);
    _sineEnvelope->setDecay(0.0625);
    _sineEnvelope->setDecayCurve(0.4);
    _sineEnvelope->setSustain(0.0);
    _sineEnvelope->setRelease(0.0);

    //saturation
    setSaturation(0.5);

    //default config
    setTone(0.5);
    setAmpAttack(ampAttackDefault());
    setAmpDecay(ampDecayDefault());
    setAmpAttackCurve(ampAttackCurveDefault());
    setAmpDecayCurve(ampDecayCurveDefault());
}

double Tom::ampAttackDefault()
{
    return 0.0012;
}

double Tom::ampDecayDefault()
{
    return 0.0625;
}

double Tom::ampAttackCurveDefault()
{
    return 1.0;
}

double Tom::ampDecayCurveDefault()
{
    return 0.4;
}

void Tom::tap()
{
    _sineEnvelope->on();
}

double Tom::step()
{
    _sequencer->step();

    return 0.25*_sineEnvelope->step()*_sine->step();
}

void Tom::setTone(double tone)
{
    _sine->setTone(120.0+80*tone);
}

Envelope *Tom::ampEnvelope()
{
    return _sineEnvelope;
}

void Tom::setAmpAttack(double attack)
{
    _sineEnvelope->setAttack(attack);
}

void Tom::setAmpDecay(double decay)
{
    _sineEnvelope->setDecay(decay);
}


void Tom::setAmpAttackCurve(double curve)
{
    _sineEnvelope->setAttackCurve(curve);
}

void Tom::setAmpDecayCurve(double curve)
{
    _sineEnvelope->setDecayCurve(curve);
}
