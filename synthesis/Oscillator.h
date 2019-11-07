#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include <QObject>

class Oscillator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name CONSTANT)
public:

    explicit Oscillator(QObject *parent=nullptr);

    QString name();

    int sampleRate();
    void setSampleRate(int sampleRate);

    double frequency();
    virtual void setFrequency(double frequency);

    void setModulation(double modulation);

    virtual double step();

protected:
    double _phase;
    double _dt;

    QString _name;

    int _mode;

    int _sampleRate;

    double _frequency;
    double _modulation;
};

#endif // OSCILLATOR_H
