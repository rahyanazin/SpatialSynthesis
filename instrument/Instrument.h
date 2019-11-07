#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <QObject>

#include "Synthesizer.h"
#include "Oscillator.h"
#include "Sequencer.h"

class Instrument : public Oscillator
{
    Q_OBJECT
    Q_PROPERTY(Sequencer* sequencer READ sequencer CONSTANT)
    Q_PROPERTY(QList<Synthesizer*> instrument READ instrument CONSTANT)

public:
    explicit Instrument(QObject *parent=nullptr);

    QList<Synthesizer*> instrument();

    Sequencer* sequencer();

    virtual double step();

public slots:
    void tap();

    void setSaturation(double saturation);

signals:
    void sequencerChanged();

protected:
    double _saturation;

    Sequencer* _sequencer;

    QList<Synthesizer*> _synths;
};

#endif // INSTRUMENT_H
