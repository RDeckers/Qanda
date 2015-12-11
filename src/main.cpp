#include <QCoreApplication>
#include <interfacer.h>
#include <qblocker.h>
using namespace Qanda;
int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
  Interfacer interfacer(InterfaceType::Practice);
  auto accounts = Account::get_all_accounts(&interfacer);
  for(int i = 0; i < accounts.length(); i++){
    accounts[i].data()->get_details();
    qDebug() << *accounts[i].data();
  }
  Account::request_accounts(&interfacer);

  //interfacer.get_instrument("EUR_SEK");
  //return 0;
  return a.exec();
}
