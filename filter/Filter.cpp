#include "Filter.h"

Filter::Filter(QObject *parent) :
    QObject(parent)
{

}

void Filter::process(QVector<double> *input, QVector<double> *output)
{
    (void) input;
    (void) output;

    return;
}

double Filter::transferFunction(double omega)
{
    (void) omega;

    return 1.0;
}
