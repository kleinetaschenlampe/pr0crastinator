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
  mainLayout = new QVBoxLayout;
  mainWidget = new QWidget;
  mainScrollArea = new QScrollArea;

  createActions();
  createMenus();
  resize(700,400);

  mainScrollArea->setWidget(mainWidget);
  mainScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  mainScrollArea->setWidgetResizable(true);
  setCentralWidget(mainScrollArea);
  mainWidget->setLayout(mainLayout);

  loadRules();
}

QWidget *MainWindow::addEmptyRule(){
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
  return widgetRule;
}

QWidget *MainWindow::addRule(QString type, QString text){
  QWidget *widgetRule = addEmptyRule();
  QComboBox *combo = widgetRule->findChild<QComboBox *>();
  combo->setCurrentIndex(combo->findText(type));

  QLineEdit *edit = widgetRule->findChild<QLineEdit *>();
  edit->setText(text);
  return widgetRule;
}

void MainWindow::loadRules(){
  QFile file("C:/Users/fp/AppData/Local/pr0crastrinator/rules.xml");
  // TODO error handling
  file.open(QIODevice::ReadOnly);
  QXmlStreamReader reader(&file);
  while(!reader.atEnd() && !reader.hasError()){
    if(reader.readNext() == QXmlStreamReader::StartElement && reader.name() == "rule"){
      QString type; QString text;

      while(!(reader.readNext() == QXmlStreamReader::EndElement)){
	if(reader.name() == "type")
	  type = reader.readElementText();
	if(reader.name() == "text")
	  text = reader.readElementText();

      }

      std::cout << type.toStdString() << " " << text.toStdString() << std::endl;
      addRule(type, text);
    }
  }

  file.close();
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
  // TODO error handling
  file.open(QIODevice::ReadWrite);
  QXmlStreamWriter xmlWriter(&file);
  xmlWriter.setAutoFormatting(true);
  xmlWriter.writeStartDocument();
  xmlWriter.writeStartElement("rules");

  QList<QWidget *> currentRules =
    mainWidget->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly);
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
  saveAct->setShortcut(QKeySequence("Ctrl+s"));
  connect(saveAct, &QAction::triggered, this, &MainWindow::saveRules);

  addAct = new QAction(tr("&Add Rule"), this);
  addAct->setStatusTip(tr("Create a new Rule"));
  addAct->setShortcut(QKeySequence("Ctrl+n"));
  connect(addAct, &QAction::triggered, this, &MainWindow::addEmptyRule);

  exitAct = new QAction(tr("&Exit"), this);
  exitAct->setStatusTip(tr("Exit the Application"));
  exitAct->setShortcut(QKeySequence("Ctrl+Shift+q"));
  connect(exitAct, &QAction::triggered, this, &MainWindow::exit);
}

void MainWindow::createMenus(){
  fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(saveAct);
  fileMenu->addAction(addAct);
  fileMenu->addSeparator();
  fileMenu->addAction(exitAct);
}
