#include "Model.h"
#include <QDebug>


Model::Model(QObject *parent, Data* data, uint columns)
    : QAbstractTableModel(parent), data_(data), columns_(columns), loaded_(false)
{
}

int Model::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return (data_ && columns_) ? (data_->items().size() + columns_ - 1)/columns_ : 0;
}

int Model::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return columns_;
}

QVariant Model::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !data_)
        return QVariant();

    auto flat_index = index.row()*columns_ + index.column();
    if (flat_index > data_->items().size())
    {
        return QVariant();
    }

    auto *item = &data_->items()[flat_index];

    switch (role)
    {
    case (Qt::DisplayRole):
        return QString::number(item->id());
        //TODO: display thumbnail
        //return item->thumbnail();
    }

    return item->title();
}
