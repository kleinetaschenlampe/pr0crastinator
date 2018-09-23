#include <QApplication>
#include "mainwindow.h"

int main(int argc, char **argv){
  // QLocale curLocale(QLocale("de_DE"));
  // QLocale::setDefault(curLocale);
  
  QApplication app(argc, argv);
  MainWindow gui;
  gui.show();
  return app.exec();
}
