#ifndef QOL_GLOBAL_H
#define QOL_GLOBAL_H

#ifdef QOL_LIB
#if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#   ifdef QOL_BUILD
#       define QOL_EXPORT __declspec(dllexport)
#   else
#       define QOL_EXPORT __declspec(dllimport)
#       if defined(DEBUG) || defined(_DEBUG)
#           pragma comment(lib, "qold.lib")
#       else
#           pragma comment(lib, "qol.lib")
#       endif
#   endif // !QOL_BUILD
#endif // _MSC_VER || ...
#endif // QOL_LIB

#ifndef QOL_EXPORT
#define QOL_EXPORT
#endif

////////////////////////////////

#include <qglobal.h>

// - private pointer
#ifndef J_DECLARE_PRIVATE
#define J_DECLARE_PRIVATE(Class) \
    Class##Private *d_ptr_; \
    inline Class##Private* d_func() { return d_ptr_; } \
    inline const Class##Private* d_func() const { return d_ptr_; } \
    friend class Class##Private;
#endif

#ifndef J_DECLARE_PUBLIC
#define J_DECLARE_PUBLIC(Class) \
    Class *q_ptr_; \
    inline Class* q_func() { return q_ptr_; } \
    inline const Class* q_func() const { return q_ptr_; } \
    friend class Class;
#endif

#ifndef J_DPTR
#define J_DPTR d_ptr_
#endif

#ifndef J_QPTR
#define J_QPTR q_ptr_
#endif

#ifndef J_DECLARE_SINGLE_INSTANCE
#define J_DECLARE_SINGLE_INSTANCE(Class) \
    public: \
        static Class *instance(); \
        static void releaseInstance(); \
    private: \
        static Class *_instance;
#endif

#ifndef J_IMPLEMENT_SINGLE_INSTANCE
#define J_IMPLEMENT_SINGLE_INSTANCE(Class, GlobalClass) \
    \
    static void __ ## Class ## _releaseInstance() { \
        Class::releaseInstance(); \
    } \
    Class *Class::_instance = 0; \
    \
    Class *Class::instance() { \
        if (Class::_instance == 0) { \
            Class::_instance = new Class; \
        } \
        if (QLatin1String(QT_STRINGIFY(Class)) != #GlobalClass) { \
            GlobalClass::instance()->registerSingletonRelease(__ ## Class ## _releaseInstance); \
        } \
        return Class::_instance; \
    } \
    \
    void Class::releaseInstance() { \
        if (Class::_instance != 0) { \
            delete Class::_instance; \
            Class::_instance = 0; \
        } \
    }
#endif

#ifndef J_SINGLE_RELEASE_CALLBACK
#define J_SINGLE_RELEASE_CALLBACK
typedef void(*SingletonReleaseCallback)();
#endif

#include <QObject>

// class QOLMain

class QOLMainPrivate;

class QOL_EXPORT QOLMain : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString mapDir READ mapDir WRITE setMapDir NOTIFY mapDirChanged)
public:
    bool init();
    void registerSingletonRelease(SingletonReleaseCallback callback);

    QString mapDir() const;

signals:
    void mapDirChanged(const QString &path);

public slots:
    void setMapDir(const QString &path);

private:
    explicit QOLMain(QObject *parent = nullptr);
    ~QOLMain();

private:
    Q_DISABLE_COPY(QOLMain)
    J_DECLARE_PRIVATE(QOLMain)
    J_DECLARE_SINGLE_INSTANCE(QOLMain)
};

#endif // QOL_GLOBAL_H
