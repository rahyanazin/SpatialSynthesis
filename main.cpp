#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "Controller.h"
#include "Synthesizer.h"
#include "SpatialSound.h"

#include "SignalPlot.h"
#include "SpectrumPlot.h"
#include "TransferFunctionPlot.h"

int main(int argc, char *argv[])
{
    qmlRegisterType<Synthesizer>("Imaginando", 1, 0, "Synthesizer");
    qmlRegisterType<SpatialSound>("Imaginando", 1, 0, "SpatialSound");
    qmlRegisterType<SignalPlot>("Imaginando", 1, 0, "SignalPlot");
    qmlRegisterType<SpectrumPlot>("Imaginando", 1, 0, "SpectrumPlot");
    qmlRegisterType<TransferFunctionPlot>("Imaginando", 1, 0, "TransferFunctionPlot");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    Controller *controller = new Controller(&app);
    engine.rootContext()->setContextProperty("controller", controller);

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
