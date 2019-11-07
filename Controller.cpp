#include "Controller.h"

#include <qmath.h>

static int rtaudio_callback(void *output, void *input, unsigned int frames, double streamtime, RtAudioStreamStatus status, void *data)
{
    Q_UNUSED(streamtime)
    Q_UNUSED(status)
    Q_UNUSED(input)

    Controller *controller = (Controller*) data;

    if (controller){
        controller->process((float*)output, frames);
    }

    return 0;
}

Controller::Controller(QObject *parent) :
    QObject(parent),
    _audio(nullptr),
    _signalPlot(nullptr),
    _spectrumPlot(nullptr),
    _bufferSize(512),
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

void Controller::process(float *output, int frames)
{
    float *output0 = output;

    float v;

    for (int i=0; i<frames; i++)
    {
        v = 0;

        if(_synth)
            v += _synth->step();

        *output++ = _spatialSound->process_left(v);
        *output++ = _spatialSound->process_right(v);
    }

    output = output0;

    if (_signalPlot){
        _signalPlot->process(output, frames);
    }

    if (_spectrumPlot)
        _spectrumPlot->process(output, frames);
}

SignalPlot *Controller::signalPlot()
{
    return _signalPlot;
}

void Controller::setSignalPlot(SignalPlot *signalPlot)
{
    _signalPlot = signalPlot;

    emit signalPlotChanged();
}

SpectrumPlot *Controller::spectrumPlot()
{
    return _spectrumPlot;
}

void Controller::setSpectrumPlot(SpectrumPlot *spectrumPlot)
{
    _spectrumPlot = spectrumPlot;

    emit spectrumPlotChanged();
}
