#ifndef RTPCLIENT_H
#define RTPCLIENT_H

#include <QObject>
#include <QUdpSocket>

class RtpClient : public QObject
{
    Q_OBJECT
public:
    explicit RtpClient(QObject *parent = 0, int width = 0, int height = 0);

signals:

public slots:
    void readyRead(void);

private:
    QUdpSocket *socket;
    int mWidth;
    int mHeight;

};

#endif // RTPCLIENT_H
