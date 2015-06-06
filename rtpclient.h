/* @file rtpclient.h
 * @brief Example to controll the RTPServer
 * @author Ollo
 *
 * @see RTPServer
 *
 * @defgroup RTPServerGui
 */

#ifndef RTPCLIENT_H
#define RTPCLIENT_H


/** @addtogroup RTPServerGui */
/*@{*/


#include <QObject>
#include <QUdpSocket>

class RtpClient : public QObject
{
    Q_OBJECT
public:
    explicit RtpClient(QObject *parent = 0, int width = 0, int height = 0);
    ~RtpClient();

signals:
     void frameUpdated(u_int8_t* frame, int width, int height);

public slots:
     void readyRead(void);

private:
    QUdpSocket *socket;
    int mWidth;
    int mHeight;
    u_int8_t* mFramebuffer;

};

/*@}*/

#endif // RTPCLIENT_H
