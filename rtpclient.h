#ifndef RTPCLIENT_H
#define RTPCLIENT_H

#include <QObject>
#include <QUdpSocket>

class RtpClient : public QObject
{
    Q_OBJECT
public:
    explicit RtpClient(QObject *parent = 0);

signals:

public slots:
    void readyRead(void);

private: QUdpSocket *socket;

};

#endif // RTPCLIENT_H
