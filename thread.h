#ifndef THREAD_H
#define THREAD_H

#include <opencv2/opencv.hpp>
#include <QThread>

enum DIM {ROW, COL};

class Thread : public QThread
{
    Q_OBJECT

public:
    Thread();
    void setMainImage(const cv::String& fileName);
    void setTemplImage(const cv::String& fileName);
    void matchTemplating();
    cv::Mat getMainData() const;
    cv::Mat getTemplData() const;
    cv::Point getPoint() const;
    void stop();

signals:
    void threadFinished();
    void mainDataReady();
    void templDataReady();

protected:
    void run() override;

private:
    cv::String mainFileName;
    cv::String templFileName;
    cv::Mat data;
    cv::Mat templ;
    cv::Point matchLoc;
    enum OPERATION {loadMainFile, loadTemplateFile, matchingTemplate};
    OPERATION m_nOperation;

};

#endif // THREAD_H
