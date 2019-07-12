//
//  classfour.cpp
//  myopencv
//
//  Created by wu baofeng on 2019/7/11.
//  Copyright © 2019 friday. All rights reserved.
//

#include "classfour.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    Mat src;
    src = imread("/Users/wubaofeng/Desktop/my_github/myopencv/class_three/cjk.jpg");
    if (src.empty()) {
        printf("没有读取到图像");
        return -1;
    }
    imshow("cjk", src);
    
    
    Mat dst;
//    dst = Mat(src.size(),src.type());
//    dst = Scalar(127,0,255);
    
//    dst = src.clone();
    
    
//    src.copyTo(dst);
    printf("%d",src.channels());
    cvtColor(src, dst, COLOR_RGB2GRAY);
    printf("%d",dst.channels());
    
    imshow("dstimg", dst);
    
    Mat mrc;
    mrc.create(3, 3, CV_8UC4);
    mrc = Scalar(127,127);
    cout <<"M="<<endl<<mrc<<endl;
//    imshow("1234555", mrc);
    
    Mat kerner = (Mat_<float>(3,3)<<0,-1,0,-1,5,-1,0,-1,0);
    Mat cdst;
    filter2D(src, cdst, -1, kerner);
    imshow("qxd", cdst);
    cout<<"kerner"<<kerner<<endl;
    
    Mat m2 = Mat::zeros(src.size(), src.type());
    
    imshow("m2", m2);
    
    Mat m3 = Mat::zeros(1, 1, CV_8UC(20));
    cout<<m3<<endl;
    
    waitKey();
    
    return 0;
}
