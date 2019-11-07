#ifndef SPATIALSOUND_H
#define SPATIALSOUND_H

#include <QObject>

#include "Sine.h"
#include "Square.h"
#include "WhiteNoise.h"
#include "HeadModel.h"
#include "Lowpass.h"

#include "TransferFunctionPlot.h"


#define DEFAULT_SAMPLE_RATE 44100


class SpatialSound : public QObject
{
    enum{
        SineWave=0,
        SquareWave=1,
        Noise=2
    };

public:

    Q_OBJECT
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    Q_PROPERTY(TransferFunctionPlot* leftPlot READ leftPlot WRITE setLeftPlot NOTIFY leftPlotChanged)
    Q_PROPERTY(TransferFunctionPlot* rightPlot READ rightPlot WRITE setRightPlot NOTIFY rightPlotChanged)

public:

    explicit SpatialSound(QObject* parent=nullptr);

    void setSampleRate(int sampleRate);

    bool running();
    void setRunning(bool running);

    double process_left(double input);
    double process_right(double input);

    TransferFunctionPlot* leftPlot();
    void setLeftPlot(TransferFunctionPlot* leftPlot);
    TransferFunctionPlot* rightPlot();
    void setRightPlot(TransferFunctionPlot* rightPlot);

public slots:
    void setAzimuth(double normalized_azimuth);

signals:
    void runningChanged();
    void leftPlotChanged();
    void rightPlotChanged();

private:
    int _sampleRate;

    bool _running;

    HeadModel* _left;
    HeadModel* _right;

    TransferFunctionPlot* _leftPlot;
    TransferFunctionPlot* _rightPlot;
};

#endif // SPATIALSOUND_H
