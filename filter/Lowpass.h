#ifndef FILTERSECONDORDER_H
#define FILTERSECONDORDER_H

#include <QObject>
#include <QQueue>
#include <QQuickItem>

#include "Filter.h"

class Lowpass : public Filter
{
    Q_OBJECT

public:
    explicit Lowpass(QObject *parent=nullptr);

    void setSampleRate(int sampleRate);

    void setCutoff(double cutoff);
    void setResonance(double resonance);

    void update();

    float process(float input);

    void process(QVector<float>* input, QVector<float>* output);

    double transferFunction(double omega);

private:
    //Filter param
    double _resonance;
    double _cutoff;
    int _sampleRate;

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

#endif // FILTERSECONDORDER_H
