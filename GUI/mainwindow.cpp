#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  accounts = Account::get_all_accounts(&interface);
  for(int i = 0; i < accounts.length(); i++){
    ui->account_selector->addItem(accounts[i]->get_name());
  }
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_account_selector_activated(int index)
{
    ui->account_info->load_account(accounts[index].operator ->());
}
