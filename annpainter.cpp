#include "annpainter.h"
#include <QDebug>

AnnPainter::AnnPainter(QObject *parent)
    : QQuickPaintedItem()
{
}

void AnnPainter::setError(const double e)
{
    this->_error.push_back(e);
    this->update();
}

void AnnPainter::paint(QPainter *painter)
{
    QColor c(Qt::GlobalColor::red);
    QColor cb(Qt::GlobalColor::black);
    QPen p(c);
    QPen pb(cb);

//    p.setWidth(1);
    painter->setPen(p);
    painter->setRenderHints(QPainter::Antialiasing, true);

    for (int i = 1; i < this->_error.size(); ++i) {
        double pe = this->_error[i - 1];
        double e = this->_error[i];
        int px = (i - 1) * 2;
        int x = i * 2;

        pe = 1 - pe;
        pe *= 400;

        e = 1 - e;
        e *= 400;

        painter->drawLine(px, pe, x, e);
    }

    painter->setPen(pb);
    painter->drawLine(0, 400, 5000, 400);
}
