#ifndef SQUARE_H
#define SQUARE_H

#include "Oscillator.h"

class Square : public Oscillator
{
public:
    Square();

    double step();
};

#endif //SQUARE_H
