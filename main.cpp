#include <QGuiApplication>
#include <QQuickView>
#include <QQuickItem>
#include <QColor>

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

    return a.exec();
}
