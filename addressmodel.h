#ifndef ADDRESSMODEL_H
#define ADDRESSMODEL_H

#include <QAbstractItemModel>
#include <QJsonObject>

struct Address
{
    QString street;
    QString city;
    QVector<QString> tags;
};

class AddressModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit AddressModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    static Address fromJson(const QJsonObject &json);
    static QJsonObject toJson(const Address &address);

private:
    QVector<Address *> mAddresses;
};

#endif // ADDRESSMODEL_H
