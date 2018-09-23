#include "procrule.h"
#include "mainwindow.h"
#include <iostream>

Procrule::Procrule(QWidget *parent) :
  QWidget(parent),
  layout(new QHBoxLayout),
  comboTriggerType(new QComboBox),
  editTriggerText(new QLineEdit),
  buttonSettings(new QPushButton("-> Action")),
  buttonDelete(new QPushButton("X"))
{
  usageType = "Allowed";
  actionType = "Warning";
  for(unsigned i=0; i<7; i++)
    times.push_back("00:00");

  comboTriggerType->addItem("Website");
  comboTriggerType->addItem("Program");

  connect(buttonDelete, QPushButton::clicked, this,
	  [this]{
	    this->setParent(0);
	  });
  connect(buttonSettings, QPushButton::clicked, this, Procrule::openSettings);

  layout->addWidget(comboTriggerType);
  layout->addWidget(editTriggerText);
  layout->addWidget(buttonSettings);
  layout->addWidget(buttonDelete);
  setLayout(layout);
}

void Procrule::openSettings(){
  settings = new ProcruleSettings(this);
  settings->show();
  std::cout << "Settings opened";
}




QString Procrule::getTriggerType()
{
  return comboTriggerType->currentText();
}
void Procrule::setTriggerType(QString triggerType)
{
  if(comboTriggerType->findText(triggerType) != -1){
    comboTriggerType->setCurrentIndex(comboTriggerType->findText(triggerType));
  } else {
    QMessageBox::critical(this,"Internal Program Error",
			  "Couldn't set the Type of RuleTrigger in the ComboBox",
			  QMessageBox::Ok);
    return;
  }
}
QString Procrule::getTriggerText()
{
  return editTriggerText->text();
}
void Procrule::setTriggerText(QString triggerText)
{
  editTriggerText->setText(triggerText);
}
QString Procrule::getUsageType()
{
  return usageType;
}
void Procrule::setUsageType(QString type)
{
  usageType = type;
}
QString Procrule::getActionType()
{
  return actionType;
}
void Procrule::setActionType(QString type)
{
  actionType = type;
}
std::vector<QString> Procrule::getTimes()
{
  return times;
}
void Procrule::setTimes(std::vector<QString> times)
{
  this->times = times;
}
ProcruleSettings *Procrule::getSettings(){
  return settings;
}
