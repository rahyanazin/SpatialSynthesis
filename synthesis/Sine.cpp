#include "Sine.h"
#include <qmath.h>
#include <qdebug.h>

#define DEFAULT_FREQUENCY   440.0

Sine::Sine()
{
    _name = "Sine";

    setFrequency(DEFAULT_FREQUENCY);
}

double Sine::step()
{
    double frequency = _frequency*_modulation;
    double frequencyAbs = 1.0/abs(frequency);

    while (_phase >= frequencyAbs)
        _phase -= frequencyAbs;

    double v = sin(2.0*M_PI*frequency*_phase);

    _phase += _dt;

    return v;
}
