#include <QSettings>
#include <QFile>
#include <QDataStream>
#include <QJsonDocument>

#include "cppinterface.h"

CPPInterface::CPPInterface()
{
    // counter in setting
    QSettings settings("Hooshan", "AyCounter");

    QString data = settings.value("variables/counter", "null").toString();

    if (data == "null")
        m_counter = 0;
    else
        m_counter = data.toInt();


    // name in file
    QFile file("file.dat");

    if (file.open(QIODevice::ReadOnly)) {
        QDataStream in(&file);
        in >> m_name;
    } else {
        qDebug() << "fail to open file!!!!!";
        m_name = "default name";
    }


    // json in file
    m_personModel = new PersonModel;

    // TEST
    QFile personFile("person" + QString::number(0) + ".json");
    if (!personFile.open(QIODevice::ReadOnly)) {
        QVector<QString> tags1 = {"dangerous", "far", "magical"};
        QVector<QString> tags2 = {"dangerous"};

        Address address1 = Address{"Diagon", "London", tags1};
        Address address2 = Address{"Koooche", "Gangcity", tags2};

        QVector<QString> phoneNumbers1 = {"09003434", "091234567"};

        QVector<Address> addresses = {address1, address2};

        Person *person1 = new Person{"ali", "alavi", 20, phoneNumbers1, addresses};
        m_personModel->appendRow(person1);
    }
    // ENDTEST

    // reading json from file
    int i = 0;
    while (true) {
        QFile personFile("person" + QString::number(i) + ".json");
        if (!personFile.open(QIODevice::ReadOnly))
            break;

        QByteArray savedData = personFile.readAll();
        QJsonDocument loadDoc = QJsonDocument::fromJson(savedData);

        Person person = PersonModel::fromJson(loadDoc.object());
        Person *personToAppend = new Person(person);
        m_personModel->appendRow(personToAppend);
        i++;
    }
}

int CPPInterface::counter() const
{
    return m_counter;
}

void CPPInterface::setcounter(int newCounter)
{
    if (m_counter == newCounter)
        return;
    m_counter = newCounter;
    emit counterChanged();
}

void CPPInterface::saveCounterToSetting() {
    QSettings settings("Hooshan", "AyCounter");
    settings.setValue("variables/counter", m_counter);
}

void CPPInterface::saveNameToFile()
{
    QFile file("file.dat");
    file.open(QIODevice::WriteOnly);

    QDataStream out(&file);
    out << m_name;
}

void CPPInterface::savePersonToFile()
{
    for (int i = 0; i < m_personModel->rowCount(); ++i) {
        QFile file("person" + QString::number(i) + ".json");
        file.open(QIODevice::WriteOnly);

        QJsonObject jsonObject = PersonModel::toJson(m_personModel->getPerson(i));
        file.write(QJsonDocument(jsonObject).toJson());
    }
}

PersonModel *CPPInterface::personModel() const
{
    return m_personModel;
}

void CPPInterface::setPersonModel(PersonModel *newPersonModel)
{
    if (m_personModel == newPersonModel)
        return;
    m_personModel = newPersonModel;
    emit personModelChanged();
}

QString CPPInterface::name() const
{
    return m_name;
}

void CPPInterface::setname(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}
