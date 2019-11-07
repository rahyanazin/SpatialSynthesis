#include "Instrument.h"

//debug stuff
#include <qdebug.h>

Instrument::Instrument(QObject *parent) :
    Oscillator(parent),
    _saturation(0.5),
    _sequencer(nullptr)
{
    _name = "Instrument";
    _sequencer = new Sequencer(this);

    connect(_sequencer, SIGNAL(trigger()), SLOT(tap()));
}

QList<Synthesizer*> Instrument::instrument()
{
    return _synths;
}

Sequencer *Instrument::sequencer()
{
    return _sequencer;
}

double Instrument::step()
{
    return 0.0;
}

void Instrument::tap()
{
    for (Synthesizer *synth : _synths)
        synth->tap();
}

void Instrument::setSaturation(double saturation)
{
    _saturation = 10.0*saturation;
}
