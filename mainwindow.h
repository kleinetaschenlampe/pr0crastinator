#include <vector>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QVBoxLayout>
#include <QScrollArea>

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0);

public slots:
  QWidget *addEmptyRule();
  QWidget *addRule(QString type, QString text);

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
  void saveRules();
  void loadRules();
  void deleteRule(int index);
};
