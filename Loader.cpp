#include "Loader.h"


void Worker::doWork(Data& data) {

    bool result = false;
    for (auto& it : data.items())
    {

        if (it.load_thumbnail())
        {
            //At least one loaded image is treated as success
            result = true;
        }
    }

    //TODO remove sleep
    QThread::sleep(5);

    emit resultReady(result);
}


Loader::Loader()
{
    Worker *worker = new Worker;
    worker->moveToThread(&thread_);

    connect(&thread_, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &Loader::operate, worker, &Worker::doWork);
    connect(worker, &Worker::resultReady, this, &Loader::handleResults);

    thread_.start();
}


Loader::~Loader()
{
    thread_.quit();
    thread_.wait();
}

void Loader::handleResults(bool result)
{
    if (!result)
    {
        //FIXME Error handler
        qDebug() << "Unable to load any of the images";
        emit failure();
    }

    emit success();
}
