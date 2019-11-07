#include "Sequencer.h"

#include <QPainter>
#include <QMatrix>

//#define DEFAULT_GROOVE

//debug stuff
#include <qdebug.h>

Sequencer::Sequencer(QObject* parent) :
    QObject(parent),
    _currentStep(0),
    _sampleRate(DEFAULT_SAMPLE_RATE),
    _tempo(DEFAULT_TEMPO),
    _step(-1),
    _counter(-1)
{
    setSampleRate(DEFAULT_SAMPLE_RATE);
    setTempo(DEFAULT_TEMPO);

    _steps.clear();
    for(int i=0; i<DEFAULT_SIZE; i++)
        _steps.append(new SequencerStep());

    #ifdef DEFAULT_GROOVE
    for(int i=0; i<DEFAULT_SIZE; i++)
        if(i%4 == 3)
            _steps.at(i)->setActive(true);
    #endif
}

int Sequencer::sampleRate()
{
    return _sampleRate;
}

void Sequencer::setSampleRate(int sampleRate)
{
    _sampleRate = sampleRate;

    _trigger = _tempo*double(_sampleRate)/1000.0;
}

int Sequencer::currentStep()
{
    return _currentStep;
}

int Sequencer::size()
{
    return DEFAULT_SIZE;
}

double Sequencer::tempo()
{
    return _tempo;
}

void Sequencer::setTempo(double tempo)
{
    _tempo = 60.0+(120.0)*tempo;

    _trigger = (15.0/_tempo)*double(_sampleRate);

    emit tempoChanged();
}

QQmlListProperty<SequencerStep> Sequencer::steps()
{
    return QQmlListProperty<SequencerStep>(this, _steps);
}

void Sequencer::step()
{
    _counter = (_counter+1)%_trigger;

    if (_counter==0)
    {
        _step = (_step+1)%DEFAULT_SIZE;

        _currentStep = _step;

        emit currentStepChanged();

        if (_steps.at(_step)->active())
            emit trigger();
    }
}

bool Sequencer::setStep(int step)
{    
    _steps.at(step)->setActive(!_steps.at(step)->active());

    return _steps.at(step)->active();
}

void Sequencer::clear()
{
    for (int i=0; i<DEFAULT_SIZE; i++)
        _steps.at(i)->setActive(false);
}

QString Sequencer::bpm()
{
    return QString::number(_tempo);
}
