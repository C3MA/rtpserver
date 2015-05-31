#include <QCoreApplication>
#include "rtpclient.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    RtpClient client;



    return a.exec();
}
