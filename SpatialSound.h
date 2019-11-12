#ifndef SPATIALSOUND_H
#define SPATIALSOUND_H

#include <QObject>
#include <QString>

#include <string>

#include "Sine.h"
#include "Square.h"
#include "WhiteNoise.h"
#include "HeadModel.h"
#include "Lowpass.h"

#include "TransferFunctionPlot.h"

#define DEFAULT_SAMPLE_RATE 44100

#define DEFAULT_MAX_AZIMUTH 90.0
#define DEFAULT_MAX_PHO     200.0
#define DEFAULT_MIN_PHO     1.0


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

    double get_pho(double normalized_pho);
    double get_azimuth(double normalized_azimuth);

    double process_left(double input);
    double process_right(double input);

    TransferFunctionPlot* leftPlot();
    void setLeftPlot(TransferFunctionPlot* leftPlot);
    TransferFunctionPlot* rightPlot();
    void setRightPlot(TransferFunctionPlot* rightPlot);

public slots:
    void reset();
    void setAzimuth(double normalized_azimuth);
    void setAzimuthRunning(bool running);
    void setPho(double normalized_pho);
    void setPhoRunning(bool running);
    QString azimuthLabel(double normalized_azimuth);
    QString phoLabel(double normalized_pho);

signals:
    void runningChanged();
    void leftPlotChanged();
    void rightPlotChanged();

private:
    int _sampleRate;

    bool _running;
    bool _running_pho;
    bool _running_azimuth;

    HeadModel* _left;
    HeadModel* _right;

    TransferFunctionPlot* _leftPlot;
    TransferFunctionPlot* _rightPlot;
};

#endif // SPATIALSOUND_H
