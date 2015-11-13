#include "qanda.h"
#include <QUrl>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

Qanda::Qanda()
{
  connect(this, SIGNAL(finished(QNetworkReply*)), this, SLOT(reply_finished(QNetworkReply*)));
  authorization_header_pair[0] = QByteArray("Authorization");
  authorization_header_pair[1] = QByteArray("Bearer ")+QByteArray(
      #include "api_key.txt" //this should be a file containing a quoted string
      );
}

Qanda::~Qanda()
{

}

void Qanda::login(){
  QUrl url = QUrl(this->base_url+QString("accounts"));
  QNetworkRequest request(url);
  request.setRawHeader(authorization_header_pair[0], authorization_header_pair[1]);
  qDebug() << "requesting url:" << url;
  qDebug() << "With headers:" << request.rawHeaderList();
  qDebug() << "an value:" << request.rawHeader("Authorization");
  this->get(request);
}

void Qanda::get_instrument(QString instrument){
  QUrl url = QUrl(this->base_url+QString("candles?count=1&instrument=")+instrument);
  QNetworkRequest request(url);
  request.setRawHeader(authorization_header_pair[0], authorization_header_pair[1]);
  this->get(request);
}

void Qanda::reply_finished(QNetworkReply *reply){
  QByteArray data = reply->readAll();
  qDebug() << "Data size:" << data.size();
  QJsonObject json = QJsonDocument::fromJson(data).object();
  qDebug() << json;
}
