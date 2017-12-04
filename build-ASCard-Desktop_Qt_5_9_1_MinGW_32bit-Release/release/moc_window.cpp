/****************************************************************************
** Meta object code from reading C++ file 'window.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../window.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Window_t {
    QByteArrayData data[14];
    char stringdata0[237];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Window_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Window_t qt_meta_stringdata_Window = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Window"
QT_MOC_LITERAL(1, 7, 25), // "on_lineEdit_returnPressed"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 19), // "on_checkbox_Pressed"
QT_MOC_LITERAL(4, 54, 16), // "isCheckedButton6"
QT_MOC_LITERAL(5, 71, 16), // "isCheckedButton7"
QT_MOC_LITERAL(6, 88, 16), // "isCheckedButton3"
QT_MOC_LITERAL(7, 105, 19), // "isCheckedButtonhelp"
QT_MOC_LITERAL(8, 125, 18), // "writeButtonClicked"
QT_MOC_LITERAL(9, 144, 17), // "readButtonClicked"
QT_MOC_LITERAL(10, 162, 26), // "on_textBrowser_textChanged"
QT_MOC_LITERAL(11, 189, 15), // "ForPlusPlusLog1"
QT_MOC_LITERAL(12, 205, 15), // "ForPlusPlusLog2"
QT_MOC_LITERAL(13, 221, 15) // "ForPlusPlusLog3"

    },
    "Window\0on_lineEdit_returnPressed\0\0"
    "on_checkbox_Pressed\0isCheckedButton6\0"
    "isCheckedButton7\0isCheckedButton3\0"
    "isCheckedButtonhelp\0writeButtonClicked\0"
    "readButtonClicked\0on_textBrowser_textChanged\0"
    "ForPlusPlusLog1\0ForPlusPlusLog2\0"
    "ForPlusPlusLog3"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Window[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    1,   75,    2, 0x08 /* Private */,
       4,    0,   78,    2, 0x08 /* Private */,
       5,    0,   79,    2, 0x08 /* Private */,
       6,    0,   80,    2, 0x08 /* Private */,
       7,    0,   81,    2, 0x08 /* Private */,
       8,    0,   82,    2, 0x08 /* Private */,
       9,    0,   83,    2, 0x08 /* Private */,
      10,    0,   84,    2, 0x08 /* Private */,
      11,    0,   85,    2, 0x08 /* Private */,
      12,    0,   86,    2, 0x08 /* Private */,
      13,    0,   87,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Window::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Window *_t = static_cast<Window *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_lineEdit_returnPressed(); break;
        case 1: _t->on_checkbox_Pressed((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->isCheckedButton6(); break;
        case 3: _t->isCheckedButton7(); break;
        case 4: _t->isCheckedButton3(); break;
        case 5: _t->isCheckedButtonhelp(); break;
        case 6: _t->writeButtonClicked(); break;
        case 7: _t->readButtonClicked(); break;
        case 8: _t->on_textBrowser_textChanged(); break;
        case 9: _t->ForPlusPlusLog1(); break;
        case 10: _t->ForPlusPlusLog2(); break;
        case 11: _t->ForPlusPlusLog3(); break;
        default: ;
        }
    }
}

const QMetaObject Window::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Window.data,
      qt_meta_data_Window,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Window::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Window::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Window.stringdata0))
        return static_cast<void*>(const_cast< Window*>(this));
    return QWidget::qt_metacast(_clname);
}

int Window::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
