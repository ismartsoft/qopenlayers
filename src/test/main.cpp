#include <QApplication>
#include <QTranslator>
#include <QTextCodec>
#include <QFile>
#include <QDebug>
#include "MainWindow.h"

int main(int argc, char **argv)
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
#if QT_VERSION >= 0x050600
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QApplication app(argc, argv);
    QApplication::setFont(QFont("Microsoft Yahei", 9));
    QApplication::setWindowIcon(QIcon(":/image/app.png"));
    QCoreApplication::setOrganizationName("Smartsoft");
    QCoreApplication::setApplicationName("XXX");
    QCoreApplication::setApplicationVersion(QString("1.0.0"));

    // stylesheet
    QFile file(":/qss/dark.qss");
    if (!file.open(QIODevice::ReadOnly)) {
        return -1;
    }
    app.setStyleSheet(file.readAll());

    // translator

    QApplication::setApplicationDisplayName(QObject::tr("XXX"));

    MainWindow mainWindow;
    if (!mainWindow.init()) {
        return -1;
    }

    mainWindow.show();

    return app.exec();
}
