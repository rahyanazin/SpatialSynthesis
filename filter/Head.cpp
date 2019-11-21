#include "Head.h"

#include <QObject>

#include <qmath.h>
#include <complex>
#include <unordered_map>

#include <HeadModelTable.h>

#define DEFAULT_SAMPLE_RATE     44100

Head::Head(QObject *parent) :
    Filter(parent),
    _sampleRate(DEFAULT_SAMPLE_RATE),
    _position(Left),
    _lastX1(0.0),
    _lastY1(0.0),
    _azimuth(45.0)
{
    new HeadModelTable();
    update();
}

void Head::setSampleRate(int sampleRate)
{
    _sampleRate = sampleRate;

    update();
}

void Head::set_position(int pos)
{
    _position = pos;

    update();
}

void Head::setAzimuth(double azimuth)
{
    _azimuth = azimuth;

    update();
}

void Head::update()
{
    a = 8.75;//100.0; //Head radius
    c = 340; //Sound speed
    alpha_min = 0.1;
    theta_min = 180.0;
    fs = _sampleRate;

    switch(_position){
        case Left:
            theta_inc = _azimuth+90.0;
        break;
        case Right:
            theta_inc = 90.0-_azimuth;
        break;
    }

    alpha = 1 + alpha_min/2.0 + (1-alpha_min/2)*cos(theta_inc*M_PI/theta_min);
    betha = c/a;

    a1 = (betha-fs)/(betha+fs);
    b0= (betha+alpha*fs)/(betha+fs);
    b1= (betha-alpha*fs)/(betha+fs);
}

double Head::process(double input)
{
    double y = b0*input + b1*_lastX1 - a1*_lastY1;

    _lastX1 = input;
    _lastY1 = y;

    if(y > 1.0 || y < -1.0){
        y = 0.0;
        _lastY1 = y;

    }

    return y;
}

//plot omega in range [0,pi]
double Head::transferFunction(double omega)
{
    double numRe = b0 + b1*qCos(omega);
    double numIm = -b1*qSin(omega);
    double denRe = 1 + a1*qCos(omega);
    double denIm = -a1*qSin(omega);

    double out = qSqrt((numRe*numRe + numIm*numIm)/(denRe*denRe + denIm*denIm));

    return out;

    /*std::complex<double> z(cos(omega), sin(omega));
    std::complex<double> Hz(0,0);

    Hz = (a0 + a1*pow(z,-1) + a2*pow(z,-2))/(b1*pow(z,-1) + b2*pow(z,-2));

    return Hz;*/
}
