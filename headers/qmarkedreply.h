#ifndef MARKEDREPLY_H
#define MARKEDREPLY_H
#include <interfacer.h>
#include <QNetworkReply>

/*NOTES:
 * It might be nicer, from a design stand-point, to inherit from QNetworkReply. However this is a virtual class which
 * seems to instantiate itself to the correct type based on invocation. This works as well and is much easier to implement and will
 * work for any type of network reply.
 * */
namespace Qanda{
class QMarkedReply : public QObject
{
  Q_OBJECT
  QNetworkReply* rep = nullptr;
private slots:
  void finished_handoff(){emit finished(rep);}
public:
  QNetworkReply* reply(){return this->rep;}
  QMarkedReply(QNetworkReply *reply);
  ~QMarkedReply();
signals:
  void finished(QNetworkReply*);
};
}
#endif // MARKEDREPLY_H
