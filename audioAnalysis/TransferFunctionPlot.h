#ifndef TRANSFERFUNCTIONPLOT_H
#define TRANSFERFUNCTIONPLOT_H

#include <QQuickItem>
#include <QQuickPaintedItem>

#include "Filter.h"

class TransferFunctionPlot : public QQuickItem
{
    Q_OBJECT

public:
    enum{red,blue,yellow};
    TransferFunctionPlot(QQuickItem *parent=nullptr);
    ~TransferFunctionPlot();

    void setFilter(Filter* filter);
    void setColor(int color);

public slots:
    QSGNode* updatePaintNode(QSGNode *, UpdatePaintNodeData *);

private:
    Filter* _filter;
    Qt::GlobalColor _color;
};

#endif // TRANSFERFUNCTIONPLOT_H
