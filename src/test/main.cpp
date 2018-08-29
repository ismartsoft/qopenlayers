#include <QApplication>
#include <QTranslator>
#include <QTextCodec>
#include <QFile>
#include <QDebug>
#include "MainWindow.h"
#include "qol_global.h"

int main(int argc, char **argv)
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
#if QT_VERSION >= 0x050600
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QApplication app(argc, argv);
    QApplication::setFont(QFont("Microsoft Yahei", 9));
    QApplication::setWindowIcon(QIcon(":/qol/image/app.png"));
    QCoreApplication::setOrganizationName("Smartsoft");
    QCoreApplication::setApplicationName("QOL Demo");
    QCoreApplication::setApplicationVersion(QString("1.0.0"));

    // stylesheet
    QFile file(":/qol/qss/dark.qss");
    if (!file.open(QIODevice::ReadOnly)) {
        return -1;
    }
    app.setStyleSheet(file.readAll());

    // translator

    QApplication::setApplicationDisplayName(QObject::tr("QOL Demo"));

    //
    QOLMain::instance()->init();

    //
    MainWindow mainWindow;
    if (!mainWindow.init()) {
        return -1;
    }

    mainWindow.show();

    int result = app.exec();

    QOLMain::releaseInstance();

    return result;
}
