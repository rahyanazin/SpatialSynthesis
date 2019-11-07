#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QQmlListProperty>

#include "Synthesizer.h"

#include "qdebug.h"

#define SEQUENCER_SIZE  16

class Engine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Synthesizer* synth READ synth CONSTANT)

public:
    explicit Engine(QObject* parent=nullptr);

    void setSampleRate(int sampleRate);

    void process(float* buffer, int frames);

    Synthesizer* synth();

signals:
    void sequencerChanged();

private:
    int _sampleRate;

    Synthesizer* _synth;
};

#endif // ENGINE_H
