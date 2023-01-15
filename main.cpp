#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "gamefield.h"
#include "game.h"
#include "CellState.h"

int main(int argc, char *argv[])
{

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    qmlRegisterType<Game>("Game", 1, 0, "Game");
    qmlRegisterType<GameField>("gamefield", 1, 0, "GameFieldModel");
    qmlRegisterUncreatableMetaObject(
                 CellState::staticMetaObject,
                 "cell.state",
                 1, 0,
                 "CellState",
                 "Error: only enums"
    );

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

