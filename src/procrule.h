#include "procrulesettings.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>

#ifndef PROCRULE_H
#define PROCRULE_H

class Procrule : public QWidget
{
  Q_OBJECT

public:
  Procrule(QWidget *parent = 0);

  // getters & setters
  QString getTriggerType();
  QString getTriggerText();
  void setTriggerType(QString triggerType);
  void setTriggerText(QString triggerText);

  void openSettings();
  ProcruleSettings *settings;
  ProcruleSettings *getSettings();

  QString getUsageType();
  void setUsageType(QString type);
  QString getActionType();
  void setActionType(QString type);
  std::vector<QString> getTimes();
  void setTimes(std::vector<QString> times);

private:
  QString triggerType;
  QString triggerText;

  QHBoxLayout *layout;
  QComboBox *comboTriggerType;
  QLineEdit *editTriggerText;
  QPushButton *buttonSettings;
  QPushButton *buttonDelete;

  QString usageType;
  QString actionType;
  // weekday - timespans
  std::vector<QString> times;
};

#endif
