#include <QGuiApplication>
#include <QQuickView>
#include <QQuickItem>
#include <QColor>
#include <QMetaObject>

#include "rtpclient.h"

#define DEFAULT_WIDTH   12
#define DEFAULT_HEIGHT  10

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    RtpClient client(NULL, DEFAULT_WIDTH, DEFAULT_HEIGHT);

    QQuickView view;
    view.setSource( QUrl("qrc:/layout/emulator.qml") );
    view.show();
    QQuickItem *rgb1 = view.rootObject()->findChild<QQuickItem*>("rgb1Obj");
    if (rgb1) {
        rgb1->setProperty("color", QColor("#00FF00"));
        qDebug() << "Set the color from th Appl.";
    }

    QVariant returnedValue;
    QMetaObject::invokeMethod(view.rootObject(), "setGUIWidthAndHeight",
            Q_RETURN_ARG(QVariant, returnedValue),
            Q_ARG(QVariant, DEFAULT_WIDTH), Q_ARG(QVariant, DEFAULT_HEIGHT));


    return a.exec();
}
