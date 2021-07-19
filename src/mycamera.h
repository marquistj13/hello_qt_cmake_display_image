#include "ui_cameras.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>  
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

#include <QMessageBox>
#include <QThread>
#include "worker.h"

class MyCamera: public QMainWindow
{
  Q_OBJECT
public:
  explicit MyCamera(QMainWindow *parent=nullptr);
  ~MyCamera();
  void showImage();

private:
  QImage mat2QImage(cv::Mat& mat);
  void closeEvent (QCloseEvent *event);
private slots:
  void on_openCamera_clicked();
  void on_startThread_clicked();
  void on_startPlot_clicked();

private:
  Ui::MainWindow *ui;
  Mat image;
  /**
   * @brief Thread object which will let us manipulate the running thread
   */
  QThread *thread;
  /**
   * @brief Object which contains methods that should be runned in another thread
   */
  Worker *worker;
};
