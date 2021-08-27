#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <cstdlib>
#include "ann.h"
#include "anntrainer.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
//    engine.load(url);



    ANN ann;
    AnnTrainer t(ann);
    int iters = 10000;

    if (argc > 1)
        iters = atoi(argv[1]);

    t.train(iters);

//    return app.exec();
    return 0;
}
