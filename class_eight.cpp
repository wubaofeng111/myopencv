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

int main()
{
    
    Mat src1;
    src1 = Mat::eye(500, 500, CV_8UC3);
    DrawLine(src1);
    DrawRect(src1);
    DrawEllipse(src1);
    DrawCircle(src1);
    DrawwPolygon(src1);
    DrawText(src1);
    DrawRadomLine(src1);
    
    imshow("one view", src1);
    
    waitKey();
    
    return 0;
}
