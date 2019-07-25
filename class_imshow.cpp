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
    
    Mat src;
    src = imread("/Users/wubaofeng/Desktop/my_github/myopencv/class_29/123.png");
    if (src.empty()) {
        printf("没有读取到图像");
        return -1;
    }
    imshow("cjk", src);
    
//    Mat gray_mat;
//    
//    cvtColor(src, gray_mat, COLOR_RGB2GRAY);
//    
//    imshow("cjk_gray", gray_mat);
//    int rows = gray_mat.rows;
//    int cols = gray_mat.cols;
//    
//    Mat gray_dst;
//    gray_dst.create(gray_mat.size(), gray_mat.type());
//    
//    for (int row = 0; row < rows ; row++ ) {
//        for (int col = 0; col < cols; col++ ) {
//            uchar gray = gray_mat.at<uchar>(row,col);
//            gray_dst.at<uchar>(row,col) = 255-gray;
//        }
//    }
//    
//    imshow("fanse", gray_dst);
//    //
//    Mat src_fanse = Mat::zeros(src.size(), src.type());
//    
//    int height = src_fanse.rows;
//    int width  = src_fanse.cols;
//    int step   = src_fanse.channels();
//    
//    for (int y = 0; y < height ; y++ ) {
//        for (int x = 0; x < width; x++ ) {
//            if (step == 1) {
//                uchar gray = src.at<uchar>(y,x);
//                src_fanse.at<uchar>(y,x) = 255-gray;
//            }else if(step == 3){
//                int b = src.at<Vec3b>(y,x)[0];
//                int g = src.at<Vec3b>(y,x)[1];
//                int r = src.at<Vec3b>(y,x)[2];
//                src_fanse.at<Vec3b>(y,x)[0] = r;
//                src_fanse.at<Vec3b>(y,x)[1] = r;
//                src_fanse.at<Vec3b>(y,x)[2] = r;
//            }
//        }
//    }
//    imshow("src_fanse", src_fanse);
//    
//    Mat fanse_1;
//    bitwise_not(src, fanse_1);
//    imshow("fanse_1", fanse_1);
    
    
    
    waitKey();
    
    return 0;
}
