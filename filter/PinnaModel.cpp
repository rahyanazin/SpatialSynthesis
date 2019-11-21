#include "PinnaModel.h"

#include <QObject>

#include <qmath.h>
#include <complex>

#include <PinnaModelTable.h>

#define DEFAULT_SAMPLE_RATE     44100

PinnaModel::PinnaModel(QObject *parent) :
    Filter(parent),
    _sampleRate(DEFAULT_SAMPLE_RATE),
    _elevation(0.0),
    _elevation_running(true)
{
    _tables = new PinnaModelTable();

    update();
}

void PinnaModel::setSampleRate(int sampleRate)
{
    _sampleRate = sampleRate;

    update();
}

void PinnaModel::setElevation(double elevation)
{
    _elevation = elevation;

    reset();

    update();
}

void PinnaModel::setElevationRunning(bool running)
{
    _elevation_running = running;

    reset();
}

void PinnaModel::update()
{
    double res1_V0;
    double res1_H0;
}

void PinnaModel::reset()
{
    //qDebug() << "reseting";
}

double PinnaModel::process(double input)
{

    double y = input;

    if(y > 1.0 || y < -1.0){
        y = 0.0;
        //_lastY1 = y;
    }

    return y;
}

//plot omega in range [0,pi]
double PinnaModel::transferFunction(double omega)
{
    double numRe = 0.0;
    double numIm = 0.0;
    double denRe = 0.0;
    double denIm = 0.0;

    double out = qSqrt((numRe*numRe + numIm*numIm)/(denRe*denRe + denIm*denIm));

    return out;

    /*std::complex<double> z(cos(omega), sin(omega));
    std::complex<double> Hz(0,0);

    Hz = (a0 + a1*pow(z,-1) + a2*pow(z,-2))/(b1*pow(z,-1) + b2*pow(z,-2));

    return Hz;*/
}
