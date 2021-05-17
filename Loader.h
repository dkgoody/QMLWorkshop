#ifndef LOADER_H
#define LOADER_H
#include <QObject>
#include <QThread>
#include "Data.h"

class Worker : public QObject
{
    Q_OBJECT

public slots:
    void doWork(Data& data);

signals:
    void resultReady(bool result);
};


class Loader : public QObject
{
    Q_OBJECT
    QThread thread_;

public:

    Loader();
    ~Loader();

public slots:
    void handleResults(bool result);

signals:
    void operate(Data& data);
    void success();
    void failure();
};


#endif // LOADER_H
