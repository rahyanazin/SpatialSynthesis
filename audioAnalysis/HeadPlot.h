#ifndef HEADPLOT_H
#define HEADPLOT_H

#include <QQuickItem>
#include <QQuickPaintedItem>

#include "Head.h"

class HeadPlot : public QQuickItem
{
    Q_OBJECT

public:
    HeadPlot (QQuickItem *parent=nullptr);
    ~HeadPlot ();

    void setFilter(Head* head);

public slots:
    QSGNode* updatePaintNode(QSGNode *, UpdatePaintNodeData *);

private:
    Head* _head;
};

#endif // HEADPLOT_H
