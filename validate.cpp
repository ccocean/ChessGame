#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "ChessBoard.h"
#include "ImageProcess.h"
#include "FileRW.h"
#include<iostream>
#include<map>

using namespace cv;
using namespace std;

map<int,string> red;
map<int,string> black;
map<int,string> piecesCate;
map<int,string> piecesColor;

void initialMap();

//int main() 
//{ 
//	//����ƥ������
//	//vector<string> filesName=getPicName("train2");
//	////imageTrainning(filesName);
//	//ChessBoard trainnning=ChessBoard();
//	//Mat trainResultH,trainResultV;
//	//Mat trainResult;
//	//Mat temp;
//	//for (int i=0;i<11;i++)
//	//{
//	//	trainResult.push_back(trainnning.imageTrainning(filesName[i]));
//	//	trainResult.push_back(trainnning.imageTrainning(filesName[i]));
//	//	trainResult.push_back(trainnning.imageTrainning(filesName[i]));
//	//	//cout<<temp<<endl;
//	//	//trainResultH.push_back(temp);
//	//}
//	////cout<<trainResultH<<endl;
//	//WriteXML(trainResult,"train2","KnnData.xml");
//
//	//ʶ������
//	cout<<"����Ҫ����ļ�����"<<endl;
//	string folderName;
//	cin>>folderName;
//	vector<string> filesName=getPicName(folderName);
//	initialMap();
//	Mat trainResultH,trainResultV;
//	Mat trainResult;
//	trainResult=ReadXML("train2","knnData.xml");
//	ChessBoard cb;
//	ofstream imageResults;
//	for (int i = 0; i < filesName.size(); i++)
//	{
//		if (i==0)
//		{
//			imageResults.open("result.txt");
//			//imageResults.open();
//			imageResults<<"�ļ�����"<<filesName[i]<<endl;
//			imageResults.close();
//		}
//		else
//		{
//			imageResults.open("result.txt",iostream::app);
//			//imageResults.open();
//			imageResults<<"�ļ�����"<<filesName[i]<<endl;
//			imageResults.close();
//		}
//		cb=ChessBoard(imread(filesName[i],0));
//		cb.writeResult(trainResult);
//	}
//	//ChessBoard cb=ChessBoard(imread("image/chess9.JPG",0));``
//	//cb.displayResult(trainResult);
//	waitKey();
//
//	return 0; 
//}

int main()
{
	vector<Rect> rects;
	int radius;
	Point center;
	Mat src = imread("train2/11.jpg");
	Mat blurImage,grayImage;
	Mat img,thres;
	cvtColor(src, grayImage, CV_RGB2GRAY);
	vector<Vec3f> chessman;
	GaussianBlur(grayImage, blurImage, Size(5, 5), 2.1);
	HoughCircles(blurImage, chessman, CV_HOUGH_GRADIENT, 1.5, 20, 130, 38, 10, 15);
	Rect temp;
	for (size_t i = 0; i < chessman.size(); i++)
	{
		center=Point(chessman[i][0], chessman[i][1]);
		radius = chessman[i][2];
		temp = Rect(center.x - radius, center.y - radius, radius * 2, radius * 2);
		rects.push_back(temp);
		circle(src, center, radius, Scalar(0, 255, 0));
	}
	img = src(rects[5]);
	Mat imgGray;
	resize(img, img, Size(100, 100));
	cvtColor(img, imgGray, CV_RGB2GRAY);
	threshold(imgGray, thres, 210, 255, CV_THRESH_BINARY);
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
	Mat erod;
	erode(thres, erod, element);
	imshow("erode", erod);
	vector<vector<Point>> counter;
	findContours(thres, counter, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	Rect bounding;
	vector<Point> points;
	for (int i = 0; i < counter.size();i++)
	{
		for (int j = 0; j < counter[i].size();j++)
		{
			if (counter[i][j].x<15 || counter[i][j].y<15 || counter[i][j].x>85 || counter[i][j].y>85)
			{
				continue;
			}
			else
			{
				points.push_back(counter[i][j]);
			}
		}
	}
	bounding = boundingRect(points);
	rectangle(img, bounding, Scalar(255, 0, 0));
	//drawContours(img, counter, -1, Scalar(255, 0, 0));
	imshow("chessman", imgGray);
	imshow("thres", thres);
	imshow("img", img);
	imshow("1", src);
	waitKey(0);
	return 0;
}

void initialMap()
{
	red[1]="��";
	red[2]="��";
	red[3]="��";
	red[4]="��";
	red[5]="��";
	red[6]="��";
	red[7]="��";
	red[8]="��";
	red[9]="һ";

	black[1]="1";
	black[2]="2";
	black[3]="3";
	black[4]="4";
	black[5]="5";
	black[6]="6";
	black[7]="7";
	black[8]="8";
	black[9]="9";

	piecesCate[0]="��";
	piecesCate[1]="��";
	piecesCate[2]="��";
	piecesCate[3]="��";
	piecesCate[4]="��";
	piecesCate[5]="��";
	piecesCate[6]="ʿ";
	piecesCate[7]="��";
	piecesCate[8]="��";
	piecesCate[9]="˧";
	piecesCate[10]="��";
	piecesCate[11]="��";

	piecesColor[1]="��";
	piecesColor[2]="��";
	piecesColor[0]="��";
}