#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "Model.h"
#include "loader.h"
#include <iostream>

void usage(const std::string& exe)
{
    //TODO extend Usage
    //FIXME: Why is it read
    std::cout << "Usage: " << exe << " <json_file>" << std::endl;
}
int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        usage(argv[0]);
        return -1;
    }

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    Data data;
    Model photos(nullptr, &data, 15);
    Loader loader;

    QObject::connect(&loader, &Loader::success, &photos, &Model::setLoaded);

    if (!data.read(argv[1]))
    {
        std::cout << "Unable to load input file <" << argv[1] << ">" << std::endl;
        usage(argv[0]);
        return -1;
    }


    emit loader.operate(data);

    engine.rootContext()->setContextProperty("photos", &photos);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    //TODO Add detail photo viewer

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
