#include <QGuiApplication>
#include <QQuickView>
#include "rtpclient.h"

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    RtpClient client;

    QQuickView view;
    view.setSource( QStringLiteral( "emulator.qml" ) );
    view.show();

    return a.exec();
}
