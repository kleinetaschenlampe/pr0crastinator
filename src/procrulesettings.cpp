#include "procrulesettings.h"
#include "procrule.h"

ProcruleSettings::ProcruleSettings(Procrule *parent) :
  QMainWindow(parent),
  comboUsage(new QComboBox(this)),
  comboAction(new QComboBox(this)),
  lblArrowRight(new QLabel("⟶", this)),
  widgetForbiddenTime(new QWidget(this)),
  widgetAllowedTime(new QWidget(this)),
  btnHelpUsage(new QPushButton(this)),
  btnOk(new QPushButton(this)),
  btnCancel(new QPushButton(this))
{
  lblsWeekdays.push_back(new QLabel(tr("Monday"), this));
  lblsWeekdays.push_back(new QLabel(tr("Tuesday"), this));
  lblsWeekdays.push_back(new QLabel(tr("Wednesday"), this));
  lblsWeekdays.push_back(new QLabel(tr("Thursday"), this));
  lblsWeekdays.push_back(new QLabel(tr("Friday"), this));
  lblsWeekdays.push_back(new QLabel(tr("Saturday"), this));
  lblsWeekdays.push_back(new QLabel(tr("Sunday"), this));

  parentw = parent;

  for(unsigned int i=0; i<7; i++){
    editsTime.push_back(new QLineEdit(this));
  }
  
  comboUsage->move(20,20);
  comboUsage->resize(100,20);
  comboUsage->addItem(tr("Allowed"));
  comboUsage->addItem(tr("Forbidden"));

  btnHelpUsage->setText("?");
  btnHelpUsage->resize(20,20);
  btnHelpUsage->move(125,20);
  connect(btnHelpUsage, QPushButton::clicked, this, ProcruleSettings::showHelpUsage);

  lblArrowRight->setPixmap(QPixmap("resources/arrow-right.png"));
  lblArrowRight->setScaledContents(true);
  lblArrowRight->move(280,15);
  lblArrowRight->resize(100,30);

  comboAction->move(430,20);
  comboAction->resize(100,20);
  comboAction->addItem(tr("Warning"));
  comboAction->addItem(tr("Stop Automatically"));

  for(unsigned int i=0; i<7; i++){
    lblsWeekdays[i]->resize(100,30);
    lblsWeekdays[i]->move(20,i*30+50);

    editsTime[i]->resize(150,20);
    editsTime[i]->move(100,i*30+57);
  }

  btnOk->setText("Ok");
  btnOk->resize(70,20);
  btnOk->move(430,270);
  connect(btnOk, QPushButton::clicked, this, ProcruleSettings::writeSettingsAndClose);
  btnCancel->setText("Cancel");
  btnCancel->resize(70,20);
  btnCancel->move(510,270);
  connect(btnCancel, QPushButton::clicked, this, close);

  setFixedSize(600,300);
  loadSettings();
  setWindowTitle("Edit Rule");
  
  show();
}

void ProcruleSettings::loadSettings()
{
  auto usageType = parentw->getUsageType();
  auto actionType = parentw->getActionType();
  auto times = parentw->getTimes();

  comboUsage->setCurrentIndex(comboUsage->findText(usageType));
  comboAction->setCurrentIndex(comboAction->findText(actionType));

  for(unsigned i=0; i<7; i++)
    editsTime[i]->setText(times[i]);
}

void ProcruleSettings::writeSettings()
{
  auto usageType = comboUsage->currentText();
  auto actionType = comboAction->currentText();
  std::vector<QString> times;
  for(unsigned i=0; i<7; i++)
    times.push_back(editsTime[i]->text());

  parentw->setUsageType(usageType);
  parentw->setActionType(actionType);
  parentw->setTimes(times);
}

void ProcruleSettings::writeSettingsAndClose(){
  writeSettings();
  close();
}

void ProcruleSettings::showHelpUsage()
{
  if(comboUsage->currentText() == "Allowed"){
    QMessageBox::information(this,"Allowed time",
			     "You can define a period of time that the trigger "
			     "should be allowed on a per day basis here. \n"
			     "Syntax is:\t hh:mm \n"
			     "ForExample:\t 2:00 \n"
			     "\t\t -> 2h are allowed on that day",
			     QMessageBox::Ok);
  } else if(comboUsage->currentText() == "Forbidden") {
    QMessageBox::information(this,"Forbidden time",
			     "You can define multiple periods of time that the trigger "
			     "should be forbidden on a per day basis here. \n"
			     "Syntax is:\t hh:mm-hh:mm, hh:mm-hh:mm, ... \n"
			     "ForExample:\t 7:30-8:30, 10:00-18:00 \n"
			     "\t\t -> Usage is forbidden from 7:30 to 8:30 and from "
			     "10:00 to 18:00",
			     QMessageBox::Ok);
  }
}
