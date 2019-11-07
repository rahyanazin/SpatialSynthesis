#include "HiHat.h"

#include <math.h>

//debug stuff
#include <qdebug.h>

HiHat::HiHat(QObject *parent) :
    Instrument(parent)
{
    _name = "HitHat";

    _whiteNoise = new WhiteNoise();

    _bandpass = new Bandpass();
    _bandpass->setSampleRate(_sampleRate);
    _bandpass->setCutoff(0.75);
    _bandpass->setResonance(0.5);

    //noise envelope
    _noiseEnvelope = new Envelope();
    _noiseEnvelope->setAttack(0.01);
    _noiseEnvelope->setDecay(0.03);
    _noiseEnvelope->setSustain(0.0);
    _noiseEnvelope->setRelease(0.0);

    //default config
    setSaturation(0.5);
    setTone(toneDefault());
    setParam(paramDefault());
    setAmpAttack(ampAttackDefault());
    setAmpDecay(ampDecayDefault());
    setAmpAttackCurve(ampAttackCurveDefault());
    setAmpDecayCurve(ampDecayCurveDefault());
}

double HiHat::toneDefault()
{
    return 0.86;
}

double HiHat::paramDefault()
{
    return 0.42;
}

double HiHat::ampAttackDefault()
{
    return 0.0012;
}

double HiHat::ampDecayDefault()
{
    return 0.0625;
}

double HiHat::ampAttackCurveDefault()
{
    return 1.0;
}

double HiHat::ampDecayCurveDefault()
{
    return 0.4;
}

void HiHat::tap()
{
    _noiseEnvelope->on();
}

double HiHat::step()
{
    _sequencer->step();

    return _noiseEnvelope->step()*_bandpass->process(_whiteNoise->step());
}

void HiHat::setTone(double tone)
{
    _bandpass->setCutoff(tone);
}

void HiHat::setParam(double resonance)
{
    _bandpass->setResonance(resonance);
}

QString HiHat::paramID()
{
    return "Resonance";
}

void HiHat::setAmpAttack(double attack)
{
    _noiseEnvelope->setAttack(attack);
}

void HiHat::setAmpDecay(double decay)
{
    _noiseEnvelope->setDecay(decay);
}

void HiHat::setAmpAttackCurve(double curve)
{
    _noiseEnvelope->setAttackCurve(curve);
}

void HiHat::setAmpDecayCurve(double curve)
{
    _noiseEnvelope->setDecayCurve(curve);
}

Envelope *HiHat::ampEnvelope()
{
    return _noiseEnvelope;
}


