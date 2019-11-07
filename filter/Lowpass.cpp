#include "Lowpass.h"

#include <QObject>

#include <qmath.h>
#include <complex>

Lowpass::Lowpass(QObject *parent) :
    Filter(parent)
{
    setSampleRate(44100);
    setCutoff(1000);
    setResonance(0.707);

    update();
}

void Lowpass::setSampleRate(int sampleRate)
{
    _sampleRate = sampleRate;

    update();
}

void Lowpass::setCutoff(double cutoff)
{
    _cutoff = cutoff;

    update();
}

void Lowpass::setResonance(double resonance)
{
    _resonance = resonance;

    update();
}

void Lowpass::update()
{
    //setting last values to zero
    _lastLeftX1 = 0;
    _lastLeftX2 = 0;
    _lastLeftY1 = 0;
    _lastLeftY2 = 0;

    //compute filter coefficients
    double thetaC = 2*M_PI*_cutoff/_sampleRate;
    double beta = 0.5*(1 - qSin(thetaC)/(2*_resonance))/(1 + qSin(thetaC)/(2*_resonance));
    double gama = (0.5 + beta)*qCos(thetaC);
    a0 = (0.5 + beta - gama)/2.f;
    a1 = 0.5 + beta - gama;
    a2 = (0.5 + beta - gama)/2.f;
    b1 = -2.f*gama;
    b2 = 2.f*beta;
}

float Lowpass::process(float input)
{
    float y = a0*input + a1*_lastLeftX1 + a2*_lastLeftX2 - b1*_lastLeftY1 - b2*_lastLeftY2;

    _lastLeftX2 = _lastLeftX1;
    _lastLeftX1 = input;
    _lastLeftY2 = _lastLeftY1;
    _lastLeftY1 = y;

    return y;
}

void Lowpass::process(QVector<float>* input, QVector<float>* output)
{
    output->clear();

    int nSamples = input->size();
    float sample, y;

    for (int i=0; i < nSamples; i++)
    {
        sample = input->at(i);

        y = a0*sample + a1*_lastLeftX1 + a2*_lastLeftX2 - b1*_lastLeftY1 - b2*_lastLeftY2;

        output->append(y);

        _lastLeftX2 = _lastLeftX1;
        _lastLeftX1 = sample;
        _lastLeftY2 = _lastLeftY1;
        _lastLeftY1 = y;
    }
}

//plot omega in range [0,pi]
double Lowpass::transferFunction(double omega)
{
    double numRe = a0 + a1*qCos(omega) + a2*qCos(2*omega);
    double numIm = -a1*qSin(omega) -a2*qSin(2*omega);
    double denRe = 1 + b1*qCos(omega) + b2*qCos(2*omega);
    double denIm = -b1*qSin(omega) -b2*qSin(2*omega);

    double out = qSqrt((numRe*numRe + numIm*numIm)/(denRe*denRe + denIm*denIm));

    return out;   

    /*std::complex<double> z(cos(omega), sin(omega));
    std::complex<double> Hz(0,0);

    Hz = (a0 + a1*pow(z,-1) + a2*pow(z,-2))/(b1*pow(z,-1) + b2*pow(z,-2));

    return Hz;*/
}
