#ifndef SEQUENCERSTEP_H
#define SEQUENCERSTEP_H

#include <QObject>

class SequencerStep : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool active READ active WRITE setActive NOTIFY activeChanged)

public:
    explicit SequencerStep(QObject* parent=nullptr);

    bool active();
    void setActive(bool active);

signals:
    void activeChanged(bool isActive);

private:
    bool _active;
};

#endif // SEQUENCERSTEP_H
