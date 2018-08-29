#include "CentralWidget.h"
#include <QtWidgets>
#include <QCoreApplication>
#include "qol_inc.h"

CentralWidget::CentralWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layoutMain = new QVBoxLayout(this);
    layoutMain->setContentsMargins(0, 0, 0, 0);

    QOL::View *olView = new QOL::View(this);
    layoutMain->addWidget(olView);

    // -- init --

    // mapDir
    QOLMain::instance()->setMapDir("C:/Users/iclosure/Documents/GitHub/yunlan-yanshan/_alllayers");
    //
}
