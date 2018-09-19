#include "mainwindow.h"
#include <iostream>
#include <QMainWindow>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent)
{ 
  std::cout << "Constructor\n";
}

MainWindow::~MainWindow() {
  std::cout << "Destructor\n";
}
