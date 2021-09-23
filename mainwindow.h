#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include "thread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void getMainImageFromThr();
    void getTemplImageFromThr();

protected:
    virtual void closeEvent(QCloseEvent *pEvent) override;

private slots:
    void thread_finished();
    void on_pushButton_findTempl_clicked();
    void on_pushButton_setMainImage_clicked();
    void on_pushButton_setTemplateImage_clicked();

private:
    Thread *thr;
    cv::String open();
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
