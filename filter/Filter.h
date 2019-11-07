#ifndef FILTER_H
#define FILTER_H

#include <QObject>
#include <QVector>

#include <complex>

class Filter : public QObject
{
    Q_OBJECT
public:
    explicit Filter(QObject* parent=nullptr);

    virtual void process(QVector<double> *input, QVector<double> *output);

    virtual double transferFunction(double omega);
};

#endif // FILTER_H
