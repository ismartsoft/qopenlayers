#include "MainWindow.h"
#include "CentralWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(1000, 650);

    CentralWidget *centralWidget = new CentralWidget(this);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{

}

bool MainWindow::init()
{
    return true;
}
