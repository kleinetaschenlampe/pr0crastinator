#include "mainwindow.h"
#include <iostream>
#include <QGroupBox>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QDir>
#include <QFile>
#include <QXmlStreamWriter>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent)
{ 
  createActions();
  createMenus();
  resize(700,400);

  mainLayout = new QVBoxLayout;
  mainWidget = new QWidget;
  setCentralWidget(mainWidget);
  mainWidget->setLayout(mainLayout);
}

void MainWindow::addRule(){
  QWidget *widgetRule = new QWidget;
  QHBoxLayout *layout = new QHBoxLayout;
  QComboBox *comboRuletype = new QComboBox;
  comboRuletype->addItem("Website");
  comboRuletype->addItem("Program");

  QLineEdit *txtRule = new QLineEdit;

  QPushButton *buttonDelete = new QPushButton("X");
  connect(buttonDelete, QPushButton::clicked, this,
	  [widgetRule, layout]{
	    widgetRule->setParent(0);
	    delete widgetRule;
	  });
  connect(buttonDelete, QPushButton::clicked, this, MainWindow::saveRules);

  layout->addWidget(comboRuletype);
  layout->addWidget(txtRule);
  layout->addWidget(buttonDelete);

  widgetRule->setLayout(layout);
  mainLayout->addWidget(widgetRule);
}

void MainWindow::saveRules(){
  // Create config dir if it doesnt exist
  QDir dir("C:/Users/fp/AppData/Local/pr0crastrinator");
  if (!dir.exists()) {
    dir.mkdir(".");
  }
  
  // Write to the file
  QFile::remove("C:/Users/fp/AppData/Local/pr0crastrinator/rules.xml");
  QFile file("C:/Users/fp/AppData/Local/pr0crastrinator/rules.xml");
  file.open(QIODevice::ReadWrite);
  QXmlStreamWriter xmlWriter(&file);
  xmlWriter.setAutoFormatting(true);
  xmlWriter.writeStartDocument();
  xmlWriter.writeStartElement("rules");

  QList<QWidget *> currentRules = mainWidget->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly);
  for(int i = 0; i != currentRules.size(); i++){
    xmlWriter.writeStartElement("rule");
    xmlWriter.writeTextElement("type",currentRules[i]->findChild<QComboBox *>()->currentText());
    xmlWriter.writeTextElement("text",currentRules[i]->findChild<QLineEdit *>()->text());
    xmlWriter.writeEndElement();
  }

  xmlWriter.writeEndElement();
  file.close();
}

void MainWindow::exit(){
  QWidget::close();
}

void MainWindow::createActions(){
  saveAct = new QAction(tr("&Save"), this);
  saveAct->setStatusTip(tr("Save rules"));
  connect(saveAct, &QAction::triggered, this, &MainWindow::saveRules);

  addAct = new QAction(tr("&Add Rule"), this);
  addAct->setStatusTip(tr("Create a new Rule"));
  connect(addAct, &QAction::triggered, this, &MainWindow::addRule);

  exitAct = new QAction(tr("&Exit"), this);
  exitAct->setStatusTip(tr("Exit the Application"));
  connect(exitAct, &QAction::triggered, this, &MainWindow::exit);
}

void MainWindow::createMenus(){
  fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(saveAct);
  fileMenu->addAction(addAct);
  fileMenu->addSeparator();
  fileMenu->addAction(exitAct);
}
