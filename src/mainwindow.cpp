#include "mainwindow.h"
#include <iostream>
#include <QGroupBox>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QDir>
#include <QFile>
#include <QXmlStreamWriter>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  modified(false),
  mainLayout(new QVBoxLayout),
  mainWidget(new QWidget),
  mainScrollArea(new QScrollArea)
{
  createActions();
  createMenus();
  resize(700,400);

  mainScrollArea->setWidget(mainWidget);
  mainScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  mainScrollArea->setWidgetResizable(true);
  setCentralWidget(mainScrollArea);
  mainWidget->setLayout(mainLayout);
  setWindowTitle("pr0crastinator");
  loadRules();
}

Procrule *MainWindow::addEmptyRule()
{
  Procrule *rule = new Procrule(this);
  mainLayout->addWidget(rule);
  return rule;
}

Procrule *MainWindow::addRule(QString triggerType, QString triggerText,
			      QString usageType, QString actionType,
			      std::vector<QString> times)
{
  Procrule *rule = addEmptyRule();
  rule->setTriggerType(triggerType);
  rule->setTriggerText(triggerText);
  rule->setUsageType(usageType);
  rule->setActionType(actionType);
  rule->setTimes(times);
  return rule;
}

void MainWindow::loadRules()
{
  QFile file("C:/Users/fp/AppData/Local/pr0crastrinator/rules.xml");
  // TODO error handling
  file.open(QIODevice::ReadOnly);
  QXmlStreamReader reader(&file);
  while(!reader.atEnd() && !reader.hasError()){
    if(reader.readNext() == QXmlStreamReader::StartElement && reader.name() == "rule"){
      QString type;
      QString text;
      QString usageType;
      QString actionType;
      std::vector<QString> times;

      while(!(reader.readNext() == QXmlStreamReader::EndElement)){
	if(reader.name() == "type")
	  type = reader.readElementText();
	if(reader.name() == "text")
	  text = reader.readElementText();
	if(reader.name() == "usageType")
	  usageType = reader.readElementText();
	if(reader.name() == "actionType")
	  actionType = reader.readElementText();
	if(reader.name() == "timeMonday")
	  times.push_back(reader.readElementText());
	if(reader.name() == "timeTuesday")
	  times.push_back(reader.readElementText());
	if(reader.name() == "timeWednesday")
	  times.push_back(reader.readElementText());
	if(reader.name() == "timeThursday")
	  times.push_back(reader.readElementText());
	if(reader.name() == "timeFriday")
	  times.push_back(reader.readElementText());
	if(reader.name() == "timeSaturday")
	  times.push_back(reader.readElementText());
	if(reader.name() == "timeSunday")
	  times.push_back(reader.readElementText());
      }

      addRule(type, text, usageType, actionType, times);
    }
  }

  file.close();
}

void MainWindow::saveRules()
{
  // Create config dir if it doesnt exist
  QDir dir("C:/Users/fp/AppData/Local/pr0crastrinator");
  if (!dir.exists()) {
    dir.mkdir(".");
  }

  // Write to the file
  QFile::remove("C:/Users/fp/AppData/Local/pr0crastrinator/rules.xml");
  QFile file("C:/Users/fp/AppData/Local/pr0crastrinator/rules.xml");
  // TODO error handling
  file.open(QIODevice::ReadWrite);
  QXmlStreamWriter xmlWriter(&file);
  xmlWriter.setAutoFormatting(true);
  xmlWriter.writeStartDocument();
  xmlWriter.writeStartElement("rules");

  QList<Procrule *> currentRules =
    mainWidget->findChildren<Procrule *>(QString(), Qt::FindDirectChildrenOnly);
  for(int i = 0; i != currentRules.size(); i++){
    auto type = currentRules[i]->findChild<QComboBox *>()->currentText();
    auto text = currentRules[i]->findChild<QLineEdit *>()->text();
    auto usageType = currentRules[i]->getUsageType();
    auto actionType = currentRules[i]->getActionType();
    auto times = currentRules[i]->getTimes();

    xmlWriter.writeStartElement("rule");
    xmlWriter.writeTextElement("type",type);
    xmlWriter.writeTextElement("text",text);
    xmlWriter.writeTextElement("usageType",usageType);
    xmlWriter.writeTextElement("actionType",actionType);
    xmlWriter.writeTextElement("timeMonday",times[0]);
    xmlWriter.writeTextElement("timeTuesday",times[1]);
    xmlWriter.writeTextElement("timeWednesday",times[2]);
    xmlWriter.writeTextElement("timeThursday",times[3]);
    xmlWriter.writeTextElement("timeFriday",times[4]);
    xmlWriter.writeTextElement("timeSaturday",times[5]);
    xmlWriter.writeTextElement("timeSunday",times[6]);
    xmlWriter.writeEndElement();
  }

  xmlWriter.writeEndElement();
  file.close();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
  if(modified == false){
    close();
  }else{
    QMessageBox msgBox;
    msgBox.setText("You have unsaved changes");
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();

    switch (ret) {
    case QMessageBox::Save:
      saveRules();
      event->accept();
      break;
    case QMessageBox::Discard:
      event->accept();
      break;
    case QMessageBox::Cancel:
      event->ignore();
      break;
    }

  }
}


void MainWindow::createActions()
{
  saveAct = new QAction(tr("&Save"), this);
  saveAct->setStatusTip(tr("Save rules"));
  saveAct->setShortcut(QKeySequence("Ctrl+s"));
  connect(saveAct, &QAction::triggered, this, &MainWindow::saveRules);

  addAct = new QAction(tr("&Add Rule"), this);
  addAct->setStatusTip(tr("Create a new Rule"));
  addAct->setShortcut(QKeySequence("Ctrl+n"));
  connect(addAct, &QAction::triggered, this, &MainWindow::addEmptyRule);
  connect(addAct, &QAction::triggered, this, [this]{
					       this->modified = true;
					     });
  exitAct = new QAction(tr("&Exit"), this);
  exitAct->setStatusTip(tr("Exit the Application"));
  exitAct->setShortcut(QKeySequence("Ctrl+Shift+q"));
  connect(exitAct, &QAction::triggered, this, &MainWindow::close);
}

void MainWindow::createMenus()
{
  fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(saveAct);
  fileMenu->addAction(addAct);
  fileMenu->addSeparator();
  fileMenu->addAction(exitAct);
}
