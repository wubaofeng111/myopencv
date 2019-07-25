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

/*
 1
 */
Mat src,src_gray,dst,src_tow;
int max_value = 255;
int should_value = 100;

char *output_window = "output_window";

void Demo_Contour(int a ,void* b)
{
    Mat bin_output;
    
    threshold(src_tow, bin_output, should_value, max_value, THRESH_BINARY);
    
    
    vector<vector<Point>> contourPoints;
    vector<Vec4i> heirachy;
    
    findContours(bin_output, contourPoints, heirachy, RETR_TREE, CHAIN_APPROX_SIMPLE,Point(0,0));
    
    vector<vector<Point>> convexs(contourPoints.size());
    
    for (int i = 0; i<contourPoints.size(); i++) {
        convexHull(contourPoints[i], convexs[i],false,true);
    }
    
    dst = Mat::zeros(src.size(), CV_8UC3);
    RNG rng(12345);
    
    for (size_t i = 0; i<convexs.size(); i++) {
        Scalar color = Scalar(rng.uniform(0, 255),rng.uniform(0, 255),rng.uniform(0, 255));
        drawContours(src, convexs, (int)i, color,2,8,-1,0,Point(0,0));
    }
    imshow(output_window, src);
}




int main()
{
    
    
    src = imread("/Users/wubaofeng/Desktop/my_github/myopencv/att_faces/s1/1.png");
    
    imshow("src", src);
    
    int rows = src.rows;
    int cols = src.cols;
    
    for (int row = 0; row < rows ; row ++) {
        for (int col = 0; col < cols ; col++) {
            if (src.at<Vec3b>(row,col) == Vec3b(255,255,255))
            {
                src.at<Vec3b>(row,col)[0] = 0;
                src.at<Vec3b>(row,col)[1] = 0;
                src.at<Vec3b>(row,col)[2] = 0;
            }
        }
    }
    
    namedWindow(output_window);
    imshow(output_window, src);
    
    /// 锐化
    Mat kernel = (Mat_<float>(3,3)<<1,1,1,1,-8,1,1,1,1);
    Mat imgLaplance;
    Mat sharpenImage = src;
    filter2D(src, imgLaplance, CV_32F, kernel,Point(-1,-1),0,BORDER_DEFAULT);
    src.convertTo(sharpenImage, CV_32F);
    Mat resultImg = sharpenImage - imgLaplance;
    resultImg.convertTo(resultImg, CV_8UC3);
    imgLaplance.convertTo(imgLaplance, CV_8UC3);
    imshow("resultImg", resultImg);
    /// 二值化
    Mat binaryImg;
    cvtColor(resultImg, resultImg, COLOR_BGR2GRAY);
    threshold(resultImg, binaryImg, 40, 255, THRESH_BINARY|THRESH_OTSU);
    
    imshow("binnaryImg", binaryImg);
    /// 距离变化
    Mat distImg;
    distanceTransform(binaryImg, distImg, DIST_L1, 3, 5);
    normalize(distImg, distImg,0,1,NORM_MINMAX);
    
    imshow("distImg", distImg);
    /// 再次二值化
    threshold(distImg, distImg, 0.4, 1, THRESH_BINARY);
    imshow("binner_2", distImg);
    
    Mat kerne2 = Mat::ones(13, 13, CV_8UC1);
    
    erode(distImg, distImg, kerne2,Point(-1,-1));
    imshow("erode", distImg);
    
    /// 编号
    Mat dist_8u;
    distImg.convertTo(dist_8u, CV_8U);
    
    vector<vector<Point>> contours;
    findContours(dist_8u, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0,0));
    // 创建编号
    Mat marks = Mat::zeros(src.size(), CV_32SC1);
    RNG rng(12345);
    for (int i = 0; i < contours.size(); i++) {
        drawContours(marks, contours, static_cast<int>(i), Scalar(rng.uniform(0, 255),rng.uniform(0, 255),rng.uniform(0, 255)),-1);
    }
    circle(marks,Point(5,5),3,Scalar(255,255,255),-1);
    
//    imshow("marks", marks*1000);
    
    /// 分水岭变化
    watershed(src, marks);
    Mat mark = Mat::zeros(marks.size(), CV_8UC1);
    marks.convertTo(mark, CV_8UC1);
    bitwise_not(mark, mark,Mat());
    imshow("mark", mark);
    
    waitKey();
    return 0;
}
