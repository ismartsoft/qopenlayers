#ifndef QOL_VIEW_H
#define QOL_VIEW_H

#include "qol_global.h"
#include <QWidget>

namespace QOL {

// class View

class ViewPrivate;

class QOL_EXPORT View : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(double centerLat READ centerLat WRITE setCenterLat NOTIFY centerLatChanged)
    Q_PROPERTY(double centerLon READ centerLon WRITE setCenterLon NOTIFY centerLonChanged)
    Q_PROPERTY(int minZoom READ minZoom WRITE setMinZoom NOTIFY minZoomChanged)
    Q_PROPERTY(int maxZoom READ maxZoom WRITE setMaxZoom NOTIFY maxZoomChanged)
    Q_PROPERTY(int zoom READ zoom WRITE setZoom NOTIFY zoomChanged)
public:
    explicit View(QWidget *parent = nullptr);
    ~View();

    double centerLat() const;
    double centerLon() const;
    int minZoom() const;
    int maxZoom() const;
    int zoom() const;

signals:
    void centerLatChanged(double value);
    void centerLonChanged(double value);
    void minZoomChanged(int value);
    void maxZoomChanged(int value);
    void zoomChanged(int value);

    void focusPoints();

public slots:
    void setCenterLat(double value);
    void setCenterLon(double value);
    void setMinZoom(int value);
    void setMaxZoom(int value);
    void setZoom(int value);

private:
    Q_DISABLE_COPY(View)
    J_DECLARE_PRIVATE(View)
};

}

#endif // QOL_VIEW_H
