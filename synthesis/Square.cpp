#include "Square.h"

#include <qdebug.h>

#define DEFAULT_FREQUENCY 440.0

Square::Square()
{
    _name = "Square";

    setFrequency(DEFAULT_FREQUENCY);
}
double Square::step()
{        
    double frequency = _frequency*_modulation;
    double frequencyAbs = 1.0/abs(frequency);

    while (_phase >= frequencyAbs)
        _phase -= frequencyAbs;

    double v;

    if(_phase < 0.5*1.0/_frequency)
        v = 1.0;

    else
        v = -1.0;

    _phase += _dt;

    return v;
}

