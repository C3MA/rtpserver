#ifndef RTPCLIENT_H
#define RTPCLIENT_H

#include <QObject>
#include <QUdpSocket>

class RtpClient : public QObject
{
    Q_OBJECT
    Q_PROPERTY(NOTIFY frameUpdated)
public:
    explicit RtpClient(QObject *parent = 0, int width = 0, int height = 0);
    ~RtpClient();

signals:
    void frameUpdated(u_int8_t* data);

public slots:
    void readyRead(void);

private:
    QUdpSocket *socket;
    int mWidth;
    int mHeight;
    u_int8_t* mFramebuffer;

};

#endif // RTPCLIENT_H
