#ifndef HEAD_H
#define HEAD_H

#include <QObject>
#include <QQueue>
#include <QQuickItem>

#include "Filter.h"

class Head : public Filter
{
    Q_OBJECT

public:
    using Filter::process;

    enum {Left, Right};

    explicit Head(QObject *parent=nullptr);

    void setSampleRate(int sampleRate);

    void set_position(int pos);

    void setAzimuth(double azimuth);

    void update();

    double process(double input);

    double transferFunction(double omega);

private:
    double _sampleRate;
    int _position;

    double a1;
    double b0;
    double b1;
    double _lastX1;
    double _lastY1;
    double alpha;
    double betha;
    double theta_inc;

    //Filters' Common Variables
    double _azimuth;
    double fs;
    double c;
    double a;
    double alpha_min;
    double theta_min;
};

#endif // HEAD_H
