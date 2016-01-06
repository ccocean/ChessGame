#include "chess.h"

static cv::Mat QImage2Mat(QImage img);
static cv::Mat getLinearFeature(cv::Mat input);
static cv::Mat getMatrixFeature(cv::Mat input);

Chess::Chess()
{

}

Chess::~Chess()
{
    //image.release();
    //grayImage.release();
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

    //threshold(grayImage,thresholdMat,20.0,255.0,CV_THRESH_BINARY);
    drawCircles();
}

void Chess::drawCircles()
{
    int radius;
    Result_t temp;
    for(size_t i=0;i<chessman.size();i++)
    {
        Point center(cvRound(chessman[i][0]),cvRound(chessman[i][1]));
        radius=cvRound(chessman[i][2]);
        //qDebug("radius %d = %d\r\n",i,radius);
        circle(image,center,radius,Scalar(0,255,0));
        temp.color=checkColor(center,radius);
        temp.center=center;
        temp.radius=radius;
        vecResult.push_back(temp);
        temp=Result_t();
    }
}

void Chess::analyzeBoard()
{
    for(size_t i=0;i<vecResult.size();i++)
    {
        vecResult[i].img=grayImage(Rect(vecResult[i].center.x,vecResult[i].center.y,vecResult[i].radius,vecResult[i].radius));
        resize(vecResult[i].img,vecResult[i].img,Size(100,100));
    }
}

Mat Chess::getFeature(int type)
{
    Mat output;
    switch(type)
    {
    case LINEAR:
        break;
    case MATRIX:
        break;
    default:
        break;
    }
    return output;
}

int Chess::checkColor(Point center, int radius)
{
    int red=0,black=0,white=0;
    int temp;
    for(int i=center.y-radius;i<center.y+radius;i++)
    {
        for(int j=center.x-radius;j<center.x+radius;j++)
        {
            temp=(int)grayImage.ptr<uchar>(i)[j];
            if (temp>=BLK_MIN&&temp<=BLK_MAX)
            {
                black++;
            }
            else if (temp>=RED_MIN&&temp<=RED_MAX)
            {
                red++;
            }
            else
            {
                white++;
            }
        }
    }
    if (black>red)
    {
        if (black>white)
        {
            return BLACK;
        }
        else
        {
            return WHITE;
        }
    }
    else
    {
        if (red>white)
        {
            return RED;
        }
        else
            return WHITE;
    }
}

static cv::Mat getLinearFeature(cv::Mat input)
{
    Mat output(1,intput.cols/2,CV_8UC1);
    int i=0,j=0;
    for(i=0;i<input.cols;i++)
    {

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
