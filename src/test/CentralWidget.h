#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include <memory>

namespace Icd {
class Table;
typedef std::shared_ptr<Table> TablePtr;
}

// class CentralWidget

class CentralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CentralWidget(QWidget *parent = nullptr);

signals:

public slots:

private:
    bool init();

private:
    Icd::TablePtr table_;
};

#endif // CENTRALWIDGET_H
