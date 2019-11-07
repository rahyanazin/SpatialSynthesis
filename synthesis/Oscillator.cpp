#include "Oscillator.h"

#define DEFAULT_SAMPLE_RATE     44100.0

#include <qdebug.h>

Oscillator::Oscillator(QObject *parent) :
    QObject(parent),
    _phase(0.0),
    _dt(1.0/double(DEFAULT_SAMPLE_RATE)),
    _name("Oscillator"),
    _sampleRate(DEFAULT_SAMPLE_RATE),
    _modulation(1.0)
{
}

QString Oscillator::name()
{
    return _name;
}

int Oscillator::sampleRate()
{
    return _sampleRate;
}

void Oscillator::setSampleRate(int sampleRate)
{
    _sampleRate = sampleRate;

    _dt = 1.0/double(_sampleRate);
}

double Oscillator::frequency()
{
    return _frequency;
}

void Oscillator::setFrequency(double frequecy)
{
    _frequency = frequecy;
}

void Oscillator::setModulation(double modulation)
{
    _modulation = modulation;
}

double Oscillator::step()
{
    return 0.0;
}
