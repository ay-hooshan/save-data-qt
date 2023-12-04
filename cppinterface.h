#ifndef CPPINTERFACE_H
#define CPPINTERFACE_H

#include <QObject>

#include "personmodel.h"

class CPPInterface : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int counter READ counter WRITE setcounter NOTIFY counterChanged FINAL)
    Q_PROPERTY(QString name READ name WRITE setname NOTIFY nameChanged FINAL)
    Q_PROPERTY(PersonModel *personModel READ personModel WRITE setPersonModel NOTIFY personModelChanged FINAL)

public:
    CPPInterface();
    int counter() const;
    Q_INVOKABLE void setcounter(int newCounter);


    Q_INVOKABLE void saveCounterToSetting();
    Q_INVOKABLE void saveNameToFile();
    Q_INVOKABLE void savePersonToFile();

    PersonModel *personModel() const;
    void setPersonModel(PersonModel *newPersonModel);

    QString name() const;
    void setname(const QString &newName);

signals:
    void counterChanged();

    void nameChanged();

    void personModelChanged();

private:
    int m_counter;
    QString m_name;
    PersonModel *m_personModel;
};

#endif // CPPINTERFACE_H
