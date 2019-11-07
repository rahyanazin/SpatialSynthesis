#include "Cymbals.h"

#include "qdebug.h"


Cymbals::Cymbals(QObject *parent) :
    Instrument(parent)
{
    setSampleRate(44100);

    _modulationIndex = 1.0f;
    _modulator.setFrequency(1047.f);
    _modulatorFrequency = 1047.f;
    _carrier.setFrequency(2490.f);
    _carrierFrequency = 2490.f;

    _bandpass.setCutoff(1000.f);
    _bandpass.setResonance(1.0);

    _highpass.setCutoff(2640.0);
    _highpass.setResonance(0.707);


    _actuatorEnvelope.setAttack(0.5);
    _actuatorEnvelope.setDecay(201);
    _actuatorEnvelope.setSustain(0);
    _actuatorEnvelope.setRelease(0);

    _signalEnvelope.setAttack(219);
    _signalEnvelope.setDecay(3700);
    _signalEnvelope.setSustain(0);
    _signalEnvelope.setRelease(0);

    _envelope.setAttack(0.5);
    _envelope.setDecay(738);
    _envelope.setSustain(0);
    _envelope.setRelease(0);
}

void Cymbals::setSampleRate(int sampleRate)
{
    _sampleRate = sampleRate;
    _modulator.setSampleRate(sampleRate);
    _carrier.setSampleRate(sampleRate);
    _actuatorEnvelope.setSampleRate(sampleRate);
    _signalEnvelope.setSampleRate(sampleRate);
    _bandpass.setSampleRate(sampleRate);
    _highpass.setSampleRate(sampleRate);
}

void Cymbals::setActuatorTone(float tone)
{
    _carrierFrequency = 4000*tone;
}

void Cymbals::setActuatorDuration(float duration)
{
    _actuatorEnvelope.setDecay(1000.f*duration);
}

void Cymbals::setSignalTone(float tone)
{
    _modulatorFrequency = 4000*tone;
    //_carrierFrequency = (20.f+21980.f*tone);
    //_modulatorFrequency = (20.f+21980.f*tone);
}

void Cymbals::setSignalDecay(float decay)
{
    _signalEnvelope.setDecay(1.f + 999.f*decay);
}

void Cymbals::impulse()
{
    _actuatorEnvelope.on();
    _signalEnvelope.on();
}

double Cymbals::step()
{    
    _carrier.setFrequency(_carrierFrequency+_modulationIndex*_modulatorFrequency*_modulator.step());

    float actuatorEnvelopeStep = _actuatorEnvelope.step();
    float carrierOut = _carrier.step();

    _bandpass.setCutoff(1000*actuatorEnvelopeStep);

    float v1 = _bandpass.process(carrierOut*actuatorEnvelopeStep);
    float v2 = _highpass.process(carrierOut*_signalEnvelope.step());

    return v1+v2;
}
