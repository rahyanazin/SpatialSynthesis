#include "CIPIC_Table.h"

#include "npy.hpp"
#include <vector>

CIPIC_Table::CIPIC_Table()
{
    std::vector<unsigned long> shape_hrir_l_003;
    std::vector<double> data_hrir_l_003;

    npy::LoadArrayFromNumpy("C:/Users/rahya/OneDrive/Documentos/QtProjects/SpatialSynthesis/filter/CIPIC_Values/subject_003_l.npy", shape_hrir_l_003, data_hrir_l_003);

    int az;
    int elev = -1;
    int time = -1;
    for (size_t i = 0; i<data_hrir_l_003.size(); i++) {
        az = i%25;
        if(az==0)
            elev++;
        elev = elev%50;
        if(az==0 && elev==0)
            time++;
//        qDebug() << az << ", " << elev << ", " << time;
        hrir_l_003[az][elev][time] = data_hrir_l_003[i];
    }

    std::vector<unsigned long> shape_hrir_r_003;
    std::vector<double> data_hrir_r_003;

    npy::LoadArrayFromNumpy("C:/Users/rahya/OneDrive/Documentos/QtProjects/SpatialSynthesis/filter/CIPIC_Values/subject_003_r.npy", shape_hrir_r_003, data_hrir_r_003);

    az = 0;
    elev = -1;
    time = -1;
    for (size_t i = 0; i<data_hrir_r_003.size(); i++) {
        az = i%25;
        if(az==0)
            elev++;
        elev = elev%50;
        if(az==0 && elev==0)
            time++;
//        qDebug() << az << ", " << elev << ", " << time;
        hrir_r_003[az][elev][time] = data_hrir_r_003[i];
    }
}
