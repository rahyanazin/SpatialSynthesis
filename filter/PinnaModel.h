#ifndef PINNAMODEL_H
#define PINNAMODEL_H

#include <QObject>
#include <QQueue>
#include <QQuickItem>

#include "Filter.h"
#include "PinnaModelTable.h"

class PinnaModel : public Filter
{
    Q_OBJECT

public:
    using Filter::process;

    explicit PinnaModel(QObject *parent=nullptr);

    void setSampleRate(int sampleRate);

    void setElevation(double elevation);
    void setElevationRunning(bool running);

    void update();

    void reset();
    double process(double input);

    double transferFunction(double omega);

private:
    double _sampleRate;
    int _position;

    double _elevation;
    bool _elevation_running;

    PinnaModelTable* _tables;

    double res1_b0;
    double res1_b1;
    double res1_b2;
    double res1_a0;
    double res1_a1;
    double res1_a2;

    double res2_b0;
    double res2_b1;
    double res2_b2;
    double res2_a0;
    double res2_a1;
    double res2_a2;

    double refl1_b0;
    double refl1_b1;
    double refl1_b2;
    double refl1_a0;
    double refl1_a1;
    double refl1_a2;

    double refl2_b0;
    double refl2_b1;
    double refl2_b2;
    double refl2_a0;
    double refl2_a1;
    double refl2_a2;

    double refl3_b0;
    double refl3_b1;
    double refl3_b2;
    double refl3_a0;
    double refl3_a1;
    double refl3_a2;
};

#endif // PINNAMODEL_H
