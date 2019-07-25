//
//  class_five.cpp
//  myopencv
//
//  Created by wu baofeng on 2019/7/11.
//  Copyright © 2019 friday. All rights reserved.
//

#include <stdio.h>
#include "classfour.hpp"
#include <unistd.h>

void DrawLine(Mat img)
{
    Point p1 = Point(20,30);
    Point p2;
    p2.x = 300;
    p2.y = 300;
    Scalar color = Scalar(0,0,255);
    line(img, p1,p2, color,1,LINE_AA);
}

void DrawRect(Mat img)
{
    Rect frame(100,200,300,300);
    Scalar color(255,255,0);
    rectangle(img, frame, color,2,LINE_8);
}

void DrawEllipse(Mat img)
{
    Point center(250,250);
    Size  axes(300/4,300/8);
    Scalar color(0,200,100);
    //90 倾斜程度
    //0 开始角度
    //360 结束角度
    ellipse(img, center, axes, 90, 0, 360, color,2,LINE_8);
}
void DrawCircle(Mat img)
{
    circle(img, Point(250,250), 250, Scalar(100,200,120),3,LINE_8);
}
void DrawwPolygon(Mat img)
{
    
    
    int itx[1][5];
    itx[0][0] = 1;
    itx[0][1] = 2;
    itx[0][2] = 3;
    itx[0][3] = 4;
    itx[0][4] = 5;
    
    cout <<itx[0]<<endl;
    int *its[] = {itx[0]};
    cout <<its[0]<<endl;
    
    cout <<itx<<endl;
    cout <<its<<endl;
    
    
    
    
    
    Point points[1][5];
    points[0][0] = Point(100,100);
    points[0][1] = Point(100,200);
    points[0][2] = Point(200,200);
    points[0][3] = Point(200,100);
    points[0][4] = Point(100,100);
    
    
    const Point * pts[] = {points[0]};
    cout <<"point"<<points[0]<<endl;
    cout <<"pts"<<pts[0]<<endl;

    int npt[] = {5};
    Scalar color = Scalar(255,0,100);
//    fillPoly(img, points, npt, 1, color,);
    fillPoly(img, pts, npt, 1, color);
}


void DrawText(Mat img)
{
    putText(img, "hello world", Point(10,20), FONT_ITALIC, 1.0, Scalar(0,0,255));
}

void DrawRadomLine(Mat img)
{
    RNG rng(12345);
    Point pt1,pt2;
    Scalar color;
    namedWindow("random Line");
    
    for (int i = 0; i< 100000; i++) {
        pt1.x = rng.uniform(0, img.cols);
        pt1.y = rng.uniform(0, img.rows);
        
        pt2.x = rng.uniform(0, img.cols);
        pt2.y = rng.uniform(0, img.rows);
        
        color = Scalar(rng.uniform(0, 255),rng.uniform(0, 255),rng.uniform(0, 255));
        line(img, pt1, pt2, color,1,LINE_8);
        imshow("random Line", img);

//        waitKey(50);
//        if (waitKey(50) > 0) {
//            break;
//        }
    }
    
    
    
}

void bfBlur(Mat sc1,Mat sc2 ,int bx,int by)
{
    int rows = sc1.rows;
    int cols = sc1.cols;
    
    
    for(int row = 1;row < rows-1;row++)
    {
        for(int col=1;col < cols-1;col++)
        {
            
        }
    }
}

int main()
{
    
    Mat src,dst;
    src = imread("/Users/wubaofeng/Desktop/my_github/myopencv/class_29/timg.jpg");
    
    imshow("src", src);
//    medianBlur(src, dst, 3);
//    imshow("dst", dst);
    
    Mat gsblur,sbBlur;
    
    bilateralFilter(src, sbBlur, 15, 100, 5);
    GaussianBlur(src, gsblur, Size(15,15), 3,3);
    
    imshow("gsblur", gsblur);
    imshow("sbblur", sbBlur);
    
    
    Mat kernel = (Mat_<int>(3,3)<< 0,-1,0,-1,5,-1,0,-1,0);
    
    filter2D(sbBlur, dst, -1, kernel,Point(-1,-1),0);
    imshow("dst", dst);
    
    
//    Mat src1 = imread("/Users/wubaofeng/Desktop/my_github/myopencv/class_three/cjk.jpg");
//
//    Mat dst1;
//
//    imshow("src1",src1);
//    blur(src1, dst1, Size(15,15),Point(-1,-1));
//    imshow("dst1", dst1);
//    //
//    Mat gaosi;
//    GaussianBlur(src1, gaosi, Size(15,15), 11,11);
//    imshow("gaossian", gaosi);
//
    waitKey();
    return 0;
}
