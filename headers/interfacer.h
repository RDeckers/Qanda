#ifndef QANDA_H
#define QANDA_H

#include <account.h>
#include <QString>
#include <QtNetwork/QNetworkAccessManager>
#include <qmarkedreply.h>
#include <QByteArray>


namespace Qanda{
class QMarkedReply;

enum InterfaceType{
  Sandbox = 0,
  Practice = 1,
  Trade = 2
};

class Interfacer : public QNetworkAccessManager
{
  Q_OBJECT
  QByteArray authorization_header_pair[2];
  void initialize_base_url(InterfaceType interface_type);
  QString base_url;
public:
  Interfacer(InterfaceType interface_type = Practice);
  ~Interfacer();
  QMarkedReply* make_new_request(QString path, bool use_authorization = true);
  void get_instrument(QString instrument);

  //QList<Account> get_detailed_accounts();

private slots:

signals:
  void recieved_accounts(AccountList accounts);
};
}
#endif // QANDA_H
