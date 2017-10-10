/****************************************************************************
** Meta object code from reading C++ file 'qt.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qt.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qt.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      34,   11,   12,   11, 0x08,
      46,   11,   11,   11, 0x08,
      54,   11,   11,   11, 0x08,
      64,   11,   11,   11, 0x08,
      85,   11,   73,   11, 0x08,
      98,   11,   11,   11, 0x08,
     108,   11,   11,   11, 0x08,
     121,   11,   11,   11, 0x08,
     133,   11,   11,   11, 0x08,
     146,   11,   11,   11, 0x08,
     170,  157,   11,   11, 0x08,
     189,   11,   11,   11, 0x08,
     198,  157,   11,   11, 0x08,
     213,  157,   11,   11, 0x08,
     230,   11,   11,   11, 0x08,
     237,   11,   11,   11, 0x08,
     244,   11,   11,   11, 0x08,
     256,  157,   11,   11, 0x08,
     275,   11,   11,   11, 0x08,
     289,   11,   11,   11, 0x08,
     305,   11,  297,   11, 0x08,
     319,   11,   11,   11, 0x08,
     336,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0std::vector<Product*>\0"
    "addSearch()\0close()\0addView()\0addBuy()\0"
    "std::string\0chooseUser()\0addCart()\0"
    "addProduct()\0sortAlpha()\0sortRating()\0"
    "sortDate()\0productIndex\0removeProduct(int)\0"
    "remove()\0addToCart(int)\0viewReviews(int)\0"
    "save()\0quit()\0addReview()\0addTheReviews(int)\0"
    "closeReview()\0addIt()\0Review*\0"
    "inputReview()\0reccomendation()\0"
    "doneWithRec()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: { std::vector<Product*> _r = _t->addSearch();
            if (_a[0]) *reinterpret_cast< std::vector<Product*>*>(_a[0]) = _r; }  break;
        case 1: _t->close(); break;
        case 2: _t->addView(); break;
        case 3: _t->addBuy(); break;
        case 4: { std::string _r = _t->chooseUser();
            if (_a[0]) *reinterpret_cast< std::string*>(_a[0]) = _r; }  break;
        case 5: _t->addCart(); break;
        case 6: _t->addProduct(); break;
        case 7: _t->sortAlpha(); break;
        case 8: _t->sortRating(); break;
        case 9: _t->sortDate(); break;
        case 10: _t->removeProduct((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->remove(); break;
        case 12: _t->addToCart((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->viewReviews((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->save(); break;
        case 15: _t->quit(); break;
        case 16: _t->addReview(); break;
        case 17: _t->addTheReviews((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->closeReview(); break;
        case 19: _t->addIt(); break;
        case 20: { Review* _r = _t->inputReview();
            if (_a[0]) *reinterpret_cast< Review**>(_a[0]) = _r; }  break;
        case 21: _t->reccomendation(); break;
        case 22: _t->doneWithRec(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    }
    return _id;
}
static const uint qt_meta_data_LoginWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x08,
      25,   12,   12,   12, 0x08,
      36,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_LoginWindow[] = {
    "LoginWindow\0\0quitLogin()\0goToMain()\0"
    "newUserLogin()\0"
};

void LoginWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LoginWindow *_t = static_cast<LoginWindow *>(_o);
        switch (_id) {
        case 0: _t->quitLogin(); break;
        case 1: _t->goToMain(); break;
        case 2: _t->newUserLogin(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData LoginWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LoginWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_LoginWindow,
      qt_meta_data_LoginWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LoginWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LoginWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LoginWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LoginWindow))
        return static_cast<void*>(const_cast< LoginWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int LoginWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
