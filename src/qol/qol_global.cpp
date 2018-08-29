#include "qol_global.h"
#include <QTranslator>
#include <QCoreApplication>

// class QOLMainPrivate

class QOLMainPrivate
{
public:
    QOLMainPrivate(QOLMain *q)
        : J_QPTR(q)
        , translator(nullptr)
    {

    }

    void init();

private:
    J_DECLARE_PUBLIC(QOLMain)
    QTranslator *translator;
    QList<SingletonReleaseCallback> callbacks;
    QString mapDir;
};

void QOLMainPrivate::init()
{
    if (qApp) {
        translator = new QTranslator();
        bool result = translator->load(":/qol/lang/zh_CN.qm");
        if (result) {
            qApp->installTranslator(translator);
        }
    }
}

// class IcdCore

J_IMPLEMENT_SINGLE_INSTANCE(QOLMain, QOLMain)

bool QOLMain::init()
{
    return true;
}

void QOLMain::registerSingletonRelease(SingletonReleaseCallback callback)
{
    if (!callback) {
        return;
    }

    Q_D(QOLMain);
    if (d->callbacks.contains(callback)) {
        return;
    }

    return d->callbacks.append(callback);
}

QString QOLMain::mapDir() const
{
    Q_D(const QOLMain);
    return d->mapDir;
}

void QOLMain::setMapDir(const QString &path)
{
    Q_D(QOLMain);
    if (path != d->mapDir) {
        d->mapDir = path;
        emit mapDirChanged(path);
    }
}

QOLMain::QOLMain(QObject *parent)
    : QObject(parent)
    , J_DPTR(new QOLMainPrivate(this))
{
    Q_INIT_RESOURCE(resource);
    Q_D(QOLMain);
    d->init();
}

QOLMain::~QOLMain()
{
    Q_D(QOLMain);

    if (d->translator) {
        qApp->removeTranslator(d->translator);
        delete d->translator;
    }

    foreach (auto &callback, d->callbacks) {
        if (callback) {
            callback();
        }
    }

    delete d;

    Q_CLEANUP_RESOURCE(resource);
}
