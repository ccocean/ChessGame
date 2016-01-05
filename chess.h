#ifndef CHESS_H
#define CHESS_H

//std head files
#include <vector>
using namespace std;

//Qt head files
#include <QImage>

//opencv head files
//#include <opencv2/core.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/imgproc.hpp>
#include "include/opencv2/core.hpp"
#include "include/opencv2/highgui.hpp"
#include "include/opencv2/imgproc.hpp"

using namespace cv;
#pragma comment( lib, "opencv_core310d.lib")
#pragma comment( lib, "opencv_highgui310d.lib")
#pragma comment( lib, "opencv_imgproc310d.lib")

class Chess
{
public:
    Chess();
    ~Chess();
    void initImg(QImage img);
    void startProc();

    inline int getCount()
    {
        if(count>0)
            return count;
        else
            return -1;
    }

private:
    Mat image,grayImage,blurImage,thresholdMat;
    vector<Vec3f> chessman;
    int count;

    //functions
    void drawCircles();
};

#endif // CHESS_H
