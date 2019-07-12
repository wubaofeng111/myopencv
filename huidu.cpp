//
//  huidu.cpp
//  myopencv
//
//  Created by wu baofeng on 2019/7/10.
//  Copyright © 2019 friday. All rights reserved.
//

#include "huidu.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void showHuidu()
{
    Mat img = imread("/Users/wubaofeng/Desktop/my_github/myopencv/class_image/imageread介绍.png",IMREAD_GRAYSCALE);
    imshow("grayImg", img);
    
    waitKey();
}

void CVColorTest()
{
    Mat img = imread("/Users/wubaofeng/Desktop/my_github/myopencv/class_image/cvtColor.png");
    namedWindow("1234",WINDOW_AUTOSIZE);
    Mat output_image;
    cvtColor(img, output_image, COLOR_RGB2HLS);
    imshow("1234", output_image);
    imwrite("cvcolor.tiff", output_image);
    Mat hsu;
    cvtColor(img, hsu, COLOR_RGB2HSV);
    
    imwrite("cv_hsv.png", hsu);
    
    waitKey();
    return;
}

int main()
{
    CVColorTest();
   
    return 0;
}
