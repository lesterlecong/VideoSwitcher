#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "videocontroller.h"


//#include <QQmlEngine>
//#include <QQmlComponent>
//#include <QQmlProperty>
//#include <QDebug>
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<VideoController>("com.techadvise.videocontroller",1,0,"VideoController");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;



    //QQmlEngine vidControllerEngine;
    //QQmlComponent component(&vidControllerEngine, QUrl(QStringLiteral("qrc:/main.qml")));
    //QObject *object = component.create();

    //qDebug() << "Property Value VidSource:" << QQmlProperty::read(object, "vidSource");
    //QQmlProperty::write(object, "vidSource", "file:///e:/Projects/Qt/Video-Switcher/video1.mp4");
    //delete object;

    return app.exec();
}
