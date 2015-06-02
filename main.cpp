#include <QCoreApplication>
#include "rtpclient.h"

#include <QQuickView>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    RtpClient client;

    QQuickView view;
    view.setSource( QStringLiteral( "emulator.qml" ) );
    view.show();

    return a.exec();
}
