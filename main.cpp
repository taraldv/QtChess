#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "board.h"
#include "tcpsockethandler.h"

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

    Board* board = new Board();
    TcpSocketHandler* socket = new TcpSocketHandler();
    QScopedPointer<Board> cppBoard(board);
    QScopedPointer<TcpSocketHandler> cppSocket(socket);
    engine.rootContext()->setContextProperty("cppBoard", cppBoard.data());
    engine.rootContext()->setContextProperty("cppSocket", cppSocket.data());

    engine.load(url);

    return app.exec();
}
