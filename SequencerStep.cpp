#include "SequencerStep.h"

SequencerStep::SequencerStep(QObject* parent) :
    QObject(parent),
    _active(false)
{

}

bool SequencerStep::active()
{
    return _active;
}

void SequencerStep::setActive(bool active)
{
    _active = active;

    emit activeChanged(_active);
}
