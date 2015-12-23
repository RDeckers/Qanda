#ifndef ACCOUNTINFO_H
#define ACCOUNTINFO_H

#include <QWidget>
#include <account.h>
using namespace Qanda;
namespace Ui {
class AccountInfo;
}

class AccountInfo : public QWidget
{
  Q_OBJECT

public:
  explicit AccountInfo(QWidget *parent = 0);
  ~AccountInfo();

private:
  Ui::AccountInfo *ui;
public slots:
  void load_account(Account *account);
};

#endif // ACCOUNTINFO_H
