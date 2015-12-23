#include "accountinfo.h"
#include "ui_accountinfo.h"

AccountInfo::AccountInfo(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::AccountInfo)
{
  ui->setupUi(this);
}

AccountInfo::~AccountInfo()
{
  delete ui;
}

void AccountInfo::load_account(Account *account){
  account->get_details();
  ui->balance->setText(QString::number(account->get_balance(),'f', 3));
}
