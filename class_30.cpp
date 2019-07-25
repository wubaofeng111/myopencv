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
    
    
    src = imread("/Users/wubaofeng/Desktop/my_github/myopencv/class_29/timg.jpg");
    
    imshow("src", src);
    
    cvtColor(src, src_gray, COLOR_RGB2GRAY);
    imshow("gray", src_gray);
    
    
    
    int rows = src.rows;
    int cols = src.cols;
    
   src_tow = Mat::zeros(src.size(), CV_8UC1);

    
    
    for (int row = 0; row < rows ; row ++) {
        for (int col = 0; col < cols ; col++) {
            uchar *dstPtr = src_tow.ptr<uchar>(row,col);
            uchar *src1Ptr = src_gray.ptr<uchar>(row,col);
            
            if (src1Ptr[0] > 200) {
                dstPtr[0] = 170 ;
               
            }else{
                dstPtr[0] = 0;
            }
    
        }
    }
    imshow("erzhi1", src_tow);
    
    
    namedWindow(output_window);
//    moveWindow(output_window, src.cols, 0);
    
    char*trackBarTitle = "change value";
    createTrackbar(trackBarTitle, output_window, &should_value, max_value,Demo_Contour);
    Demo_Contour(0, 0);
    
    // 边缘提取
    
    
    waitKey();
    return 0;
}
