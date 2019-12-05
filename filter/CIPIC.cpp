#include "CIPIC.h"

#include <QObject>

#include <qmath.h>
#include <complex>

#include "npy.hpp"
#include <vector>

#include <CIPIC_Table.h>

#define DEFAULT_SAMPLE_RATE     44100

#define NUMBER_SUBJECTS         45

CIPIC::CIPIC(QObject *parent) :
    Filter(parent),
    _sampleRate(DEFAULT_SAMPLE_RATE),
    _position(-1),
    _azimuth(0),
    _elevation(0),
    _azimuth_running(true),
    _elevation_running(true),
    _subject(0)
{
    for (int i=0; i<200; i++)
        _last_values.append(0.0);

    subject_label[0] = "subject_003";
    subject_label[1] = "subject_008";
    subject_label[2] = "subject_009";
    subject_label[3] = "subject_010";
    subject_label[4] = "subject_011";
    subject_label[5] = "subject_012";
    subject_label[6] = "subject_015";
    subject_label[7] = "subject_017";
    subject_label[8] = "subject_018";
    subject_label[9] = "subject_019";
    subject_label[10] = "subject_020";
    subject_label[11] = "subject_021";
    subject_label[12] = "subject_027";
    subject_label[13] = "subject_028";
    subject_label[14] = "subject_033";
    subject_label[15] = "subject_040";
    subject_label[16] = "subject_044";
    subject_label[17] = "subject_048";
    subject_label[18] = "subject_050";
    subject_label[19] = "subject_051";
    subject_label[20] = "subject_058";
    subject_label[21] = "subject_059";
    subject_label[22] = "subject_060";
    subject_label[23] = "subject_061";
    subject_label[24] = "subject_065";
    subject_label[25] = "subject_119";
    subject_label[26] = "subject_124";
    subject_label[27] = "subject_126";
    subject_label[28] = "subject_127";
    subject_label[29] = "subject_131";
    subject_label[30] = "subject_133";
    subject_label[31] = "subject_134";
    subject_label[32] = "subject_135";
    subject_label[33] = "subject_137";
    subject_label[34] = "subject_147";
    subject_label[35] = "subject_148";
    subject_label[36] = "subject_152";
    subject_label[37] = "subject_153";
    subject_label[38] = "subject_154";
    subject_label[39] = "subject_155";
    subject_label[40] = "subject_156";
    subject_label[41] = "subject_158";
    subject_label[42] = "subject_162";
    subject_label[43] = "subject_163";
    subject_label[44] = "subject_165";
    subject_label[45] = "subject_mean";

    update();
}

void CIPIC::setSampleRate(int sampleRate)
{
    _sampleRate = sampleRate;

    update();
}

void CIPIC::set_hrir_table()
{

    for (int s=0; s<46; s++){
        std::vector<unsigned long> shape;
        std::vector<double> data;

        switch(_position){
            case Left:
                npy::LoadArrayFromNumpy("C:/Users/rahya/OneDrive/Documentos/QtProjects/SpatialSynthesis/filter/CIPIC_Values/"+subject_label[s]+"_l.npy", shape, data);
            break;
            case Right:
                npy::LoadArrayFromNumpy("C:/Users/rahya/OneDrive/Documentos/QtProjects/SpatialSynthesis/filter/CIPIC_Values/"+subject_label[s]+"_r.npy", shape, data);
            break;
        }

//        int az;
//        int elev = -1;
//        int time = -1;
//        for (size_t i = 0; i<data.size(); i++) {
//            az = i%((int)shape[0]);
//            if(az==0)
//                elev++;
//            elev = elev%((int)shape[1]);
//            if(az==0 && elev==0)
//                time++;

//            _hrir_table[s][az][elev][time] = data[i];
//        }

        int az = -1;
        int dt = -1;
        int el = -1;
        for (size_t i = 0; i<data.size(); i++) {
            dt = i%200;
            if (dt == 0)
                el = (el+1)%9;
            if (el == 0 && dt == 0)
                az = (az+1)%19;
            _hrir_table[s][az][el][dt] = data[i];
        }
    }
}

void CIPIC::set_position(int pos)
{
    _position = pos;

    set_hrir_table();

    update();
}

void CIPIC::setAzimuth(double azimuth)
{
    _azimuth = azimuth;

    update();
}

void CIPIC::setAzimuthRunning(bool running)
{
    _azimuth_running = running;

//    reset();
}

void CIPIC::setPho(double pho)
{
    update();
}

void CIPIC::setPhoRunning(bool running)
{
    _pho_running = running;

//    reset();
}

void CIPIC::setElevation(double elevation)
{
    _elevation = elevation;

    update();
}

void CIPIC::setElevationRunning(bool running)
{
    _elevation_running = running;

//    reset();
}

void CIPIC::update()
{
    //update hrir
    double elev_i = _elevation/5.625;
    int elev_i0 = floor(elev_i);
    int elev_i1 = ceil(elev_i);
    if (abs(elev_i-elev_i0)<abs(elev_i-elev_i1))
        _elevation_index = elev_i0;
    else
        _elevation_index = elev_i1;

    double az_i = (_azimuth+45.0)/5;
    int az_i0 = floor(az_i);
    int az_i1 = ceil(az_i);
    int ai = -1;
    if (abs(az_i-az_i0)<abs(az_i-az_i1))
        _azimuth_index = az_i0;
    else
        _azimuth_index = az_i1;

//    for (int t=0; t<200; t++)
//        _hrir[t] = _hrir_table[ai][ei][t];
}

double CIPIC::process(double input)
{
    double y = 0;

    _last_values.append(input);
    _last_values.dequeue();

    for (int n=0; n<200; n++)
        y += _hrir_table[_subject][_azimuth_index][_elevation_index][n]*_last_values.at(199-n);

    if(y > 1.0 || y < -1.0)
        y = 0.0;

    return y;
}

void CIPIC::setSubject(int subject)
{
    _subject = subject;
}

//plot omega in range [0,pi]
double CIPIC::transferFunction(double omega)
{
    double numRe = 0;
    double numIm = 0;
    for (int n=0; n<200; n++){
        numRe += _hrir_table[_subject][_azimuth_index][_elevation_index][n]*qCos(-n*omega);
        numIm += _hrir_table[_subject][_azimuth_index][_elevation_index][n]*qSin(-n*omega);
    }

    double out = qSqrt((numRe*numRe + numIm*numIm));

    return out;

    //    return 1;
}

void CIPIC::impression()
{
//    qDebug() << _azimuth_index << _elevation_index;
//    qDebug() << _azimuth_index << _elevation_index;
//    qDebug() << "______________";
//    for (int n=0; n<200; n++){
//        qDebug()<< n << ": " << _hrir_table[_subject][_azimuth_index][_elevation_index][n];
//    }

//    for (int az = 0; az < 19; ++az) {
//        QDebug deb = qDebug();
//        for (int el = 0; el < 9; ++el)
//            deb << _hrir_table[_subject][az][el][20];
//    }

    std::vector<unsigned long> shape;
    std::vector<double> data;

    npy::LoadArrayFromNumpy("C:/Users/rahya/OneDrive/Documentos/QtProjects/SpatialSynthesis/filter/CIPIC_Values/subject_003_l.npy", shape, data);

    int az = -1;
    int dt = -1;
    int el = -1;
    for (size_t i = 0; i<data.size(); i++) {
        dt = i%200;
        if (dt == 0)
            el = (el+1)%9;
        if (el == 0 && dt == 0)
            az = (az+1)%19;
        qDebug() << az << el << dt << data[i];
    }
}
