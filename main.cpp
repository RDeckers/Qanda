#include <QCoreApplication>
#include "qanda.h"

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
  Qanda qanda;
  //qanda.login();
  qanda.get_instrument("EUR_SEK");
  return a.exec();
}
