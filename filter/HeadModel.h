#ifndef HEADMODEL_H
#define HEADMODEL_H

#include <QObject>
#include <QQueue>
#include <QQuickItem>

#include "Filter.h"
#include "HeadModelTable.h"

class HeadModel : public Filter
{
    Q_OBJECT

public:
    using Filter::process;

    enum {Left, Right};

    explicit HeadModel(QObject *parent=nullptr);

    void setSampleRate(int sampleRate);

    void set_position(int pos);

    void setAzimuth(double azimuth);
    void setPho(double pho);
    void setElevation(double pho);

    void update();

    void reset();
    double process(double input);

    double transferFunction(double omega);

private:
    double _sampleRate;
    int _position;

    //Long Distance Head Filter Param
    double a_a1;
    double a_b0;
    double a_b1;
    double alpha;
    double betha;

    //Long Distance Head Filters' Variables
    double alpha_min;
    double theta_min;

    //Shelving Filter
    double p_a1;
    double p_b0;
    double p_b1;
    double m;
    double n;
    double V0;
    double ac;
    double pho;
    double fc;
    double gain_high;
    double gain_dc;

    //Filters' Commom Variables
    double _azimuth;
    double _headRadius;
    //double _radius;
    double _pho;
    double theta_inc;
    double fs;
    double c;
    //double a;

    //Filter's Param
    double _lastX1;
    double _lastX2;
    double _lastY1;
    double _lastY2;
    double b0;
    double b1;
    double b2;
    double a1;
    double a2;

    HeadModelTable* _tables;
};

#endif // HEADMODEL_H
