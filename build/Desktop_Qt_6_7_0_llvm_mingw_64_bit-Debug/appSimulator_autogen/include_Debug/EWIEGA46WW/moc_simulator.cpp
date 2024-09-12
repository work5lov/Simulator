/****************************************************************************
** Meta object code from reading C++ file 'simulator.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../progs/Qt/Simulator/simulator.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'simulator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.0. It"
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
struct qt_meta_stringdata_CLASSSimulatorENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSSimulatorENDCLASS = QtMocHelpers::stringData(
    "Simulator",
    "ipAddressChanged",
    "",
    "connectionStatusChanged",
    "progressChanged",
    "connectionErrorOccurred",
    "errorMessage",
    "connectToVPN",
    "disconnectFromVPN",
    "startProgressAnimation",
    "generateIPAddress",
    "country",
    "ipAddress",
    "connectionStatus",
    "progress"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSSimulatorENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       3,   74, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   62,    2, 0x06,    4 /* Public */,
       3,    0,   63,    2, 0x06,    5 /* Public */,
       4,    0,   64,    2, 0x06,    6 /* Public */,
       5,    1,   65,    2, 0x06,    7 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       7,    0,   68,    2, 0x0a,    9 /* Public */,
       8,    0,   69,    2, 0x0a,   10 /* Public */,
       9,    0,   70,    2, 0x0a,   11 /* Public */,
      10,    1,   71,    2, 0x0a,   12 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   11,

 // properties: name, type, flags
      12, QMetaType::QString, 0x00015103, uint(0), 0,
      13, QMetaType::QString, 0x00015001, uint(1), 0,
      14, QMetaType::Int, 0x00015001, uint(2), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject Simulator::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSSimulatorENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSSimulatorENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSSimulatorENDCLASS_t,
        // property 'ipAddress'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'connectionStatus'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'progress'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Simulator, std::true_type>,
        // method 'ipAddressChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'connectionStatusChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'progressChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'connectionErrorOccurred'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'connectToVPN'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'disconnectFromVPN'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'startProgressAnimation'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'generateIPAddress'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>
    >,
    nullptr
} };

void Simulator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Simulator *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->ipAddressChanged(); break;
        case 1: _t->connectionStatusChanged(); break;
        case 2: _t->progressChanged(); break;
        case 3: _t->connectionErrorOccurred((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->connectToVPN(); break;
        case 5: _t->disconnectFromVPN(); break;
        case 6: _t->startProgressAnimation(); break;
        case 7: _t->generateIPAddress((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Simulator::*)();
            if (_t _q_method = &Simulator::ipAddressChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Simulator::*)();
            if (_t _q_method = &Simulator::connectionStatusChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Simulator::*)();
            if (_t _q_method = &Simulator::progressChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Simulator::*)(const QString & );
            if (_t _q_method = &Simulator::connectionErrorOccurred; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    } else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<Simulator *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->ipAddress(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->connectionStatus(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->progress(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<Simulator *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setIpAddress(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
}

const QMetaObject *Simulator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Simulator::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSSimulatorENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Simulator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void Simulator::ipAddressChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Simulator::connectionStatusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Simulator::progressChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Simulator::connectionErrorOccurred(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
