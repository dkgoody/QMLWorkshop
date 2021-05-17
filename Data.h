#ifndef DATA_H
#define DATA_H

#include <QImage>
#include <QJsonObject>
#include <vector>

class Data
{
public:
    class Item
    {
    public:
        Item() {};
        ~Item() = default;
        Item(const Item &) = default;
        Item &operator=(const Item &) = default;

        Item(const QJsonObject& json_obj);

        uint id() const { return id_; }
        uint albumId() const { return albumId_; }
        const QString& title() const { return title_; }
        const QString& url() const { return url_; }
        const QImage thumbnail() const { return thumbnail_; }


        bool load_thumbnail();

    private:
       uint albumId_;
       uint id_;
       QString title_;
       QString url_;
       QString thumbnail_url_;
       QImage thumbnail_;
    };

    Data() = default;
    bool read(const std::string& file_path);
    const std::vector<Item>& items() const { return items_; }
    std::vector<Item>& items() { return items_; }


private:
    std::vector<Item> items_;

    //TODO Add albums_ vector to point to the first element in the album_
    //TODO Add functions to allow showing rows of albums
};


#endif // DATA_H
