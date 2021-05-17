#ifndef MODEL_H
#define MODEL_H

#include <QAbstractTableModel>
#include "Data.h"

class Model : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit Model(QObject *parent = nullptr, Data *data = nullptr, uint columns = 10);

    Q_PROPERTY(double loaded READ loaded NOTIFY loadedChanged)

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

signals:
    void loadedChanged(bool);

public slots:
    void onTest()
    {
       qDebug() << "you clicked!!";
       setLoaded();
    }

    void onClicked(int row)
    {
        qDebug() << QString::number(row);
    }

    bool setLoaded()
    {
        loaded_ = true;
        emit loadedChanged(loaded_);
    }
    bool loaded() const { return loaded_; }


private:
    Data* data_;
    uint columns_;
    bool loaded_;
};

#endif // MODEL_H
