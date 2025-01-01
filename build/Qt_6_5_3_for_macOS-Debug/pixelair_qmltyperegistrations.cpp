/****************************************************************************
** Generated QML type registration code
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <QtQml/qqml.h>
#include <QtQml/qqmlmoduleregistration.h>

#include <canvascontroller.h>
#include <canvasrenderer.h>


#if !defined(QT_STATIC)
#define Q_QMLTYPE_EXPORT Q_DECL_EXPORT
#else
#define Q_QMLTYPE_EXPORT
#endif
Q_QMLTYPE_EXPORT void qml_register_types_PixelAir()
{
    qmlRegisterTypesAndRevisions<CanvasController>("PixelAir", 1);
    qmlRegisterTypesAndRevisions<CanvasRenderer>("PixelAir", 1);
    qmlRegisterAnonymousType<QQuickItem, 254>("PixelAir", 1);
    qmlRegisterModule("PixelAir", 1, 0);
}

static const QQmlModuleRegistration registration("PixelAir", qml_register_types_PixelAir);
