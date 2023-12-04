#ifndef PERSONMODEL_H
#define PERSONMODEL_H

#include <QAbstractListModel>

#include "addressmodel.h"

struct Person
{
    QString firstName;
    QString lastName;
    int age;
    QVector<QString> phoneNumbers;
    QVector<Address> addresses;
};

class PersonModel : public QAbstractListModel
{
    Q_OBJECT

public:
    virtual QVariant data(const QModelIndex &index, int role) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    static Person fromJson(const QJsonObject &json);
    static QJsonObject toJson(const Person &person);

    Q_INVOKABLE Person getPerson(QModelIndex index);
    Q_INVOKABLE Person getPerson(int index);
    Q_INVOKABLE QString getFullName(QModelIndex index);
    Q_INVOKABLE QString getPersonJson(int index);

    // TODO: write json from string and string from json function :/

    Q_INVOKABLE void appendRow(Person *person);
    Q_INVOKABLE void appendRow(QString jsonString);

private:
    QVector<Person *> mPersons;
};

#endif // PERSONMODEL_H
