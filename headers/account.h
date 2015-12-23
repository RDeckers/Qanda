#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <QObject>
#include <QNetworkReply>
#include <QJsonObject>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QSharedPointer>

#include <instrument.h>

namespace Qanda{
class Interfacer;
class Account;

//typedef AccountList ;
typedef QList<QSharedPointer<Account>> AccountList;

class Account : public QObject{
  Q_OBJECT
  Interfacer *interface; //possibly guard witha  shared pointer.
  //Always(?) returned by Oanda
  QString name;
  QString currency;
  quint64 id;
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
  void wait_for_reply(QNetworkReply* reply);
  InstrumentList process_instruments(QNetworkReply *reply);
  void process_details(QNetworkReply *reply);
  static AccountList process_accounts(QNetworkReply *reply, Interfacer *interface);
public:
  //Account(Interfacer  *parent_interface, QJsonObject json);
  //Account(QJsonObject);
  ~Account();
  size_t get_id(){return this->id;}
  QString get_name(){return this->name;}
  double get_balance(){return this->balance;}

  void request_instruments();
  InstrumentList get_instruments();

  void request_details();
  void get_details();

  static AccountList get_all_accounts(Interfacer *interface);
  static void request_accounts(Interfacer *interface);
signals:
  void new_details(Account *account);
  void recieved_accounts(AccountList accounts);
  void recieved_instruments(InstrumentList instruments);
  //static QList<Account> get_all_accounts_detailed(Interfacer *interface);

  friend std::ostream& operator<< (std::ostream& stream, const Account& account);
  friend QDebug operator<< (QDebug stream, const Account& account);
};
}

#endif // ACCOUNT_H
