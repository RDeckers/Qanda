#ifndef QANDA_H
#define QANDA_H

#include <QString>
#include <QtNetwork/QNetworkAccessManager>
#include <QByteArray>

class Qanda : public QNetworkAccessManager
{
  Q_OBJECT
  const QString base_url =  "https://api-fxpractice.oanda.com/v1/";
  QByteArray authorization_header_pair[2];/* = [QByteArray("Authorization"), QByteArray("Bearer ")+
  QByteArray(
      #include "api_key.txt"
      )];*/
public:
  Qanda();
  void get_instrument(QString instrument);
  void login();
  ~Qanda();
public slots:
  void reply_finished(QNetworkReply * reply);
};

#endif // QANDA_H
