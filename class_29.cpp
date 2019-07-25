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

Mat src,gray,dst;
int max_value = 255;
int should_value = 100;

char *output_window = "output_window";

void Demo_Contour(int a ,void* b)
{
    Mat cany_output;
    vector<vector<Point>> contourPoints;
    vector<Vec4i> heirachy;
    Canny(gray, cany_output, should_value, should_value*2,3,false);
    findContours(cany_output, contourPoints, heirachy, RETR_TREE, CHAIN_APPROX_SIMPLE,Point(0,0));
    
    dst = Mat::zeros(src.size(), CV_8UC3);
    RNG rng(12345);
    
    for (size_t i = 0; i<contourPoints.size(); i++) {
        Scalar color = Scalar(rng.uniform(0, 255),rng.uniform(0, 255),rng.uniform(0, 255));
        drawContours(src, contourPoints, (int)i, color,2,8,heirachy,0,Point(0,0));
    }
    imshow(output_window, src);
}


int main()
{
    
    
    src = imread("/Users/wubaofeng/Desktop/my_github/myopencv/class_29/timg.jpg");
    
    imshow("src", src);
    
    cvtColor(src, gray, COLOR_RGB2GRAY);
    imshow("gray", gray);
    
    namedWindow(output_window);
//    moveWindow(output_window, src.cols, 0);
    
    char*trackBarTitle = "change value";
    createTrackbar(trackBarTitle, output_window, &should_value, max_value,Demo_Contour);
    Demo_Contour(0, 0);
    
    // 边缘提取
    
    
    waitKey();
    return 0;
}
