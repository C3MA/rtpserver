#include "rtpclient.h"
#include "rtp.h"
#include "rtpparser.h"

RtpClient::RtpClient(QObject *parent, int width, int height) :
    QObject(parent)
{
    // create a QUDP socket
    socket = new QUdpSocket(this);

    // Store the module attributes
    mWidth = width;
    mHeight = height;

    mFramebuffer = (u_int8_t *) malloc(RGB_SIZE * mWidth * mHeight);

    qDebug() << "Using Screen of  " << mWidth << "x" << mHeight << " pixel";

    socket->bind(QHostAddress::LocalHost, 5000);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

RtpClient::~RtpClient()
{
    free(mFramebuffer);
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

    decode_packet((uint8_t*) pkt, len, mFramebuffer, mWidth, mHeight);
    emit frameUpdated(mFramebuffer, mWidth, mHeight);
}
