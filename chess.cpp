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

    vecResult.reserve((size_t)this->count);
    Result_t temp=Result_t();
    for(int i=0;i<this->count;i++)
    {
        vecResult.push_back(temp);
    }
    drawCircles();
    analyzeBoard();
}

void Chess::drawCircles()
{
    int radius;
    Result_t temp;
    Mat tempMat;
    for(int i=0;i<this->count;i++)
    {
        Point center(cvRound(chessman[i][0]),cvRound(chessman[i][1]));
        radius=cvRound(chessman[i][2]);
        //qDebug("radius %d = %d\r\n",i,radius);
        circle(image,center,radius,Scalar(0,255,0));
        vecResult[i].color=checkColor(center,radius);
        vecResult[i].center=center;
        vecResult[i].radius=radius;
        vecResult[i].img=tempMat.clone();
        vecResult[i].feature=tempMat.clone();
        vecResult[i].thres=tempMat.clone();
    }
}

void Chess::analyzeBoard()
{
    vector<vector<Point>> counter;
    vector<Point> points;
    Rect bounding;
    for(size_t i=0;i<vecResult.size();i++)
    {
        //vecResult[i].img=grayImage(Rect(vecResult[i].center.x,vecResult[i].center.y,vecResult[i].radius,vecResult[i].radius));
        //resize(vecResult[i].img,vecResult[i].img,Size(100,100));
        //threshold(vecResult[i].img,vecResult[i].thres,210,255,CV_THRESH_BINARY);
        //findContours(vecResult[i].thres,counter,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
        for(size_t j=0;j<counter.size();j++)
        {
            for(size_t k=0;k<counter[j].size();k++)
            {
                if (counter[j][k].x<15 || counter[j][k].y<15 || counter[j][k].x>85 || counter[j][k].y>85)
                {
                    continue;
                }
                else
                {
                    points.push_back(counter[j][k]);
                }
            }
        }
        bounding=boundingRect(points);
        bounding.x-=5;bounding.y-=4;
        bounding.width+=10;bounding.height+=14;
        //vecResult[i].img=vecResult[i].img(bounding);
        //threshold(vecResult[i].img,vecResult[i].thres,210,255,CV_THRESH_BINARY);
        getFeature(LINEAR,i);
    }
}

Mat Chess::getFeature(int type,int num)
{
    Mat output;
    switch(type)
    {
    case LINEAR:
        //vecResult[num].feature=getLinearFeature(vecResult[num].thres);
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
    Mat output(1,input.cols,CV_8UC1);
    int i=0,j=0;
    int cnt=0;
    int temp;
    for(i=0;i<input.cols;i++)
    {
        for(j=0;j<input.rows;j++)
        {
            temp=(int)input.ptr<uchar>(i)[j];
            if(temp>0)
                cnt+=temp;
            else
                continue;
        }
        output.ptr<uchar>(0)[i]=(uchar)cnt;
    }
    return output;
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
