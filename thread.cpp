#include <opencv2/opencv.hpp>
#include "thread.h"
#include "mainwindow.h"
#include "convert.h"
#include <QtWidgets>

Thread::Thread():QThread(nullptr){}

void Thread::run()
{
    switch(m_nOperation)
    {
    case loadMainFile:
        data = cv::imread(mainFileName, cv::IMREAD_COLOR);
        emit mainDataReady();
        break;
    case loadTemplateFile:
        templ = cv::imread(templFileName, cv::IMREAD_COLOR);
        emit templDataReady();
        break;
    case matchingTemplate:
        cv::Mat result;
        int match_method = cv::TM_SQDIFF_NORMED;
        cv::matchTemplate(data, templ, result, match_method);
        double minVal;
        double maxVal;
        cv::Point minLoc;
        cv::Point maxLoc;
        minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat() );
        if( match_method  == cv::TM_SQDIFF || match_method == cv::TM_SQDIFF_NORMED )
            matchLoc = minLoc;
        else
            matchLoc = maxLoc;
        emit threadFinished();
        break;
    }
}

void Thread::setMainImage(const cv::String &fileName)
{
    if(isRunning()) return;
    m_nOperation = loadMainFile;
    mainFileName = fileName;
    QThread::start();
}

void Thread::setTemplImage(const cv::String &fileName)
{
    if(isRunning()) return;
    m_nOperation = loadTemplateFile;
    templFileName = fileName;
    QThread::start();
}

void Thread::matchTemplating()
{
    if(isRunning()) return;
    m_nOperation = matchingTemplate;
    QThread::start();
}



cv::Point Thread::getPoint() const { return matchLoc; }

cv::Mat Thread::getMainData()const { return data; }

cv::Mat Thread::getTemplData() const{ return templ; }


void Thread::stop()
{
    requestInterruption();
}
