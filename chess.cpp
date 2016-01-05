#include "chess.h"

static cv::Mat QImage2Mat(QImage img);

Chess::Chess()
{

}

Chess::~Chess()
{
    image.release();
    grayImage.release();
}

void Chess::initImg(QImage img)
{
    this->image=QImage2Mat(img);
}

void Chess::startProc()
{
    cvtColor(image,grayImage,CV_RGB2GRAY);
    GaussianBlur(grayImage,blurImage,Size(5,5),2.1);
    HoughCircles(blurImage,chessman,CV_HOUGH_GRADIENT,1.5,10,130,38,10,15);
    this->count=chessman.size();
    //HoughCircles(grayImage,chessman,CV_HOUGH_GRADIENT,1.5,20,100,100,10,15);

    //threshold(grayImage,thresholdMat,20.0,255.0,CV_THRESH_BINARY);
    drawCircles();
}

void Chess::drawCircles()
{
    int radius;
    for(size_t i=0;i<chessman.size();i++)
    {
        Point center(cvRound(chessman[i][0]),cvRound(chessman[i][1]));
        radius=cvRound(chessman[i][2]);
        circle(image,center,radius,Scalar(0,255,0));
    }
}

static cv::Mat QImage2Mat(QImage image)
{
    cv::Mat mat;
    switch(image.format())
    {
        case QImage::Format_ARGB32:
        case QImage::Format_RGB32:
        case QImage::Format_ARGB32_Premultiplied:
            mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
            break;
        case QImage::Format_RGB888:
            mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
            cv::cvtColor(mat, mat, CV_BGR2RGB);
            break;
        case QImage::Format_Indexed8:
            mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
            break;
    }
    return mat;
}
