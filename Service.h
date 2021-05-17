#ifndef SERVICE_H
#define SERVICE_H

#include <QImage>
#include <QString>

class Service
{

public:
    static bool get(const QString& url, QImage& image);
};


#endif // SERVICE_H
