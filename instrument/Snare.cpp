#include "Snare.h"

#include <math.h>

//#define DAMPED_SINE

//debug stuff
#include <qdebug.h>

Snare::Snare(QObject *parent) :
    Instrument(parent)
{
    _name = "Snare";

    //noise
    _noise = new WhiteNoise();

    //noise envelope
    _noiseEnvelope = new Envelope();
    _noiseEnvelope->setAttack(0.005);
    _noiseEnvelope->setAttackCurve(0.75);
    _noiseEnvelope->setDecay(0.1);
    _noiseEnvelope->setDecayCurve(0.25);
    _noiseEnvelope->setSustain(0.0);
    _noiseEnvelope->setRelease(0.0);

    //noise filter
    _noiseFilter.setSampleRate(_sampleRate);
    _noiseFilter.setCutoff(100.0);

    //damped sine
    _dampedSine = new DampedSine();
    _dampedSine->setTone(20.0);

    //sine
    _sine = new Sine();

    ////sine amplitude envelope
    _sineEnvelope = new Envelope();
    _sineEnvelope->setAttack(0.25);
    _sineEnvelope->setAttackCurve(1.0);
    _sineEnvelope->setDecay(0.01);
    _sineEnvelope->setDecayCurve(0.4);
    _sineEnvelope->setSustain(0.0);
    _sineEnvelope->setRelease(0.0);

    //Saturation
    setSaturation(0.5);

    setTone(toneDefault());
    setAmpAttack(ampAttackDefault());
    setAmpDecay(ampDecayDefault());
    setAmpAttackCurve(ampAttackCurveDefault());
    setAmpDecayCurve(ampDecayCurveDefault());
}

double Snare::ampAttackDefault()
{
    return 0.0012;
}

double Snare::ampDecayDefault()
{
    return 0.02;
}

double Snare::ampAttackCurveDefault()
{
    return 1.0;
}

double Snare::ampDecayCurveDefault()
{
    return 0.4;
}

double Snare::step()
{
    _sequencer->step();

    #ifdef DAMPED_SINE
    return 0.7*(_noiseEnvelope->step()*_noiseFilter.process(_noise->step()) + 0.3*_dampedSine->step();
    #else
    return 0.5*(_noiseEnvelope->step()*_noiseFilter.process(_noise->step()) + 0.5*_sineEnvelope->step()*_sine->step());
    #endif
}

void Snare::tap()
{
    _dampedSine->tap();
    _noiseEnvelope->on();
    _sineEnvelope->on();
}

void Snare::setTone(double tone)
{
    _dampedSine->setTone(200.0+400*tone);
    _sine->setTone(100.0+300*tone);

    _noiseFilter.setCutoff(100.0+tone*4000);
}

void Snare::setAmpAttack(double attack)
{
    _sineEnvelope->setAttack(attack);
    _noiseEnvelope->setAttack(attack);
}

void Snare::setAmpDecay(double decay)
{
    _dampedSine->setDecay(1.0+39.0*decay);

    _sineEnvelope->setDecay(decay);
    _noiseEnvelope->setDecay(0.25*decay);
}

void Snare::setAmpAttackCurve(double curve)
{
    _sineEnvelope->setAttackCurve(curve);
    _noiseEnvelope->setAttackCurve(curve);
}

void Snare::setAmpDecayCurve(double curve)
{
    _sineEnvelope->setDecayCurve(curve);
    _noiseEnvelope->setDecayCurve(curve);
}

Envelope* Snare::ampEnvelope()
{
    return _noiseEnvelope;
}
