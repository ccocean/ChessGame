#ifndef CHESS_H
#define CHESS_H

//Qt head files
#include <QImage>

//opencv head files
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
using namespace cv;

class Chess
{
public:
    Chess();
    void initImg(QImage img);
private:
    Mat image,grayImage;
}

#endif // CHESS_H
