#ifndef CHESS_HEADER_H
#define CHESS_HEADER_H

//std head files
#include <vector>
using namespace std;

//Qt head files
#include <QImage>
#ifdef _DEBUG
#include<QDebug>
#endif

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

#define RED_MIN 70
#define RED_MAX 110
#define BLK_MIN 0
#define BLK_MAX 30

typedef struct Result
{
    int color;
    int type;
    Point center;
    int radius;
    Mat img;
    Mat thres;
    Mat feature;
}Result_t;

enum ColorTypes
{
    WHITE=0,
    BLACK=1,
    RED=2
};

enum FeatureTypes
{
    LINEAR=0,
    MATRIX=1
};

#endif // CHESS_DATA_H
