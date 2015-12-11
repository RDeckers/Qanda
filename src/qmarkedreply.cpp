#include <qmarkedreply.h>
namespace Qanda{
QMarkedReply::QMarkedReply(QNetworkReply *reply)
{
  this->rep = reply;
  connect(reply, &QNetworkReply::finished, this, &QMarkedReply::finished_handoff);
}

QMarkedReply::~QMarkedReply()
{

}
}
