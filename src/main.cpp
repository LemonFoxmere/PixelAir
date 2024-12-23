#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include "macos/windowHelper/MacOSWindowHelper.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/PixelAir/qml/Main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    // Access the root object (ApplicationWindow) and customize MacOS window
    if (!engine.rootObjects().isEmpty()) {
        QObject *rootObject = engine.rootObjects().first();
        QQuickWindow *window = qobject_cast<QQuickWindow *>(rootObject);
        if (window) {
            customizeMacOSWindow(window->winId());
        }
    }

    return app.exec();
}
