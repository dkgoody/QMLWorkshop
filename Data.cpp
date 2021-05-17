#include "Data.h"
#include "Service.h"

#include <QDebug>
#include <fstream>
#include "QFile"
#include "QDir"
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonArray"


Data::Item::Item(const QJsonObject& json_obj)
{
    title_ = json_obj["title"].toString();
    id_ = (uint)json_obj["id"].toInt();
    albumId_ = (uint)json_obj["id"].toInt();
}

bool Data::Item::load_thumbnail()
{
    return Service::get(thumbnail_url_, thumbnail_);
}


bool Data::read(const std::string& fileName)
{
    QFile file(QString(fileName.c_str()));
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    if (!file.isOpen())
    {
        return false;
    }

    auto jsonData = file.readAll();
    file.close();

    auto document = QJsonDocument::fromJson(jsonData);

    foreach (const QJsonValue & v, document.array())
    {
        items_.push_back(Item(v.toObject()));
    }

    struct
    {
        bool operator()(const Item& a, const Item& b) const
        {
            return (a.albumId() < b.albumId()) || (a.albumId() == b.albumId() && a.id() < b.id());
        }
    } sortingItem;

    std::sort(items_.begin(), items_.end(), sortingItem);

    return true;
}

