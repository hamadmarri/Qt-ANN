#ifndef ANNPAINTER_H
#define ANNPAINTER_H

#include <QtGui>
#include <QQuickPaintedItem>
#include <vector>

class AnnPainter : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(double error WRITE setError)

public:
    explicit AnnPainter(QObject *parent = nullptr);

    void setError(const double e);

signals:

private:
    std::vector<double> _error;

    // QQuickPaintedItem interface
public:
    void paint(QPainter *painter);
};

#endif // ANNPAINTER_H
