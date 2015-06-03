#include <QGuiApplication>
#include <QQuickView>
#include <QQuickItem>
#include <QColor>
#include <QMetaObject>

#include "rtpclient.h"

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    RtpClient client(NULL, 12, 10);

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
            Q_ARG(QVariant, 12), Q_ARG(QVariant, 10));


    return a.exec();
}
