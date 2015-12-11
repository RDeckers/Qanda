#ifndef QBLOCKER_H
#define QBLOCKER_H

#include <QObject>
#include <QEventLoop>

//TODO: make thread safe.
class QBlocker : public QEventLoop
{
  Q_OBJECT
  bool clean = true;
public:
  QBlocker(){};
  ~QBlocker(){};
  void make_clean(){clean = true;}
  bool is_clean(){return clean;}
  void exec(){
    if(clean){
      clean = false;
      this->QEventLoop::exec();
      clean = true;
    }
  }
public slots:
  void exit(int status){
    clean = false;
    QEventLoop::exit(status);
  }
  void quit(){exit(0);}
};

#endif // QBLOCKER_H
