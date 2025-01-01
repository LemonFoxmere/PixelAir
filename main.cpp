#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <macos/windowHelper/MacOSWindowHelper.h>
#include <QDebug>
#include <QDir>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);

    QGuiApplication app(argc, argv);
    app.setApplicationName("PixelAir");
    app.setApplicationDisplayName("PixelAir");

    app.setWindowIcon(QIcon(":/images/raster/resources/appicon.png"));

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/PixelAir/Main.qml")));

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
