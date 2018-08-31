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

    QHBoxLayout *layoutBottom = new QHBoxLayout();
    layoutMain->addLayout(layoutBottom);

    layoutBottom->addStretch();

    QPushButton *buttonFocus = new QPushButton(tr("Focus points"), this);
    buttonFocus->setFixedWidth(100);
    layoutBottom->addWidget(buttonFocus);

    layoutBottom->addStretch();

    connect(buttonFocus, &QPushButton::clicked, this, [=](){
        olView->focusPoints();
    });

    // -- init --

    // mapDir
    QOLMain::instance()->setMapDir("C:/Users/iclosure/Documents/GitHub/map/_alllayers");
    //
}
