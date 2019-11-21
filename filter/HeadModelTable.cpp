#include "HeadModelTable.h"
#include "math.h"
#include "QDebug"

HeadModelTable::HeadModelTable()
{
    high_frequency_gain(1.0, 40.0);
}

double HeadModelTable::dc_gain(double pho, double theta_inc)
{
    double gain_dc = 0.0;
//    qDebug() << "ThInc: " << theta_inc;
//    qDebug() << "Floor: " << floor(theta_inc);
//    qDebug() << "Ceil : " << ceil(theta_inc);

    int i0 = static_cast <int> (floor(theta_inc/10.0));
    int i1 = static_cast <int> (ceil(theta_inc/10.0));
    double i = theta_inc/10.0;

//    qDebug() << "i_0  : " << i0;
//    qDebug() << "i_Inc: " << i;
//    qDebug() << "i_1  : " << i1;

    if (i0 == i1){
//        qDebug("Integer Theta_Inc");

        int aux_i = static_cast <int> (i);

        double p11 = dc_gain_table[aux_i][1];
        double p21 = dc_gain_table[aux_i][2];
        double q11 = dc_gain_table[aux_i][3];
        double q21 = dc_gain_table[aux_i][4];

        gain_dc = (p11*pho+p21)/(pho*pho+q11*pho+q21);
//        qDebug() << "G: " << gain_dc;
    }

    else{
        double theta_inc_0 = dc_gain_table[i0][0];
        double p11_0 = dc_gain_table[i0][1];
        double p21_0 = dc_gain_table[i0][2];
        double q11_0 = dc_gain_table[i0][3];
        double q21_0 = dc_gain_table[i0][4];

//        qDebug() << "Th_0 : " << theta_inc_0;
//        qDebug() << "p11_0: " << p11_0;
//        qDebug() << "p21_0: " << p21_0;
//        qDebug() << "q11_0: " << q11_0;
//        qDebug() << "q21_0: " << q21_0;

        double theta_inc_1 = dc_gain_table[i1][0];
        double p11_1 = dc_gain_table[i1][1];
        double p21_1 = dc_gain_table[i1][2];
        double q11_1 = dc_gain_table[i1][3];
        double q21_1 = dc_gain_table[i1][4];

//        qDebug() << "Th_1 : " << theta_inc_1;
//        qDebug() << "p11_1: " << p11_1;
//        qDebug() << "p21_1: " << p21_1;
//        qDebug() << "q11_1: " << q11_1;
//        qDebug() << "q21_1: " << q21_1;

        double gain_dc_0 = (p11_0*pho+p21_0)/(pho*pho+q11_0*pho+q21_0);
        double gain_dc_1 = (p11_1*pho+p21_1)/(pho*pho+q11_1*pho+q21_1);

//        qDebug() << "G0: " << gain_dc_0;
//        qDebug() << "G1: " << gain_dc_1;

        gain_dc = (gain_dc_1-gain_dc_0)*(theta_inc-theta_inc_0)/(theta_inc_1-theta_inc_0)+gain_dc_0;
//        qDebug() << "G: " << gain_dc;
    }

    return gain_dc;
}

double HeadModelTable::high_frequency_gain(double pho, double theta_inc)
{
    double gain_high_frequency = 0.0;

    int i0 = static_cast <int> (floor(theta_inc/10.0));
    int i1 = static_cast <int> (ceil(theta_inc/10.0));
    double i = theta_inc/10.0;

    if (i0 == i1){
        int aux_i = static_cast <int> (i);

        double p12 = high_frequency_gain_table[aux_i][1];
        double p22 = high_frequency_gain_table[aux_i][2];
        double q12 = high_frequency_gain_table[aux_i][3];
        double q22 = high_frequency_gain_table[aux_i][4];

        gain_high_frequency = (p12*pho+p22)/(pho*pho+q12*pho+q22);
    }

    else{
        double theta_inc_0 = high_frequency_gain_table[i0][0];
        double p12_0 = high_frequency_gain_table[i0][1];
        double p22_0 = high_frequency_gain_table[i0][2];
        double q12_0 = high_frequency_gain_table[i0][3];
        double q22_0 = high_frequency_gain_table[i0][4];

        double theta_inc_1 = high_frequency_gain_table[i1][0];
        double p12_1 = high_frequency_gain_table[i1][1];
        double p22_1 = high_frequency_gain_table[i1][2];
        double q12_1 = high_frequency_gain_table[i1][3];
        double q22_1 = high_frequency_gain_table[i1][4];

        double gain_high_frequency_0 = (p12_0*pho+p22_0)/(pho*pho+q12_0*pho+q22_0);
        double gain_high_frequency_1 = (p12_1*pho+p22_1)/(pho*pho+q12_1*pho+q22_1);

        gain_high_frequency = (gain_high_frequency_1-gain_high_frequency_0)*(theta_inc-theta_inc_0)/(theta_inc_1-theta_inc_0)+gain_high_frequency_0;
    }

    return gain_high_frequency;
}

double HeadModelTable::shelving_filter_cutoff(double pho, double theta_inc)
{
    double cutoff_high_frequency = 0.0;

    int i0 = static_cast <int> (floor(theta_inc/10.0));
    int i1 = static_cast <int> (ceil(theta_inc/10.0));
    double i = theta_inc/10.0;

    if (i0 == i1){
        int aux_i = static_cast <int> (i);

        double p13 = shelving_filter_cutoff_table[aux_i][1];
        double p23 = shelving_filter_cutoff_table[aux_i][2];
        double p33 = shelving_filter_cutoff_table[aux_i][3];
        double q13 = shelving_filter_cutoff_table[aux_i][4];
        double q23 = shelving_filter_cutoff_table[aux_i][5];

        cutoff_high_frequency = (p13*pho*pho + p23*pho + p33)/(pho*pho +q13*pho + q23);
    }

    else{
        double theta_inc_0 = shelving_filter_cutoff_table[i0][0];
        double p13_0 = shelving_filter_cutoff_table[i0][1];
        double p23_0 = shelving_filter_cutoff_table[i0][2];
        double p33_0 = shelving_filter_cutoff_table[i0][3];
        double q13_0 = shelving_filter_cutoff_table[i0][4];
        double q23_0 = shelving_filter_cutoff_table[i0][5];

        double theta_inc_1 = shelving_filter_cutoff_table[i1][0];
        double p13_1 = shelving_filter_cutoff_table[i1][1];
        double p23_1 = shelving_filter_cutoff_table[i1][2];
        double p33_1 = shelving_filter_cutoff_table[i1][3];
        double q13_1 = shelving_filter_cutoff_table[i1][4];
        double q23_1 = shelving_filter_cutoff_table[i1][5];

        double cutoff_high_frequency_0 = (p13_0*pho*pho + p23_0*pho + p33_0)/(pho*pho +q13_0*pho + q23_0);
        double cutoff_high_frequency_1 = (p13_1*pho*pho + p23_1*pho + p33_1)/(pho*pho +q13_1*pho + q23_1);

        cutoff_high_frequency = (cutoff_high_frequency_1-cutoff_high_frequency_0)*(theta_inc-theta_inc_0)/(theta_inc_1-theta_inc_0)+cutoff_high_frequency_0;
    }

    return cutoff_high_frequency;
}
