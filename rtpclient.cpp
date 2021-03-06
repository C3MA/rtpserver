#include "rtpclient.h"
#include "rtp.h"
#include "rtpparser.h"

RtpClient::RtpClient(QObject *parent) :
    QObject(parent)
{
    // create a QUDP socket
    socket = new QUdpSocket(this);

    socket->bind(QHostAddress::LocalHost, 5000);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void RtpClient::readyRead(void)
{
    // when data comes in
    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());
    QHostAddress sender;
    quint16 senderPort;
    // qint64 QUdpSocket::readDatagram(char * data, qint64 maxSize,
    // QHostAddress * address = 0, quint16 * port = 0)
    // Receives a datagram no larger than maxSize bytes and stores it in data.
    // The sender's host address and port is stored in *address and *port
    // (unless the pointers are 0).
    quint64 len = socket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);

    char* pkt = buffer.data();



    qDebug() << "Message from: " << sender.toString();
    qDebug() << "Message port: " << senderPort;

    u_int8_t fb[12 * 10 *3];
    decode_packet((uint8_t*) pkt, len, fb, 12, 10);

}
