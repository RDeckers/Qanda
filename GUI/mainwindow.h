#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <interfacer.h>
#include <account.h>
using namespace Qanda;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT
  Interfacer interface;
  AccountList accounts;
public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void on_account_selector_activated(int index);

private:
  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
