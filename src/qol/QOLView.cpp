#include "QOLView.h"
#include <QtWebChannel>
#include <QtWebSockets>
#include <QtWebEngineWidgets>

namespace QOL {

// class ViewPrivate

class ViewPrivate
{
public:
    ViewPrivate(View *q)
        : J_QPTR(q)
        , centerLat(23.5564)
        , centerLon(104.3282)
        , minZoom(5)
        , maxZoom(18)
        , zoom(14)
        , webView(nullptr)
        , webChannel(nullptr)
    {

    }

    ~ViewPrivate()
    {
        Q_Q(View);
        webChannel->deregisterObject(q);
    }

    void init();

private:
    J_DECLARE_PUBLIC(View)
    double centerLat;
    double centerLon;
    int minZoom;
    int maxZoom;
    int zoom;
    QWebEngineView *webView;
    QWebChannel *webChannel;
};

void ViewPrivate::init()
{
    Q_Q(View);
    QHBoxLayout *layoutMain = new QHBoxLayout(q);
    layoutMain->setContentsMargins(0, 0, 0, 0);

    webView = new QWebEngineView(q);
    layoutMain->addWidget(webView);

    webChannel = new QWebChannel(q);
    webChannel->registerObject("qol", QOLMain::instance());
    webChannel->registerObject("qolview", q);

    webView->page()->setWebChannel(webChannel);
    webView->setUrl(QUrl("qrc:/qol/html/index.html"));
}

// class View

View::View(QWidget *parent)
    : QWidget(parent)
    , J_DPTR(new ViewPrivate(this))
{
    Q_D(View);
    d->init();
}


View::~View()
{
    Q_D(View);
    delete d;
}

double View::centerLat() const
{
    Q_D(const View);
    return d->centerLat;
}

double View::centerLon() const
{
    Q_D(const View);
    return d->centerLon;
}

int View::minZoom() const
{
    Q_D(const View);
    return d->minZoom;
}

int View::maxZoom() const
{
    Q_D(const View);
    return d->maxZoom;
}

int View::zoom() const
{
    Q_D(const View);
    return d->zoom;
}

void View::setCenterLat(double value)
{
    Q_D(View);
    if (value != d->centerLat) {
        d->centerLat = value;
        emit centerLatChanged(value);
    }
}

void View::setCenterLon(double value)
{
    Q_D(View);
    if (value != d->centerLat) {
        d->centerLon = value;
        emit centerLonChanged(value);
    }
}

void View::setMinZoom(int value)
{
    Q_D(View);
    if (value != d->minZoom) {
        d->minZoom = value;
        emit minZoomChanged(value);
    }
}

void View::setMaxZoom(int value)
{
    Q_D(View);
    if (value != d->maxZoom) {
        d->maxZoom = value;
        emit maxZoomChanged(value);
    }
}

void View::setZoom(int value)
{
    Q_D(View);
    if (value != d->zoom) {
        d->zoom = value;
        emit zoomChanged(value);
    }
}


}
