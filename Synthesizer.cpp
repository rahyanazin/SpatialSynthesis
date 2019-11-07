#include "Synthesizer.h"

Synthesizer::Synthesizer(QObject* parent) :
    QObject(parent),    
    _sampleRate(DEFAULT_SAMPLE_RATE),
    _mode(0),
    _running(false)
{
    // Sources
    _sine = new Sine();
    _square = new Square();
    _noise = new WhiteNoise();

    // Filters
    _lowpass = new Lowpass();

    // Sample Rate
    _sine->setSampleRate(_sampleRate);
    _square->setSampleRate(_sampleRate);
    _noise->setSampleRate(_sampleRate);
    _lowpass->setSampleRate(_sampleRate);

    setTone(0.5);
}

void Synthesizer::setSampleRate(int sampleRate)
{
    _sampleRate = sampleRate;
}

int Synthesizer::mode()
{
    return _mode;
}

void Synthesizer::setMode(int mode)
{        
    _mode = mode;
}

bool Synthesizer::running()
{
    return _running;
}

void Synthesizer::setRunning(bool running)
{
    _running = running;
}

double Synthesizer::step()
{
    double v = 0;

    if (_running){
        switch (_mode) {
            case SineWave:
                v = 0.4*_sine->step();
            break;

            case SquareWave:
                v = 0.4*_square->step();
            break;

            case Noise:
                v = _lowpass->process(_noise->step());
            break;
        }
    }

    return v;
}

void Synthesizer::setTone(double tone)
{
    double f = 20.0+21980.0*tone;

    _sine->setFrequency(f);
    _square->setFrequency(f);
    _lowpass->setCutoff(f);
}

void Synthesizer::setResonance(double resonance)
{
    _lowpass->setResonance(resonance);
}
