#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <QObject>
#include <QNetworkReply>
#include <QJsonObject>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QSharedPointer>

namespace Qanda{
class Interfacer;
class Account;

typedef QList<QSharedPointer<Account>> AccountList ;
//typedef QScopedArrayPointer<Account> AccountList;

class Account : public QObject{
  Q_OBJECT
  Interfacer *interface; //possibly guard witha  shared pointer.
  //Always(?) returned by Oanda
  QString name;
  QString currency;
  size_t id;
  double margin_rate;
  //Require an extra query
  double balance;
  double unrealized_pl;
  double realized_pl;
  double margin_used;
  double margin_availible;
  int open_orders; //unsigned? double?
  int open_trades;
  bool detailed = false;

  Account(Interfacer  *parent_interface, QJsonObject json);
  void proccess_details(QNetworkReply *reply);
  static AccountList proccess_accounts(QNetworkReply *reply, Interfacer *interface);
public:
  //Account(Interfacer  *parent_interface, QJsonObject json);
  //Account(QJsonObject);
  ~Account();
  size_t get_id(){return this->id;}

  void request_details();


  void get_details();

  static AccountList get_all_accounts(Interfacer *interface);
  static void request_accounts(Interfacer *interface);
signals:
  void new_details(Account *account);
  void recieved_accounts(AccountList accounts);
  //static QList<Account> get_all_accounts_detailed(Interfacer *interface);

  friend std::ostream& operator<< (std::ostream& stream, const Account& account);
  friend QDebug operator<< (QDebug stream, const Account& account);
};
}

#endif // ACCOUNT_H
