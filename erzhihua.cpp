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
    src1.convertTo(m1, COLOR_RGB2GRAY);
    
    
    for (int row = 0; row < rows ; row ++) {
        for (int col = 0; col < cols ; col++) {
            uchar *dstPtr = dst1.ptr<uchar>(row,col);
            uchar *src1Ptr = m1.ptr<uchar>(row,col);
            
            if (src1Ptr[0] > 200) {
                dstPtr[0] = 255 ;
                dstPtr[1] = 255;
                dstPtr[2] = 255;
            }else{
                dstPtr[0] = 0 ;
                dstPtr[1] = 0;
                dstPtr[2] = 0;
            }
            
           
        }
    }
    

    imshow("blamed demo", dst1);
    
    
    
    
    
    
    
    waitKey();
    
    return 0;
}
