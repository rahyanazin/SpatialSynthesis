#include "Engine.h"

#include <qmath.h>

Engine::Engine(QObject *parent) :
    QObject(parent),
    _synth(nullptr)
{
    _synth = new Synthesizer();
}

void Engine::process(float *output, int frames)
{
    float v;

    for (int i=0; i<frames; i++)
    {
        v = 0;

        if(_synth)
            v += _synth->step();

        *output++ = v; //left
        *output++ = v; //right
    }
}

Synthesizer *Engine::synth()
{
    return _synth;
}

void Engine::setSampleRate(int sampleRate)
{
    _sampleRate = sampleRate;
}
