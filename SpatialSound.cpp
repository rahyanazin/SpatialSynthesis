#include "SpatialSound.h"

SpatialSound::SpatialSound(QObject* parent) :
    QObject(parent),
    _sampleRate(DEFAULT_SAMPLE_RATE),
    _running(true),
    _running_pho(true),
    _running_azimuth(true),
    _leftPlot(nullptr)
{
    _left = new HeadModel();
    _left->set_position(HeadModel::Left);
    _right = new HeadModel();
    _right->set_position(HeadModel::Right);

    setSampleRate(DEFAULT_SAMPLE_RATE);
    setAzimuth(0.5);
    setPho(0.5);
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

double SpatialSound::get_pho(double normalized_pho)
{
    return DEFAULT_MIN_PHO+(DEFAULT_MAX_PHO-DEFAULT_MIN_PHO)*normalized_pho;
}

double SpatialSound::get_azimuth(double normalized_azimuth)
{
    return DEFAULT_MAX_AZIMUTH*(2.0*normalized_azimuth-1.0);
}

double SpatialSound::process_left(double input)
{
    if (_running) {
        return _left->process(input);
    }
    else {
        return input;
    }
}

double SpatialSound::process_right(double input)
{
    if (_running) {
        return _right->process(input);
    }
    else {
        return input;
    }
}

void SpatialSound::setAzimuth(double normalized_azimuth)
{
    double azimuth = get_azimuth(normalized_azimuth);

    _left->setAzimuth(azimuth);
    _right->setAzimuth(azimuth);

    if (_leftPlot)
        _leftPlot->update();

    if (_rightPlot)
        _rightPlot->update();
}

void SpatialSound::setAzimuthRunning(bool running)
{
    _running_azimuth = running;

    _left->setAzimuthRunning(_running_azimuth);
    _right->setAzimuthRunning(_running_azimuth);

    if (_leftPlot)
        _leftPlot->update();

    if (_rightPlot)
        _rightPlot->update();

    if (_running_azimuth)
        qDebug() << "azimuth on!";
    else
        qDebug() << "azimuth off!";
}

void SpatialSound::setPho(double normalized_pho)
{
    double pho = get_pho(normalized_pho);

    _left->setPho(pho);
    _right->setPho(pho);

    if (_leftPlot)
        _leftPlot->update();

    if (_rightPlot)
        _rightPlot->update();
}

void SpatialSound::setPhoRunning(bool running)
{
    _running_pho = running;

    _left->setPhoRunning(_running_pho);
    _right->setPhoRunning(_running_pho);

    if (_leftPlot)
        _leftPlot->update();

    if (_rightPlot)
        _rightPlot->update();

    if (_running_pho)
        qDebug() << "pho on!";
    else
        qDebug() << "pho off!";
}

QString SpatialSound::azimuthLabel(double normalized_azimuth)
{
    return QString::number(get_azimuth(normalized_azimuth), 'f', 1)+"º";
}

QString SpatialSound::phoLabel(double normalized_pho)
{
    return QString::number(get_pho(normalized_pho), 'f', 1);
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

void SpatialSound::reset()
{
    _left->reset();
    _right->reset();
}
