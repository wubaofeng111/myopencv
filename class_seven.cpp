//
//  class_five.cpp
//  myopencv
//
//  Created by wu baofeng on 2019/7/11.
//  Copyright © 2019 friday. All rights reserved.
//

#include <stdio.h>
#include "classfour.hpp"

int main()
{
    
    Mat src1,src2;
    Mat dst1,dst2;
    
    src1 = imread("/Users/wubaofeng/Desktop/my_github/myopencv/class_three/cjk.jpg");
    if (src1.empty()) {
        printf("没有读取到图像");
        return -1;
    }
    imshow("cjk", src1);
    
//    src2 = imread("/Users/wubaofeng/Desktop/my_github/myopencv/class_three/cjk1.png");
//    if (src2.empty()) {
//        printf("没有读取到图像");
//        return -1;
//    }
    
    
//    imshow("cjk1", src2);
    
    
    int rows = src1.rows;
    int cols = src1.cols;
    dst1 = Mat::zeros(rows, cols , src1.type());
    /// 公式
//    dst(i,j) = a*src(i,j)+b;
    
    float a = 0.2;
    float b = 10;
    
    
    /*
     
     for (int row = 0; row < rows ; row ++) {
     for (int col = 0; col < cols ; col++) {
     float b = src1.at<Vec3b>(row,col)[0];
     float g = src1.at<Vec3b>(row,col)[1];
     float r = src1.at<Vec3b>(row,col)[2];
     
     dst1.at<Vec3b>(row,col)[0] = saturate_cast<uchar>(al*b+bl);
     dst1.at<Vec3b>(row,col)[1] = saturate_cast<uchar>(al*g+bl);
     dst1.at<Vec3b>(row,col)[2] = saturate_cast<uchar>(al*r+bl);
     
     }
     }

     */
    
    Mat m1;
    src1.convertTo(m1, CV_32F);
    
    
    for (int row = 0; row < rows ; row ++) {
        for (int col = 0; col < cols ; col++) {
            uchar *dstPtr = dst1.ptr<uchar>(row,col);
            float *src1Ptr = m1.ptr<float>(row,col);
            dstPtr[0] = saturate_cast<uchar>(a*src1Ptr[0] +b) ;
            dstPtr[1] =saturate_cast<uchar>(a*src1Ptr[1] +b);
            dstPtr[2] = saturate_cast<uchar>(a*src1Ptr[2] +b);
        }
    }
    

    imshow("blamed demo", dst1);
    
    
    
    
    
    
    
    waitKey();
    
    return 0;
}
