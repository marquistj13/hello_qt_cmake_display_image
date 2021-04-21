#include "cameras.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>  
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

#include <QMessageBox>

class MyCamera: public QMainWindow
{
  Q_OBJECT
public:
  explicit MyCamera(QMainWindow *parent=nullptr);
  ~MyCamera();
  void showImage();

private:
  QImage mat2QImage(cv::Mat& mat);
private slots:
  void on_openCamera_clicked();

private:
  Ui::MainWindow *ui;
  Mat image;
};
