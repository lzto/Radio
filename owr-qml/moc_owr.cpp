/****************************************************************************
** Meta object code from reading C++ file 'owr.h'
**
** Created: Tue Jun 19 17:40:18 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "owr.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'owr.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_OWR[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       5,    4,    4,    4, 0x05,

 // slots: signature, parameters, type, tag, flags
      33,    4,    4,    4, 0x0a,
      44,    4,    4,    4, 0x0a,
      56,    4,    4,    4, 0x0a,
      78,    4,    4,    4, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_OWR[] = {
    "OWR\0\0signal_updateFreq(QVariant)\0"
    "slot_pre()\0slot_next()\0slot_trigger_update()\0"
    "get_current_freq()\0"
};

void OWR::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        OWR *_t = static_cast<OWR *>(_o);
        switch (_id) {
        case 0: _t->signal_updateFreq((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 1: _t->slot_pre(); break;
        case 2: _t->slot_next(); break;
        case 3: _t->slot_trigger_update(); break;
        case 4: _t->get_current_freq(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData OWR::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject OWR::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_OWR,
      qt_meta_data_OWR, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &OWR::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *OWR::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *OWR::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OWR))
        return static_cast<void*>(const_cast< OWR*>(this));
    return QObject::qt_metacast(_clname);
}

int OWR::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void OWR::signal_updateFreq(QVariant _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
