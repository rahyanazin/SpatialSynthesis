#ifndef BANDPASS_H
#define BANDPASS_H

#include <QObject>
#include <QQueue>
#include <QQuickItem>

#include "Filter.h"

class Bandpass : public Filter
{
    Q_OBJECT

public:
    explicit Bandpass(QObject *parent=nullptr);

    void setSampleRate(int sampleRate);

    void setCutoff(double cutoff);
    void setResonance(double resonance);

    void setModulation(double modulation);


    void update();

    double process(double input);

    void process(QVector<double>* input, QVector<double>* output);

    double transferFunction(double omega);

    double cutoff();

private:
    int _sampleRate;

    double _cutoffNormalized;
    double _resonanceNormalized;

    double _cutoff;
    double _resonance;
    double _modulation;

    double _rMin;
    double _rMax;


    //Filter variables
    double a0;
    double a1;
    double a2;
    double b1;
    double b2;
    double _lastLeftX1;
    double _lastLeftX2;
    double _lastLeftY1;
    double _lastLeftY2;
};

#endif // BANDPASS_H
