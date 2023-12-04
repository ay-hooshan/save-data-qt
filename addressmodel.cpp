#include <QJsonArray>

#include "addressmodel.h"

AddressModel::AddressModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}

int AddressModel::rowCount(const QModelIndex &parent) const
{
    return mAddresses.size();
}

Address AddressModel::fromJson(const QJsonObject &json)
{
    Address result;

    if (const QJsonValue v = json["street"]; v.isString()) {
        result.street = v.toString();
    }

    if (const QJsonValue v = json["city"]; v.isString()) {
        result.city = v.toString();
    }

    if (const QJsonValue v = json["tags"]; v.isArray()) {
        QJsonArray tagsArray = v.toArray();
        result.tags.reserve(tagsArray.size());
        for (const QJsonValue &tag : tagsArray)
            result.tags.append(tag.toString());
    }

    return result;
}

QJsonObject AddressModel::toJson(const Address &address)
{
    QJsonObject json;

    json["street"] = address.street;
    json["city"] = address.city;

    QJsonArray tagsArray;
    for (const QString &tag : address.tags)
        tagsArray.append(tag);
    json["tags"] = tagsArray;

    return json;
}
