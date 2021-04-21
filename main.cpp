// #include "test.h"
// #include "cameras.h"
// #include <QApplication>

// int main(int argc, char *argv[])
// {
//   QApplication a(argc, argv);
//   // QWidget *widget = new QWidget;
//   // QDialog *dialog - new Qdialog;
//   QMainWindow *window = new QMainWindow;
//   // Ui::Form w;
//   // w.setupUi(widget);
//   Ui::MainWindow m;
//   m.setupUi(window);

//   // widget->show();
//   window->show();

//   return a.exec();
// }

#include "mycamera.h"
#include <QApplication>


int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QMainWindow *window = new QMainWindow;
  MyCamera* cam = new MyCamera(window);
  //MyCamera* cam = new MyCamera();
  cam->show();

  return a.exec();
}

