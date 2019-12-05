#include "Synthesizer.h"

#define MAXTONE 15000.0
#define MINTONE 100.0

Synthesizer::Synthesizer(QObject* parent) :
    QObject(parent),    
    _sampleRate(DEFAULT_SAMPLE_RATE),
    _mode(0)
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

double Synthesizer::step()
{
    double v = 0;

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

    return v;
}

double Synthesizer::getTone(double normalized_tone)
{
    return MINTONE+(MAXTONE-MINTONE)*(std::exp(normalized_tone)-1.0)/((std::exp(1.0)-1.0));
}

QString Synthesizer::toneLabel(double normalized_tone)
{
    return QString::number(getTone(normalized_tone), 'f', 1)+"Hz";
}

void Synthesizer::setTone(double normalized_tone)
{
    double f = getTone(normalized_tone);

    _sine->setFrequency(f);
    _square->setFrequency(f);
    _lowpass->setCutoff(f);
}

void Synthesizer::setResonance(double normalized_resonance)
{
    double r = getResonance(normalized_resonance);

    _lowpass->setResonance(r);
}

QString Synthesizer::resonanceLabel(double normalized_resonance)
{
    return QString::number(getResonance(normalized_resonance), 'f', 1);
}

double Synthesizer::getResonance(double normalized_resonance)
{
    return normalized_resonance*5.0;
}
