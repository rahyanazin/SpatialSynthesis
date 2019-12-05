#ifndef CIPIC_H
#define CIPIC_H

#include <QObject>
#include <QQueue>
#include <QQuickItem>

#include "Filter.h"
#include "CIPIC_Table.h"
#include "string.h"

class CIPIC : public Filter
{
    Q_OBJECT

public:
    using Filter::process;

    enum {Left, Right};

    explicit CIPIC(QObject *parent=nullptr);

    void setSampleRate(int sampleRate);

    void set_hrir_table();
    void set_position(int pos);

    void setAzimuth(double azimuth);
    void setAzimuthRunning(bool running);
    void setPho(double pho);
    void setPhoRunning(bool running);
    void setElevation(double elevation);
    void setElevationRunning(bool running);

    void update();

    //void reset();
    double process(double input);

    void setSubject(int subject);

    double transferFunction(double omega);

    void impression();

private:
    double _sampleRate;
    int _position;

    double _azimuth;
    double _elevation;

    int _azimuth_index;
    int _elevation_index;

    bool _pho_running;
    bool _azimuth_running;
    bool _elevation_running;

    QQueue<double> _last_values;

    double _hrir[200];
    double _hrir_table[46][19][9][200];

    int _subject;

    CIPIC_Table* _tables;

    std::string subject_label[46];
};

#endif // CIPIC_H
