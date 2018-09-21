#include <vector>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QVBoxLayout>

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0);

private:
  QMenu *fileMenu;
  QAction *addAct;
  QAction *saveAct;
  QAction *exitAct;
  QVBoxLayout *mainLayout;
  QWidget *mainWidget;

  void createMenus();
  void createActions();

  void exit();
  void addRule();
  void saveRules();
  void deleteRule(int index);
};
