#include <interfacer.h>
#include <QUrl>
#include <QtNetwork/QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <qblocker.h>

namespace Qanda{
Interfacer::Interfacer(InterfaceType interface_type){
  this->initialize_base_url(interface_type);
  //If not using the sandbox, create an authorization header
  if(InterfaceType::Sandbox != interface_type){
    authorization_header_pair[0] = QByteArray("Authorization");
    authorization_header_pair[1] = QByteArray("Bearer ")
        +QByteArray(
        #include "../resources/api_key.txt" //this should be a file containing a quoted string
          );
  }
}

Interfacer::~Interfacer(){
}

void Interfacer::initialize_base_url(InterfaceType interface_type){
  switch(interface_type){
  case InterfaceType::Practice:
    this->base_url = QString("https://api-fxpractice.oanda.com/v1/");
    break;
  case InterfaceType::Trade:
    this->base_url = QString("https://api-fxtrade.oanda.com/v1/");
    break;
  default:
    this->base_url  = QString("http://api-sandbox.oanda.com/v1/");
    break;
  }
}

QMarkedReply* Interfacer::make_new_request(QString path, bool use_authorization){
  QUrl url = QUrl(this->base_url+path);
  QNetworkRequest request(url);
  if(use_authorization)
    request.setRawHeader(authorization_header_pair[0], authorization_header_pair[1]);
  return new QMarkedReply(this->get(request));
}

void Interfacer::get_instrument(QString instrument){
  QUrl url = QUrl(this->base_url+QString("candles?count=1&instrument=")+instrument);
  QNetworkRequest request(url);
  request.setRawHeader(authorization_header_pair[0], authorization_header_pair[1]);
  this->get(request);
}
}
