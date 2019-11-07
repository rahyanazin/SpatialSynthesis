#include "WhiteNoise.h"

#include <cstdlib>

//debug stuff
#include <qdebug.h>

WhiteNoise::WhiteNoise()
{
    _name = "White Noise";
}

double WhiteNoise::step()
{    
    return (2.0*((double)rand()/RAND_MAX)-1.0);
}
