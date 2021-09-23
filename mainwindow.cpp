#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "convert.h"
#include <QtWidgets>
#include <opencv2/opencv.hpp>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      thr(new Thread),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(thr, SIGNAL(threadFinished()), this, SLOT(thread_finished())/*, Qt::DirectConnection*/);
    connect(thr, SIGNAL(mainDataReady()), this, SLOT(getMainImageFromThr()), Qt::QueuedConnection);
    connect(thr, SIGNAL(templDataReady()), this, SLOT(getTemplImageFromThr()), Qt::QueuedConnection);
}


MainWindow::~MainWindow()
{
    delete ui;
    delete thr;
}

void MainWindow::getMainImageFromThr()
{
    ui->label->setPixmap(ASM::cvMatToQPixmap(thr->getMainData()));
    QApplication::restoreOverrideCursor();
    ui->pushButton_setMainImage->setEnabled(true);
    statusBar()->showMessage(tr("File loaded"), 2000);
}

void MainWindow::getTemplImageFromThr()
{
    ui->label_2->setPixmap(ASM::cvMatToQPixmap(thr->getTemplData()));
    QApplication::restoreOverrideCursor();
    ui->pushButton_setTemplateImage->setEnabled(true);
    statusBar()->showMessage(tr("File loaded"), 2000);
}

void MainWindow::closeEvent(QCloseEvent *pEvent)
{
    pEvent->accept();
    thr->stop();
}

cv::String MainWindow::open()
{

    QString fileName =
            QFileDialog::getOpenFileName(this,
                                        tr("Open Image"),
                                        ".",
                                        tr("Image Files (*.png *.jpg *.bmp)"));

    return fileName.toStdString();

}

void MainWindow::thread_finished()
{
    const cv::Point a = thr->getPoint();

    QPixmap resPixmap = ASM::cvMatToQPixmap(thr->getMainData());
    QPainter painter(&resPixmap);
    painter.setPen(Qt::red);

    painter.drawRect(a.x, a.y, thr->getTemplData().cols, thr->getTemplData().rows);
    ui->label->setPixmap(resPixmap);

    QApplication::restoreOverrideCursor();
    ui->pushButton_setMainImage->setEnabled(true);
    ui->pushButton_findTempl->setEnabled(true);
    ui->pushButton_setTemplateImage->setEnabled(true);
    statusBar()->showMessage(tr("Found..."), 2000);
}


void MainWindow::on_pushButton_findTempl_clicked()
{
    if(thr->getMainData().empty() || thr->getTemplData().empty())
    {
        statusBar()->showMessage(tr("Choose images"), 2000);
        return;
    }
    else if(thr->getMainData().cols < thr->getTemplData().cols ||
            thr->getMainData().rows < thr->getTemplData().rows)
    {
        statusBar()->showMessage(tr("The template size cannot be larger"
                                    "than the size of the image"), 2000);
        return;
    }

    ui->pushButton_setMainImage->setEnabled(false);
    ui->pushButton_findTempl->setEnabled(false);
    ui->pushButton_setTemplateImage->setEnabled(false);

    QApplication::setOverrideCursor(Qt::WaitCursor);
    thr->matchTemplating();

    statusBar()->showMessage(tr("Searching..."));
}


void MainWindow::on_pushButton_setMainImage_clicked()
{
    cv::String fileName = open();
    if(fileName.empty()) return;
    ui->pushButton_setMainImage->setEnabled(false);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    thr->setMainImage(fileName);
}


void MainWindow::on_pushButton_setTemplateImage_clicked()
{
    cv::String fileName = open();
    if(fileName.empty()) return;
    ui->pushButton_setTemplateImage->setEnabled(false);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    thr->setTemplImage(fileName);

}

