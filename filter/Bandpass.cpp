#include "Bandpass.h"

#include <QObject>

#include <qmath.h>
#include <complex>

#define DEFAULT_SAMPLE_RATE     44100
#define DEFAULT_CUTOFF          16500
#define DEFAULT_RESONANCE       0.4

#define CUTOFF_MIN              1200.0
#define CUTOFF_MAX              20940.0

#define RESONANCE_MIN           0.25
#define RESONANCE_MAX           0.95

Bandpass::Bandpass(QObject *parent) :
    Filter(parent),
    _lastLeftX1(0.0),
    _lastLeftX2(0.0),
    _lastLeftY1(0.0),
    _lastLeftY2(0.0),
    _sampleRate(DEFAULT_SAMPLE_RATE),
    _cutoff(DEFAULT_CUTOFF),
    _resonanceNormalized(DEFAULT_RESONANCE),
    _rMax(double(DEFAULT_SAMPLE_RATE)),
    _modulation(1.0)
{
    update();
}

void Bandpass::setSampleRate(int sampleRate)
{
    _sampleRate = sampleRate;

    update();
}

void Bandpass::setCutoff(double cutoff)
{
    _cutoff = 20.0 + (double(_sampleRate)/2.0 - 20.0)*cutoff;

    update();
}

void Bandpass::setResonance(double resonance)
{
    _resonanceNormalized = resonance;

    if(_resonanceNormalized < 0.25)
        _resonanceNormalized = 0.25;

    if(_resonanceNormalized > 0.95)
        _resonanceNormalized = 0.95;

    update();
}

void Bandpass::setModulation(double modulation)
{
    _modulation = modulation;

    update();
}

void Bandpass::update()
{  
    double cutoff = _cutoff*_modulation;

    if(cutoff < CUTOFF_MIN)
        cutoff = CUTOFF_MIN;

    if(cutoff > CUTOFF_MAX)
        cutoff = CUTOFF_MAX;

    _rMin = 2.0*cutoff/double(_sampleRate);
    //_rMax = _sampleRate;

    _resonance = _rMin*qPow(_rMax/_rMin, _resonanceNormalized);

    //compute filter coefficients
    double thetaC = 2.0*M_PI*cutoff/_sampleRate;
    double angle = thetaC/(2.0*_resonance);
    double beta = 0.5*(1.0 - qTan(angle))/(1.0 + qTan(angle));
    double gama = (0.5 + beta)*qCos(thetaC);

    a0 = 0.5 - beta;
    a1 = 0.0;
    a2 = -(0.5-beta);
    b1 = -2.0*gama;
    b2 = 2.0*beta;
}

double Bandpass::process(double input)
{
    double y = a0*input + a1*_lastLeftX1 + a2*_lastLeftX2 - b1*_lastLeftY1 - b2*_lastLeftY2;

    _lastLeftX2 = _lastLeftX1;
    _lastLeftX1 = input;
    _lastLeftY2 = _lastLeftY1;
    _lastLeftY1 = y;

    if(y > 1.0 || y < -1.0){
        //y = (2.0*((double)rand()/RAND_MAX)-1.0);
        y = 0.0;
        _lastLeftY1 = y;

    }

    //return tanh(y);
    //return tanh(y*(1.0+10.0/*_saturation*/));
    return y;


}

void Bandpass::process(QVector<double>* input, QVector<double>* output)
{
    output->clear();

    int nSamples = input->size();
    double sample, y;

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
double Bandpass::transferFunction(double omega)
{
    double numRe = a0 + a1*qCos(omega) + a2*qCos(2*omega);
    double numIm = -a1*qSin(omega) -a2*qSin(2*omega);
    double denRe = 1 + b1*qCos(omega) + b2*qCos(2*omega);
    double denIm = -b1*qSin(omega) -b2*qSin(2*omega);

    double out = qSqrt((numRe*numRe + numIm*numIm)/(denRe*denRe + denIm*denIm));

    return out;
}

double Bandpass::cutoff()
{
    return _cutoff;
}
