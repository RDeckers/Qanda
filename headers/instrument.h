#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <QVector>
#include <QString>
#include <QSharedPointer>
#include <cstdint>

namespace Qanda{
class Instrument;
class Interfacer;

typedef QList<QSharedPointer<Instrument>> InstrumentList ;

enum InstrumentProperties{
  DisplayName = (1 << 0),
  Pip = (1 << 1),
  MaxTradeUnites = (1 << 2),
  Precision = (1 << 3),
  MaxTrailingStop = (1 << 4),
  MinTrailingStop = (1 << 5),
  MarginRate = (1 << 6),
  Halted  = (1 << 7),
  InterestRate = (1 << 8),
  ALL = 0xFFFFFFFF //32 bits.
};

typedef struct{//currently only bid/ask supported.
    uint64_t timestamp; //and unix timestamps.
    uint64_t volume;
    bool completed;
    double closeAsk, closeBid, highAsk, highBid, lowAsk, lowBid, openAsk, openBid;
}InstrumentTick_t;

class Instrument
{
  Interfacer *interface;
  QString instrument;
  QString displayName;
  double pip;
  uint64_t  max_trade_units;
  double precision; //double?
  uint64_t max_trailing_stop;
  uint64_t min_trailing_stop;
  double margin_rate;
  bool halted;
  double interest_rate;
  QVector<Qanda::InstrumentTick_t> ticks;
public:
  Instrument(Interfacer *interface, QJsonObject json);
  //Instrument(QString name);
  ~Instrument();
};
}
#endif // INSTRUMENT_H
