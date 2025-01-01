/****************************************************************************
** Meta object code from reading C++ file 'canvascontroller.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/controllers/canvascontroller.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'canvascontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSCanvasControllerENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSCanvasControllerENDCLASS = QtMocHelpers::stringData(
    "CanvasController",
    "QML.Element",
    "auto",
    "QML.Singleton",
    "true",
    "widthChanged",
    "",
    "heightChanged",
    "activeLayerChanged",
    "drawPixel",
    "x",
    "y",
    "uint8_t",
    "r",
    "g",
    "b",
    "a",
    "c",
    "erasePixel",
    "clearLayer",
    "getPixel",
    "std::optional<Pixel>",
    "width",
    "height",
    "activeLayer"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSCanvasControllerENDCLASS_t {
    uint offsetsAndSizes[50];
    char stringdata0[17];
    char stringdata1[12];
    char stringdata2[5];
    char stringdata3[14];
    char stringdata4[5];
    char stringdata5[13];
    char stringdata6[1];
    char stringdata7[14];
    char stringdata8[19];
    char stringdata9[10];
    char stringdata10[2];
    char stringdata11[2];
    char stringdata12[8];
    char stringdata13[2];
    char stringdata14[2];
    char stringdata15[2];
    char stringdata16[2];
    char stringdata17[2];
    char stringdata18[11];
    char stringdata19[11];
    char stringdata20[9];
    char stringdata21[21];
    char stringdata22[6];
    char stringdata23[7];
    char stringdata24[12];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSCanvasControllerENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSCanvasControllerENDCLASS_t qt_meta_stringdata_CLASSCanvasControllerENDCLASS = {
    {
        QT_MOC_LITERAL(0, 16),  // "CanvasController"
        QT_MOC_LITERAL(17, 11),  // "QML.Element"
        QT_MOC_LITERAL(29, 4),  // "auto"
        QT_MOC_LITERAL(34, 13),  // "QML.Singleton"
        QT_MOC_LITERAL(48, 4),  // "true"
        QT_MOC_LITERAL(53, 12),  // "widthChanged"
        QT_MOC_LITERAL(66, 0),  // ""
        QT_MOC_LITERAL(67, 13),  // "heightChanged"
        QT_MOC_LITERAL(81, 18),  // "activeLayerChanged"
        QT_MOC_LITERAL(100, 9),  // "drawPixel"
        QT_MOC_LITERAL(110, 1),  // "x"
        QT_MOC_LITERAL(112, 1),  // "y"
        QT_MOC_LITERAL(114, 7),  // "uint8_t"
        QT_MOC_LITERAL(122, 1),  // "r"
        QT_MOC_LITERAL(124, 1),  // "g"
        QT_MOC_LITERAL(126, 1),  // "b"
        QT_MOC_LITERAL(128, 1),  // "a"
        QT_MOC_LITERAL(130, 1),  // "c"
        QT_MOC_LITERAL(132, 10),  // "erasePixel"
        QT_MOC_LITERAL(143, 10),  // "clearLayer"
        QT_MOC_LITERAL(154, 8),  // "getPixel"
        QT_MOC_LITERAL(163, 20),  // "std::optional<Pixel>"
        QT_MOC_LITERAL(184, 5),  // "width"
        QT_MOC_LITERAL(190, 6),  // "height"
        QT_MOC_LITERAL(197, 11)   // "activeLayer"
    },
    "CanvasController",
    "QML.Element",
    "auto",
    "QML.Singleton",
    "true",
    "widthChanged",
    "",
    "heightChanged",
    "activeLayerChanged",
    "drawPixel",
    "x",
    "y",
    "uint8_t",
    "r",
    "g",
    "b",
    "a",
    "c",
    "erasePixel",
    "clearLayer",
    "getPixel",
    "std::optional<Pixel>",
    "width",
    "height",
    "activeLayer"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSCanvasControllerENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       2,   14, // classinfo
       8,   18, // methods
       3,  100, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // classinfo: key, value
       1,    2,
       3,    4,

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       5,    0,   66,    6, 0x06,    4 /* Public */,
       7,    0,   67,    6, 0x06,    5 /* Public */,
       8,    0,   68,    6, 0x06,    6 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       9,    6,   69,    6, 0x02,    7 /* Public */,
       9,    3,   82,    6, 0x02,   14 /* Public */,
      18,    2,   89,    6, 0x02,   18 /* Public */,
      19,    0,   94,    6, 0x02,   21 /* Public */,
      20,    2,   95,    6, 0x102,   22 /* Public | MethodIsConst  */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, 0x80000000 | 12, 0x80000000 | 12, 0x80000000 | 12, 0x80000000 | 12,   10,   11,   13,   14,   15,   16,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QColor,   10,   11,   17,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   10,   11,
    QMetaType::Void,
    0x80000000 | 21, QMetaType::Int, QMetaType::Int,   10,   11,

 // properties: name, type, flags
      22, QMetaType::Int, 0x00015103, uint(0), 0,
      23, QMetaType::Int, 0x00015103, uint(1), 0,
      24, QMetaType::Int, 0x00015103, uint(2), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject CanvasController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSCanvasControllerENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSCanvasControllerENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_metaTypeArray<
        // property 'width'
        int,
        // property 'height'
        int,
        // property 'activeLayer'
        int,
        // Q_OBJECT / Q_GADGET
        CanvasController,
        // method 'widthChanged'
        void,
        // method 'heightChanged'
        void,
        // method 'activeLayerChanged'
        void,
        // method 'drawPixel'
        void,
        int,
        int,
        uint8_t,
        uint8_t,
        uint8_t,
        uint8_t,
        // method 'drawPixel'
        void,
        int,
        int,
        QColor,
        // method 'erasePixel'
        void,
        int,
        int,
        // method 'clearLayer'
        void,
        // method 'getPixel'
        std::optional<Pixel>,
        int,
        int
    >,
    nullptr
} };

void CanvasController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CanvasController *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->widthChanged(); break;
        case 1: _t->heightChanged(); break;
        case 2: _t->activeLayerChanged(); break;
        case 3: _t->drawPixel((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<uint8_t>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<uint8_t>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<uint8_t>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<uint8_t>>(_a[6]))); break;
        case 4: _t->drawPixel((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QColor>>(_a[3]))); break;
        case 5: _t->erasePixel((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 6: _t->clearLayer(); break;
        case 7: { std::optional<Pixel> _r = _t->getPixel((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])));
            if (_a[0]) *reinterpret_cast< std::optional<Pixel>*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CanvasController::*)();
            if (_t _q_method = &CanvasController::widthChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CanvasController::*)();
            if (_t _q_method = &CanvasController::heightChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CanvasController::*)();
            if (_t _q_method = &CanvasController::activeLayerChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<CanvasController *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->width(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->height(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->activeLayer(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<CanvasController *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setWidth(*reinterpret_cast< int*>(_v)); break;
        case 1: _t->setHeight(*reinterpret_cast< int*>(_v)); break;
        case 2: _t->setActiveLayer(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
}

const QMetaObject *CanvasController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CanvasController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSCanvasControllerENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CanvasController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void CanvasController::widthChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void CanvasController::heightChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void CanvasController::activeLayerChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
