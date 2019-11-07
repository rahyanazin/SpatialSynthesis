#ifndef SINE_H
#define SINE_H

#include "Oscillator.h"

class Sine: public Oscillator
{
public:
    Sine();

    double step();
};

#endif // SINE_H
