#include <instrument.h>
#include <QJsonObject>
#include <QDebug>

namespace Qanda{
Instrument::Instrument(Interfacer *interface, QJsonObject json){
  this->interface = interface;
  this->instrument = json["instrument"].toString();

}

Instrument::~Instrument(){

}
}
