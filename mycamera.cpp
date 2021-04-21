#include "mycamera.h"
#include <QFileDialog>
#include <QDebug>

MyCamera::MyCamera(QMainWindow *parent)
  :QMainWindow(parent),ui(new Ui::MainWindow)
{
  qDebug()<<"MyCamera in Thread "<<this->QObject::thread()->currentThreadId();
  ui->setupUi(this);
  
  // The thread and the worker are created in the constructor so it is always safe to delete them.
  thread = new QThread();
  worker = new Worker();

  worker->moveToThread(thread);
  connect(worker, SIGNAL(valueChanged(QString)), ui->label, SLOT(setText(QString)));
  connect(worker, SIGNAL(workRequested()), thread, SLOT(start()));
  connect(thread, SIGNAL(started()), worker, SLOT(doWork()));
  connect(worker, SIGNAL(finished()), thread, SLOT(quit()), Qt::DirectConnection);
}

MyCamera::~MyCamera(){
  worker->abort();
  thread->wait();
  qDebug()<<"Deleting thread and worker in Thread "<<this->QObject::thread()->currentThreadId();
  delete thread;
  delete worker;

  delete ui;
}

void MyCamera::closeEvent(QCloseEvent *event){
  qDebug()<<"Closing MyCamera ";
  worker->abort();
  thread->wait();
  qDebug()<<"Deleting thread and worker in Thread "<<this->QObject::thread()->currentThreadId();
  delete thread;
  delete worker;

  delete ui;
}

void MyCamera::on_startThread_clicked()
{
  // To avoid having two threads running simultaneously, the previous thread is aborted.
  worker->abort();
  thread->wait(); // If the thread is not running, this will immediately return.

  worker->requestWork();
}
void MyCamera::on_openCamera_clicked()
{
     //调用窗口打开文件
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("open image"),
                                                    ".",
                                                    tr("Image file(*.png *.jpg *.bmp)"));
    image = imread(filename.toLocal8Bit().data());
    if(image.data) {
        //ui->pushButton_2->setEnabled(true);
        // prepare the image for the Qt format...
        // ... change color channel ordering (from BGR in our Mat to RGB in QImage)
        cvtColor(image, image, CV_BGR2RGB);
        //cvtColor(image, image, CV_BGR2GRAY); // in gray
    }
    //将Mat图像转换为QImage图像，才能显示在label上
    // QImage img = QImage((const unsigned char*)(image.data),
    //                     image.cols, image.rows, QImage::Format_RGB888);
    QImage img = mat2QImage(image);
    //设定图像大小自适应label窗口的大小
    //img = img.scaled(ui->imgLabel->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->imgLabel->setPixmap(QPixmap::fromImage(img));
}

QImage MyCamera::mat2QImage(cv::Mat& mat)
{

	// 8-bits unsigned, NO. OF CHANNELS = 1
	if(mat.type() == CV_8UC1)
	{
#if 0
		qDebug() << "CV_8UC1";
#endif
		QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
		// Set the color table (used to translate colour indexes to qRgb values)
		image.setColorCount(256);
		for(int i = 0; i < 256; i++)
		{
			image.setColor(i, qRgb(i, i, i));
		}
		// Copy input Mat
		uchar *pSrc = mat.data;
		for(int row = 0; row < mat.rows; row ++)
		{
			uchar *pDest = image.scanLine(row);
			memcpy(pDest, pSrc, mat.cols);
			pSrc += mat.step;
		}
		return image;
	}
	// 8-bits unsigned, NO. OF CHANNELS = 3
	else if(mat.type() == CV_8UC3)
	{
		// Copy input Mat
		const uchar *pSrc = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
		return image.rgbSwapped();
	}
	else if(mat.type() == CV_8UC4)
	{
#if 0
		qDebug() << "CV_8UC4";
#endif
		// Copy input Mat
		const uchar *pSrc = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
		return image.copy();
	}
	else
	{
#if 0
		qDebug() << "ERROR: Mat could not be converted to QImage.";
#endif
		QMessageBox::information(
			NULL,
			"Error",
			"Image Format Unknown!",
			QMessageBox::Yes | QMessageBox::No,
			QMessageBox::Yes);
		return QImage();
	}
}
