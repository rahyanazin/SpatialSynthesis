#include "Kick.h"

#include <math.h>

//#define DAMPED_SINE

//debug stuff
#include <qdebug.h>

Kick::Kick(QObject *parent) :
    Instrument(parent)
{    
    _name = "Kick";

    _actuator = new Synthesizer();
    _source = new Synthesizer();

    _actuator->ampEnvelope()->setAttack(0.1);
    _actuator->ampEnvelope()->setDecay(0.6);
    _actuator->ampEnvelope()->setSustain(0.0);
    _actuator->ampEnvelope()->setRelease(0.0);

    _actuator->setSampleRate(_sampleRate);
    _actuator->setCutoff(100.0);

    _source->setSampleRate(_sampleRate);
    _source->setMode(0);
    _source->setOscID(0);
    _source->setAmpModID(0);
    _source->setPitchModID(0);

    _source->ampEnvelope()->setActive(true);
    _source->ampEnvelope()->setAttack(0.1);
    _source->ampEnvelope()->setAttackCurve(0.6);
    _source->ampEnvelope()->setDecay(1.0);
    _source->ampEnvelope()->setDecayCurve(0.4);
    _source->ampEnvelope()->setSustain(0.0);
    _source->ampEnvelope()->setRelease(0.0);

    _source->pitchEnvelope()->setActive(false);

    _synths.append(_actuator);
    _synths.append(_source);

    //Saturation
    setSaturation(0.5);

}

double Kick::ampAttackDefault()
{
    return 0.0012;
}

double Kick::ampDecayDefault()
{
    return 0.0625;
}

double Kick::ampAttackCurveDefault()
{
    return 1.0;
}

double Kick::ampDecayCurveDefault()
{
    return 0.4;
}


double Kick::step()
{   
    _sequencer->step();

    double v = _source->step();

    return v;
}

void Kick::tap()
{
    _actuator->tap();
    _source->tap();
}

void Kick::setTone(double tone)
{
    _source->setTone(0.01*tone);
    _actuator->setCutoff(0.01*tone);
}

void Kick::setAmpAttack(double attack)
{
    _source->ampEnvelope()->setAttack(0.1*attack);
}

void Kick::setAmpDecay(double decay)
{
    _source->ampEnvelope()->setDecay(decay);
}

void Kick::setAmpAttackCurve(double curve)
{
    _source->ampEnvelope()->setAttackCurve(curve);
}
void Kick::setAmpDecayCurve(double curve)
{
    _source->ampEnvelope()->setDecayCurve(curve);
}

Envelope* Kick::ampEnvelope()
{
    return _source->ampEnvelope();
}
