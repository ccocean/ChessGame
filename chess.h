#ifndef CHESS_H
#define CHESS_H

#include "chess_header.h"

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
    std::vector<Vec3f> chessman;
    int count;
    std::vector<Result_t> vecResult;

    //functions
    void drawCircles();
    int checkColor(Point center, int radius);
    void analyzeBoard();
    Mat getFeature(int type,int num);
};

#endif // CHESS_H
