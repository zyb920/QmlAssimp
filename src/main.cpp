#include <QGuiApplication>
#include <QQuickView>
#include <QSurfaceFormat>
#include <QQmlApplicationEngine>
#include "item/FBOItem.h"
#include "model/Model.h"
#include "src/item/Camera.h"
int main(int argc, char *argv[])
{
    qSetMessagePattern("log[%{file} %{function} %{line}] %{message}");

    QGuiApplication a(argc, argv);
#ifndef Q_PROCESSPR_ARM
    //![1] set OpenGL Format
    QSurfaceFormat fmt = QSurfaceFormat::defaultFormat();
    fmt.setVersion(3, 3);
    fmt.setProfile(QSurfaceFormat::CoreProfile);
#ifdef USE_GL_DEBUGGER
    fmt.setOption(QSurfaceFormat::DebugContext);
#endif
    QSurfaceFormat::setDefaultFormat(fmt);
    //![1]
#endif
    qmlRegisterType<FBOItem>("J3D", 1, 0, "FBOItem");
    qmlRegisterType<JCamera>("J3D", 1, 0, "JCamera");
    qmlRegisterType<JKeyCamera>("J3D", 1, 0, "JKeyCamera");
    qmlRegisterType<Model>("J3D", 1, 0, "Model");
    QQuickView view;
    view.setSource(QUrl(QLatin1Literal("qrc:/main.qml")));
    view.setResizeMode(QQuickView::SizeViewToRootObject);
    QObject::connect(view.engine(), &QQmlEngine::quit, &a, &QGuiApplication::quit);
    view.show();
    return a.exec();
}
