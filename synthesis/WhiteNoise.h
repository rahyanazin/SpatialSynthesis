#ifndef WHITENOISE_H
#define WHITENOISE_H

#include "Oscillator.h"

class WhiteNoise : public Oscillator
{
public:
    WhiteNoise();

    double step();
};

#endif // WHITENOISE_H
