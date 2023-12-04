#include <QJsonArray>
#include <QJsonDocument>

#include "personmodel.h"

QVariant PersonModel::data(const QModelIndex &index, int role) const
{
    return QVariant("null");
}

int PersonModel::rowCount(const QModelIndex &parent) const
{
    return mPersons.size();
}

Person PersonModel::fromJson(const QJsonObject &json)
{
    Person result;

    if (const QJsonValue v = json["firstName"]; v.isString()) {
        result.firstName = v.toString();
    }

    if (const QJsonValue v = json["lastName"]; v.isString()) {
        result.lastName = v.toString();
    }

    if (const QJsonValue v = json["age"]; v.isDouble()) {
        result.age = v.toDouble();
    }

    if (const QJsonValue v = json["phoneNumbers"]; v.isArray()) {
        QJsonArray phoneNumArray = v.toArray();
        result.phoneNumbers.reserve(phoneNumArray.size());
        for (const QJsonValue &phoneNumber : phoneNumArray)
            result.phoneNumbers.append(phoneNumber.toString());
    }

    if (const QJsonValue v = json["addresses"]; v.isArray()) {
        QJsonArray addressesArray = v.toArray();
        result.addresses.reserve(addressesArray.size());
        for (const QJsonValue &address : addressesArray)
            result.addresses.append(AddressModel::fromJson(address.toObject()));
    }

    return result;
}

QJsonObject PersonModel::toJson(const Person &person)
{
    QJsonObject json;

    json["firstName"] = person.firstName;
    json["lastName"] = person.lastName;
    json["age"] = person.age;

    QJsonArray phoneNumberArray;
    for (const QString &tag : person.phoneNumbers)
        phoneNumberArray.append(tag);
    json["phoneNumbers"] = phoneNumberArray;

    QJsonArray addressesArray;
    for (const Address &address : person.addresses)
        addressesArray.append(AddressModel::toJson(address));
    json["addresses"] = addressesArray;

    return json;
}

Person PersonModel::getPerson(QModelIndex index)
{
    return *mPersons.at(index.row());
}

Person PersonModel::getPerson(int index)
{
    return *mPersons.at(index);
}

QString PersonModel::getFullName(QModelIndex index)
{
    return mPersons.at(index.row())->firstName + " " + mPersons.at(index.row())->lastName;
}

QString PersonModel::getPersonJson(int index)
{
    return QJsonDocument(toJson(*mPersons.at(index))).toJson(QJsonDocument::Indented);
}

void PersonModel::appendRow(Person *person)
{
    beginInsertRows(QModelIndex(), mPersons.size(), mPersons.size());
    mPersons.append(person);
    endInsertRows();
}

void PersonModel::appendRow(QString jsonString)
{
    QJsonObject obj;
    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());

    if(!doc.isNull())
    {
        if(doc.isObject())
        {
            obj = doc.object();
        }
        else
        {
            qDebug() << "Document is not an object";
        }
    }
    else
    {
        qDebug() << "Invalid JSON...\n" << jsonString;
    }

    Person person = fromJson(obj);
    Person *personToAppend = new Person(person);
    appendRow(personToAppend);
}
