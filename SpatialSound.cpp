#include "SpatialSound.h"

SpatialSound::SpatialSound(QObject* parent) :
    QObject(parent),
    _sampleRate(DEFAULT_SAMPLE_RATE),
    _running(true),
    _leftPlot(nullptr)
{
    _left = new HeadModel();
    _left->set_position(HeadModel::Left);
    _right = new HeadModel();
    _right->set_position(HeadModel::Right);

    setSampleRate(DEFAULT_SAMPLE_RATE);
    setAzimuth(0.75);
}

void SpatialSound::setSampleRate(int sampleRate)
{
    _sampleRate = sampleRate;
    _left->setSampleRate(_sampleRate);
    _right->setSampleRate(_sampleRate);

}

bool SpatialSound::running()
{
    return _running;
}

void SpatialSound::setRunning(bool running)
{
    _running = running;
}

double SpatialSound::process_left(double input)
{
    if (_running)
        return _left->process(input);
    else
        return input;
}

double SpatialSound::process_right(double input)
{
    if (_running)
        return _right->process(input);
    else
        return input;
}

void SpatialSound::setAzimuth(double normalized_azimuth)
{
    double azimuth = 90.0*(2.0*normalized_azimuth-1.0);

    _left->setAzimuth(azimuth);
    _right->setAzimuth(azimuth);

    if (_leftPlot)
        _leftPlot->update();

    if (_rightPlot)
        _rightPlot->update();
}

TransferFunctionPlot* SpatialSound::leftPlot()
{
    return _leftPlot;
}

void SpatialSound::setLeftPlot(TransferFunctionPlot *leftPlot)
{
    _leftPlot = leftPlot;

    _leftPlot->setFilter(_left);
    _leftPlot->setColor(TransferFunctionPlot::blue);

    emit leftPlotChanged();
}

TransferFunctionPlot* SpatialSound::rightPlot()
{
    return _rightPlot;
}

void SpatialSound::setRightPlot(TransferFunctionPlot *rightPlot)
{
    _rightPlot = rightPlot;

    _rightPlot->setFilter(_right);
    _rightPlot->setColor(TransferFunctionPlot::yellow);

    emit rightPlotChanged();
}
