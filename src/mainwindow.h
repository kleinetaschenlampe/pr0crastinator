#include "procrule.h"
#include <vector>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QVBoxLayout>
#include <QScrollArea>

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0);


public slots:
  Procrule *addEmptyRule();
  Procrule *addRule(QString triggerType, QString triggerText,
		    QString usageType, QString actionType,
		    std::vector<QString> times);

  void saveRules();

private:
  QMenu *fileMenu;
  QAction *addAct;
  QAction *saveAct;
  QAction *exitAct;
  QVBoxLayout *mainLayout;
  QWidget *mainWidget;
  QScrollArea *mainScrollArea;

  void createMenus();
  void createActions();

  void exit();
  void loadRules();
  void deleteRule(int index);
};

#endif
