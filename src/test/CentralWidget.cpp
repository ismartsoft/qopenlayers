#include "CentralWidget.h"
#include <QtWidgets>
#include <QCoreApplication>
#include "SlaverPane.h"
#include "jwt/jwt_inc.h"
#include "icdcore/icdcore_inc.h"
#include "icdparser/icdparser_inc.h"

CentralWidget::CentralWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layoutMain = new QVBoxLayout(this);
    layoutMain->setContentsMargins(0, 0, 0, 0);

    QTabWidget *tabWidget = new QTabWidget(this);
    tabWidget->setStyleSheet("QTabWidget::tab-bar{alignment:center;} "
                             "QTabWidget QTabBar::tab{min-width:8em;min-height:30px;}");
    layoutMain->addWidget(tabWidget);

    for (int i = 0; i < 4; ++i) {
        SlaverPane *newPane = new SlaverPane(this);
        tabWidget->addTab(newPane, tr("Slaver %1").arg(i + 1));
    }

    if (!init()) {
        //
    }
}

bool CentralWidget::init()
{
    Json::Value config(Json::objectValue);
    config["sourceType"] = "file";
    config["filePath"] = ;

    return true;
}

