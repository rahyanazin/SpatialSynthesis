#ifndef SPATIALSOUND_H
#define SPATIALSOUND_H

#include <QObject>
#include <QString>

#include <string>

#include "Sine.h"
#include "Square.h"
#include "WhiteNoise.h"
#include "Lowpass.h"

#include "HeadModel.h"
#include "CIPIC.h"

#include "TransferFunctionPlot.h"

#define DEFAULT_SAMPLE_RATE 44100

#define DEFAULT_MAX_AZIMUTH     45.0
#define DEFAULT_MIN_AZIMUTH     -45.0
#define DEFAULT_MAX_PHO         200.0
#define DEFAULT_MIN_PHO         1.0
#define DEFAULT_MAX_ELEVATION   45.0
#define DEFAULT_MIN_ELEVATION   0.0

class SpatialSound : public QObject
{
    enum{
        SineWave=0,
        SquareWave=1,
        Noise=2
    };

    enum{
        HeadModelMode=0,
        CIPICMode=1
    };

public:

    Q_OBJECT
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    Q_PROPERTY(bool transferFunction READ transferFunction WRITE setTransferFunction NOTIFY transferFunctionChanged)
    Q_PROPERTY(int subject READ subject WRITE setSubject NOTIFY subjectChanged)
    Q_PROPERTY(int mode READ mode WRITE setMode NOTIFY modeChanged)
    Q_PROPERTY(TransferFunctionPlot* leftPlot READ leftPlot WRITE setLeftPlot NOTIFY leftPlotChanged)
    Q_PROPERTY(TransferFunctionPlot* rightPlot READ rightPlot WRITE setRightPlot NOTIFY rightPlotChanged)

public:

    explicit SpatialSound(QObject* parent=nullptr);

    void setSampleRate(int sampleRate);

    bool running();
    void setRunning(bool running);
    bool transferFunction();
    void setTransferFunction(bool transferFunction);
    int mode();
    void setMode(int mode);
    int subject();
    void setSubject(int subject);

    double get_pho(double normalized_pho);
    double get_azimuth(double normalized_azimuth);
    double get_elevation(double normalized_azimuth);

    double process_left(double input);
    double process_right(double input);

    TransferFunctionPlot* leftPlot();
    void setLeftPlot(TransferFunctionPlot* leftPlot);
    TransferFunctionPlot* rightPlot();
    void setRightPlot(TransferFunctionPlot* rightPlot);

public slots:
    void reset();
    void setAzimuth(double normalized_azimuth);
    void setPho(double normalized_pho);
    void setElevation(double normalized_pho);
    QString azimuthLabel(double normalized_azimuth);
    QString phoLabel(double normalized_pho);
    QString elevationLabel(double elevation_pho);

signals:
    void runningChanged();
    void transferFunctionChanged();
    void modeChanged();
    void subjectChanged();
    void leftPlotChanged();
    void rightPlotChanged();

private:
    int _sampleRate;

    bool _running;
    bool _transferFunction;
    int _mode;
    int _subject;

    HeadModel* _left_Head;
    HeadModel* _right_Head;

    CIPIC* _left_CIPIC;
    CIPIC* _right_CIPIC;


    TransferFunctionPlot* _leftPlot;
    TransferFunctionPlot* _rightPlot;
};

#endif // SPATIALSOUND_H
