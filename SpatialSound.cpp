#include "SpatialSound.h"

SpatialSound::SpatialSound(QObject* parent) :
    QObject(parent),
    _sampleRate(DEFAULT_SAMPLE_RATE),
    _running(true),
    _transferFunction(true),
    _mode(HeadModelMode),
    _subject(0),
    _leftPlot(nullptr),
    _rightPlot(nullptr)

{
    _left_CIPIC = new CIPIC();
    _left_CIPIC->set_position(CIPIC::Left);
    _right_CIPIC = new CIPIC();
    _right_CIPIC->set_position(CIPIC::Right);

    _left_Head = new HeadModel();
    _left_Head->set_position(HeadModel::Left);
    _right_Head = new HeadModel();
    _right_Head->set_position(HeadModel::Right);

    setSampleRate(DEFAULT_SAMPLE_RATE);
    setAzimuth(0.5);
    setElevation(0.0);
    setPho(0.5);
}

void SpatialSound::setSampleRate(int sampleRate)
{
    _sampleRate = sampleRate;
    _left_CIPIC->setSampleRate(_sampleRate);
    _right_CIPIC->setSampleRate(_sampleRate);
    _left_Head->setSampleRate(_sampleRate);
    _right_Head->setSampleRate(_sampleRate);

}

bool SpatialSound::running()
{
    return _running;
}

void SpatialSound::setRunning(bool running)
{
    _running = running;
}

bool SpatialSound::transferFunction()
{
    return _transferFunction;
}

void SpatialSound::setTransferFunction(bool transferFunction)
{
    _transferFunction = transferFunction;

    if(_transferFunction){
        leftPlot()->update();
        rightPlot()->update();
    }

}


int SpatialSound::mode()
{
    return _mode;
}

void SpatialSound::setMode(int mode)
{
    _mode = mode;

    switch (_mode) {
        case HeadModelMode:
            leftPlot()->setFilter(_left_Head);
            rightPlot()->setFilter(_right_Head);
        break;
        case CIPICMode:
            leftPlot()->setFilter(_left_CIPIC);
            rightPlot()->setFilter(_right_CIPIC);
        break;
    }
    leftPlot()->update();
    rightPlot()->update();

}

int SpatialSound::subject()
{
    return _subject;
}

void SpatialSound::setSubject(int subject)
{
    _subject = subject;

    _left_CIPIC->setSubject(_subject);
    _right_CIPIC->setSubject(_subject);

    leftPlot()->update();
    rightPlot()->update();

    emit subjectChanged();
}

double SpatialSound::get_pho(double normalized_pho)
{
    return DEFAULT_MIN_PHO+(DEFAULT_MAX_PHO-DEFAULT_MIN_PHO)*normalized_pho;
}

double SpatialSound::get_azimuth(double normalized_azimuth)
{
    return DEFAULT_MIN_AZIMUTH+(DEFAULT_MAX_AZIMUTH-DEFAULT_MIN_AZIMUTH)*normalized_azimuth;
}

double SpatialSound::get_elevation(double normalized_elevation)
{
    return DEFAULT_MIN_ELEVATION+(DEFAULT_MAX_ELEVATION-DEFAULT_MIN_ELEVATION)*normalized_elevation;
}

double SpatialSound::process_left(double input)
{
    if (_running) {
        switch (_mode) {
            case CIPICMode:
                return _left_CIPIC->process(input);
            break;
            case HeadModelMode:
                return _left_Head->process(input);
            break;
        }
    }
    else {
        return input;
    }
}

double SpatialSound::process_right(double input)
{
    if (_running) {
        switch (_mode) {
            case CIPICMode:
                return _right_CIPIC->process(input);
            break;
            case HeadModelMode:
                return _right_Head->process(input);
            break;
        }
    }
    else {
        return input;
    }
}

void SpatialSound::setAzimuth(double normalized_azimuth)
{
    double azimuth = get_azimuth(normalized_azimuth);

    _left_CIPIC->setAzimuth(azimuth);
    _right_CIPIC->setAzimuth(azimuth);
    _left_Head->setAzimuth(azimuth);
    _right_Head->setAzimuth(azimuth);

    if(_transferFunction) {
        if (_leftPlot != nullptr)
            _leftPlot->update();

        if (_rightPlot != nullptr)
            _rightPlot->update();
    }
}

void SpatialSound::setPho(double normalized_pho)
{
    double pho = get_pho(normalized_pho);

    _left_CIPIC->setPho(pho);
    _right_CIPIC->setPho(pho);
    _left_Head->setPho(pho);
    _right_Head->setPho(pho);

    if(_transferFunction){
        if (_leftPlot != nullptr)
            _leftPlot->update();

        if (_rightPlot != nullptr)
            _rightPlot->update();
    }
}


void SpatialSound::setElevation(double normalized_elevation)
{
    double elevation = get_elevation(normalized_elevation);

    _left_CIPIC->setElevation(elevation);
    _right_CIPIC->setElevation(elevation);
    _left_Head->setElevation(elevation);
    _right_Head->setElevation(elevation);

    if(_transferFunction){
        if (_leftPlot != nullptr)
            _leftPlot->update();

        if (_rightPlot != nullptr)
            _rightPlot->update();
    }
}

QString SpatialSound::azimuthLabel(double normalized_azimuth)
{
    return QString::number(get_azimuth(normalized_azimuth), 'f', 1)+"º";
}

QString SpatialSound::phoLabel(double normalized_pho)
{
    return QString::number(get_pho(normalized_pho), 'f', 1);
}

QString SpatialSound::elevationLabel(double normalized_elevation)
{
    return QString::number(get_elevation(normalized_elevation), 'f', 1)+"º";
}

void SpatialSound::impression()
{
    _left_CIPIC->impression();
}

TransferFunctionPlot* SpatialSound::leftPlot()
{
    return _leftPlot;
}

void SpatialSound::setLeftPlot(TransferFunctionPlot *leftPlot)
{
    _leftPlot = leftPlot;

    _leftPlot->setFilter(_left_Head);
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

    _rightPlot->setFilter(_right_Head);
    _rightPlot->setColor(TransferFunctionPlot::yellow);

    emit rightPlotChanged();
}

void SpatialSound::reset()
{
    _left_Head->reset();
    _right_Head->reset();
}
