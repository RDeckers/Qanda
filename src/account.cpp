#include <account.h>
#include <iostream>
#include <interfacer.h>

#include <QJsonDocument>
#include <QJsonArray>

#include <qblocker.h>

/*Account::get_all_accounts(Interfacer *interface){
  interface->request_accounts();
}*/
namespace Qanda{
Account::Account(Interfacer *parent, QJsonObject json){
  this->interface = parent;
  this->name = json["accountName"].toString();
  this->currency = json["accountCurrency"].toString();
  this->id = json.value("accountId").toVariant().toULongLong();
  this->margin_rate = json["marginRate"].toDouble();
}

Account::~Account(){
}

void Account::wait_for_reply(QNetworkReply *reply){
  QBlocker block;
  connect(reply, &QNetworkReply::finished, &block, &QBlocker::quit);
  block.exec();
}

InstrumentList Account::get_instruments(){
  auto reply = interface->make_new_request(QString("instruments?accountId=%1").arg(this->id))->reply();
  /*QBlocker block;
  connect(reply, &QMarkedReply::finished, &block, &QBlocker::quit);
  block.exec();*/
  wait_for_reply(reply);
  return process_instruments(reply);
}

void Account::request_instruments(){
  auto reply = interface->make_new_request(QString("instruments?accountId=%1").arg(this->id));
  connect(reply, &QMarkedReply::finished, this, &Account::process_instruments);
}

InstrumentList Account::process_instruments(QNetworkReply *reply){
  auto data = reply->readAll();
  QJsonArray json_array = QJsonDocument::fromJson(data).object()["instruments"].toArray();
  InstrumentList instrument_list;
  for(int i = 0; i < json_array.size();i++){
    auto object = json_array[i].toObject();
    QSharedPointer<Instrument> p(new Instrument(interface, object));
    instrument_list.append(p);
  }
  delete reply;
  emit recieved_instruments(instrument_list);
  return instrument_list;
}

void Account::get_details(){
  auto reply = interface->make_new_request(QString("accounts/%1").arg(this->id))->reply();
  wait_for_reply(reply);
  process_details(reply);
}

void Account::request_details(){
  auto reply = interface->make_new_request(QString("accounts/%1").arg(this->id));
  connect(reply, &QMarkedReply::finished, this, &Account::process_details);
}

void Account::process_details(QNetworkReply *reply){
  QJsonObject json = QJsonDocument::fromJson(reply->readAll()).object();
  this->balance = json["balance"].toDouble();
  this->unrealized_pl = json["unrealizedPl"].toDouble();
  this->realized_pl = json["realizedPl"].toDouble();
  this->margin_used = json["marginUsed"].toDouble();
  this->margin_availible = json["marginAvail"].toDouble();
  this->open_orders = json["openTrades"].toInt();
  this->open_trades = json["openOrders"].toInt();
  this->detailed = true;
  emit new_details(this);
}

void Account::request_accounts(Interfacer *interface){
  auto reply = interface->make_new_request("accounts");
  connect(reply, &QMarkedReply::finished,  [=]{
    &Account::process_accounts(reply->reply(), interface);
  });
}

AccountList Account::get_all_accounts(Interfacer *interface){
  //interface.request_all_accounts;
  auto reply = interface->make_new_request("accounts");
  QBlocker block;
  connect(reply, &QMarkedReply::finished, &block, &QBlocker::quit);
  block.exec();
  return process_accounts(reply->reply(), interface);
}

AccountList Account::process_accounts(QNetworkReply *reply, Interfacer *interface){
  QJsonObject base_object = QJsonDocument::fromJson(reply->readAll()).object();
  QJsonArray account_object_list = base_object["accounts"].toArray();
  AccountList account_list;
  for(int i = 0; i < account_object_list.size(); i++){
    //QSharedPointer<Account> p(new Account(interface, account_object_list[i].toObject()));
    QSharedPointer<Account> a(new Account(interface, account_object_list[i].toObject()));
    account_list.append(a);
  }
  delete reply;
  emit interface->recieved_accounts(account_list);
  return account_list;
}

std::ostream& operator<<(std::ostream& ost, const Account& account){
  ost << "{Name: " << account.name.toStdString() << ", ";
  ost << "Currency: " << account.currency.toStdString() << ", ";
  ost << "Id: " << account.id << ", ";
  ost << "Margin " << account.margin_rate;

  if(account.detailed){
    ost  << ", balance: " << account.balance << ", ";
    ost  << "unrealized pl: " << account.unrealized_pl << ", ";
    ost  << "realized pl: " << account.realized_pl << ", ";
    ost  << "margin used: " << account.margin_used << ", ";
    ost  << "margin availible: " << account.margin_availible << ", ";
    ost  << "open orders: " << account.open_orders << ", ";
    ost  << "open trades: : " << account.open_trades;
  }
  ost << "}";
  return ost;
}

QDebug operator<<(QDebug  ost, const Account& account){
  ost << "{Name: " << account.name << ", ";
  ost << "Currency: " << account.currency << ", ";
  ost << "Id: " << account.id << ", ";
  ost << "Margin: " << account.margin_rate;

  if(account.detailed){
    ost  << ", balance: " << account.balance << ", ";
    ost  << "unrealized pl: " << account.unrealized_pl << ", ";
    ost  << "realized pl: " << account.realized_pl << ", ";
    ost  << "margin used: " << account.margin_used << ", ";
    ost  << "margin availible: " << account.margin_availible << ", ";
    ost  << "open orders: " << account.open_orders << ", ";
    ost  << "open trades: : " << account.open_trades;
  }
  ost << "}";
  return ost;
}
}
