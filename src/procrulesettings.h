#include <vector>
#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QMessageBox>

#ifndef PROCRULESETTINGS_H
#define PROCRULESETTINGS_H

class Procrule;

class ProcruleSettings : public QMainWindow
{
  Q_OBJECT

public:
  ProcruleSettings(Procrule* parent);

private:
  QComboBox *comboUsage;
  QComboBox *comboAction;
  QLabel *lblArrowRight;

  std::vector<QLabel *> lblsWeekdays;

  QWidget *widgetForbiddenTime;
  QWidget *widgetAllowedTime;

  QPushButton *btnHelpUsage;
  std::vector<QLineEdit *> editsTime;

  QPushButton *btnOk;
  QPushButton *btnCancel;

  Procrule *parentw;
  void insertForbidden(int day);
  void showHelpUsage();
  void loadSettings();
  void writeSettings();
  void writeSettingsAndClose();
};

#endif
