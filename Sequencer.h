#ifndef SEQUENCER_H
#define SEQUENCER_H

#include <QObject>
#include <QQmlListProperty>

#include "SequencerStep.h"

#define DEFAULT_SAMPLE_RATE     44100
#define DEFAULT_TEMPO           0.5
#define DEFAULT_SIZE            16

class Sequencer : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int size READ size CONSTANT)
    Q_PROPERTY(double tempo READ tempo WRITE setTempo NOTIFY tempoChanged)
    Q_PROPERTY(QQmlListProperty<SequencerStep> steps READ steps CONSTANT)
    Q_PROPERTY(int currentStep READ currentStep NOTIFY currentStepChanged)

public:
    explicit Sequencer(QObject* parent=nullptr);

    int sampleRate();
    void setSampleRate(int sampleRate);

    int currentStep();

    int size();

    double tempo();
    void setTempo(double tempo);

    QQmlListProperty<SequencerStep> steps();

    void step();

public slots:
    bool setStep(int step);

    void clear();
    QString bpm();

signals:
    void currentStepChanged();
    void tempoChanged();
    void stepsChanged();
    void trigger();

private:
    int _sampleRate;

    double _tempo;

    int _step;
    int _counter;
    int _trigger;
    int _currentStep;

    QList<SequencerStep*> _steps;
};

#endif // SEQUENCER_H
