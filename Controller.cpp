#include "Controller.h"

#include <qmath.h>

#include <HeadModelTable.h>

static int rtaudio_callback(void *output, void *input, unsigned int frames, double streamtime, RtAudioStreamStatus status, void *data)
{
    Q_UNUSED(streamtime)
    Q_UNUSED(status)
    Q_UNUSED(input)

    Controller *controller = (Controller*) data;

    if (controller){
        //qDebug() << frames;
        controller->process((float*)output, frames);
    }

    return 0;
}

Controller::Controller(QObject *parent) :
    QObject(parent),
    _audio(nullptr),
    _running(false),
    _signalLeft(nullptr),
    _signalRight(nullptr),
    _spectrumLeft(nullptr),
    _spectrumRight(nullptr),
    _bufferSize(1024),
    _channels(2),
    _sampleRate(44100)
{
    _synth = new Synthesizer();
    _spatialSound = new SpatialSound();

    start();
}

Controller::~Controller()
{
    stop();

    if (_audio)
        delete _audio;
}

void Controller::start()
{

//    if(_running)
//        return;

    if(!_audio)
    {
        try
        {
            _audio = new RtAudio();
        }
        catch (RtAudioError e)
        {
            qDebug() << "Fail to create RtAudio" << e.what();
        }

        _streamOutput.deviceId = _audio->getDefaultOutputDevice();
        _streamOutput.nChannels = _channels;
    }


    if (_audio)
    {
        _audio->openStream(&_streamOutput, NULL, RTAUDIO_FLOAT32, _sampleRate, &_bufferSize, rtaudio_callback, this);
        _audio->startStream();

//        _running = true;

        runningChanged();
    }
}

void Controller::stop()
{
//    if (_audio)
//        _audio->abortStream();

//    if (!_running)
//        return;

//    _running = false;

    if (_audio && _audio->isStreamOpen())
        _audio->closeStream();

    emit runningChanged();
}

Synthesizer *Controller::synth()
{
    return _synth;
}

SpatialSound *Controller::spatialSound()
{
    return _spatialSound;
}

void Controller::signalProcess(float *output, float *output_left, float*output_right, int frames)
{
    double v_left = 0.0;
    double v_right = 0.0;

    for (int i=0; i<frames; i++)
    {
        if(_running)
            if(_synth) {
                double v = _synth->step();
                v_left = _spatialSound->process_left(v);
                v_right = _spatialSound->process_right(v);
            }

        *output_left++ = static_cast <float> (v_left);
        *output_right++ = static_cast <float> (v_right);

        *output++ = static_cast <float> (v_left);
        *output++ = static_cast <float> (v_right);
    }
}

void Controller::process(float *output, int frames)
{
    float output_left[frames];
    float output_right[frames];

    signalProcess(output, output_left, output_right, frames);

    if (_signalLeft)
        _signalLeft->process(output_left, frames);

    if (_signalRight)
        _signalRight->process(output_right, frames);

    if (_spectrumLeft)
        _spectrumLeft->process(output_left, frames);

    if (_spectrumRight)
        _spectrumRight->process(output_right, frames);
}

bool Controller::running()
{
    return _running;
}

void Controller::setRunning(bool running)
{
    _running = running;

    emit runningChanged();
}

SignalPlot *Controller::signalLeft()
{
    return _signalLeft;
}

void Controller::setSignalLeft(SignalPlot *signalLeft)
{
    _signalLeft = signalLeft;
    _signalLeft->setColor(SignalPlot::blue);

    emit signalLeftChanged();
}
SignalPlot *Controller::signalRight()
{
    return _signalRight;
}

void Controller::setSignalRight(SignalPlot *signalPlot)
{
    _signalRight = signalPlot;
    _signalRight->setColor(SignalPlot::yellow);

    emit signalRightChanged();
}

SpectrumPlot *Controller::spectrumLeft()
{
    return _spectrumLeft;
}

void Controller::setSpectrumLeft(SpectrumPlot *spectrumLeft)
{
    _spectrumLeft = spectrumLeft;
    _spectrumLeft->setColor(SignalPlot::blue);

    emit spectrumLeftChanged();
}

SpectrumPlot *Controller::spectrumRight()
{
    return _spectrumRight;
}

void Controller::setSpectrumRight(SpectrumPlot *spectrumRight)
{
    _spectrumRight = spectrumRight;
    _spectrumRight->setColor(SignalPlot::yellow);

    emit spectrumRightChanged();
}
