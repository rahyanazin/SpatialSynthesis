#include "HeadModel.h"

#include <QObject>

#include <qmath.h>
#include <complex>

#include <Table.h>

#define DEFAULT_SAMPLE_RATE     44100

#define DEFAULT_HEAD_RADIUS     8.75//100.0

HeadModel::HeadModel(QObject *parent) :
    Filter(parent),
    _sampleRate(DEFAULT_SAMPLE_RATE),
    _position(Left),
    _pho_running(true),
    _azimuth_running(true),
    _azimuth(0.0),
    _headRadius(DEFAULT_HEAD_RADIUS),
    _pho(100.5),
    _lastX1(0.0),
    _lastX2(0.0),
    _lastY1(0.0),
    _lastY2(0.0)
{
    _tables = new Table();

    update();
}

void HeadModel::setSampleRate(int sampleRate)
{
    _sampleRate = sampleRate;

    update();
}

void HeadModel::set_position(int pos)
{
    _position = pos;

    update();
}

void HeadModel::setAzimuth(double azimuth)
{
    _azimuth = azimuth;

    reset();

    update();
}

void HeadModel::setAzimuthRunning(bool running)
{
    _azimuth_running = running;

    reset();
}

void HeadModel::setPho(double pho)
{
    _pho = pho;

    reset();

    update();
}

void HeadModel::setPhoRunning(bool running)
{
    _pho_running = running;

    reset();
}

void HeadModel::update()
{
    //a = 8.75/100.0; //Head radius
    c = 340.0; //Sound speed
    switch(_position){
        case Left:
            theta_inc = 90.0+_azimuth;
        break;
        case Right:
            theta_inc = 90.0-_azimuth;
        break;
    }

    //Long Distance Filter Stuff
    alpha_min = 0.1;
    theta_min = 180.0;
    fs = _sampleRate;

    alpha = 1.0 + alpha_min/2.0 + (1.0-alpha_min/2.0)*cos(theta_inc*M_PI/theta_min);
    betha = c/_headRadius;

    a_a1 = (betha-fs)/(betha+fs);
    a_b0= (betha+alpha*fs)/(betha+fs);
    a_b1= (betha-alpha*fs)/(betha+fs);

    //Near Field Head Model Filter Stuff
    //pho = _radius/a;
    gain_dc = _tables->dc_gain(_pho, theta_inc);
    gain_high = _tables->high_frequency_gain(_pho, theta_inc);
    fc = _tables->shelving_filter_cutoff(_pho, theta_inc);
    V0 = pow(10.0, gain_high/20.0);
    ac = (V0*tan(M_PI*fc/fs)-1.0)/(V0*tan(M_PI*fc/fs)+1.0);
    m = (V0-1.0)/2.0;
    n = ac;

    p_b0 = 1.0+m-m*n;
    p_b1 = m*n+n-m;
    p_a1 = n;

    //Head Model Filter Stuff
    b0 = gain_dc*p_b0*a_b0;
    b1 = gain_dc*(p_b0*a_b1+p_b1*a_b0);
    b2 = gain_dc*p_b1*a_b1;
    a1 = p_a1+a_a1;
    a2 = p_a1*a_a1;
}

void HeadModel::reset()
{
    qDebug() << "reseting";

    _lastX1 = 0.0;
    _lastX2 = 0.0;
    _lastY1 = 0.0;
    _lastY2 = 0.0;
}

double HeadModel::process(double input)
{

    double y = input;

    if (_pho_running && _azimuth_running)
        y = b0*input + b1*_lastX1 + b2*_lastX2 - a1*_lastY1 - a2*_lastY2;

    if (_pho_running && !_azimuth_running)
        y = p_b0*input + p_b1*_lastX1 - p_a1*_lastY1;

    if (!_pho_running && _azimuth_running)
        y = a_b0*input + a_b1*_lastX1 - a_a1*_lastY1;

    _lastX2 = _lastX1;
    _lastX1 = input;
    _lastY2 = _lastY1;
    _lastY1 = y;

    if(y > 1.0 || y < -1.0){
        y = 0.0;
        _lastY1 = y;
    }

    return y;
}

//plot omega in range [0,pi]
double HeadModel::transferFunction(double omega)
{
    double numRe = 0.0;
    double numIm = 0.0;
    double denRe = 0.0;
    double denIm = 0.0;

    if (_pho_running && _azimuth_running) {
        numRe = b0 + b1*qCos(omega) + b2*qCos(2*omega);
        numIm = -b1*qSin(omega) -b2*qSin(2*omega);
        denRe = 1 + a1*qCos(omega) + a2*qCos(2*omega);
        denIm = -a1*qSin(omega) -a2*qSin(2*omega);
    }

    if (_pho_running && !_azimuth_running) {
        numRe = p_b0 + p_b1*qCos(omega);
        numIm = -p_b1*qSin(omega);
        denRe = 1 + p_a1*qCos(omega);
        denIm = -p_a1*qSin(omega);
    }

    if (!_pho_running && _azimuth_running) {
        numRe = a_b0 + a_b1*qCos(omega);
        numIm = -a_b1*qSin(omega);
        denRe = 1 + a_a1*qCos(omega);
        denIm = -a_a1*qSin(omega);
    }

    double out = qSqrt((numRe*numRe + numIm*numIm)/(denRe*denRe + denIm*denIm));

    return out;

    /*std::complex<double> z(cos(omega), sin(omega));
    std::complex<double> Hz(0,0);

    Hz = (a0 + a1*pow(z,-1) + a2*pow(z,-2))/(b1*pow(z,-1) + b2*pow(z,-2));

    return Hz;*/
}
