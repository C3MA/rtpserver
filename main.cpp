#include <QGuiApplication>
#include <QQuickView>
#include <QQuickItem>
#include <QColor>
#include <QMetaObject>
#include <QQmlContext>
#include <rgb2qcolorconverter.h>

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

    /* Set the inital screen dimensions */
    QVariant returnedValue;
    QMetaObject::invokeMethod(view.rootObject(), "setGUIWidthAndHeight",
            Q_RETURN_ARG(QVariant, returnedValue),
            Q_ARG(QVariant, DEFAULT_WIDTH), Q_ARG(QVariant, DEFAULT_HEIGHT));

    /* Connect the background (receiving part) to the GUI */
    RGB2QColorConverter converter(NULL, view.rootObject());
    QObject::connect(&client, SIGNAL(frameUpdated(u_int8_t* ,int, int)),
                         &converter, SLOT(newFrame(u_int8_t* ,int, int)));



    return a.exec();
}
