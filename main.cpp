#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <cstdlib>
#include "ann.h"
#include "anntrainer.h"
#include "annpainter.h"

void runANN(int argc, char *argv[]) {
//    ANN ann;
//    AnnTrainer t(ann);
//    int iters = 1000000;

//    if (argc > 1)
//        iters = atoi(argv[1]);

//    t.setIterations(iters);
//    t.train();

    qmlRegisterType<AnnTrainer>("ANN", 1, 0, "ANN");
    qmlRegisterType<AnnPainter>("AnnPainter", 1, 0, "AnnPainter");
}

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    runANN(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
