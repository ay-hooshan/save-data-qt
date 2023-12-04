#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "cppinterface.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    CPPInterface *cppInterface = new CPPInterface;
    qmlRegisterType<CPPInterface>("AyInterface", 1, 0, "AyCppInterface");

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/qmlcounter/Main.qml"_qs);

    engine.rootContext()->setContextProperty(QStringLiteral("ayInterface"), cppInterface);

    engine.load(url);

    return app.exec();
}
