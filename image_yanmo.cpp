//
//  image_yanmo.cpp
//  myopencv
//
//  Created by wu baofeng on 2019/7/10.
//  Copyright © 2019 friday. All rights reserved.
//

#include "image_yanmo.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace cv;



int main()
{
    Mat src,dst;
    src = imread("/Users/wubaofeng/Desktop/my_github/myopencv/class_three/cjk.jpg");
    if (src.empty()) {
        return -1;
    }
    
    int cols = src.cols * src.channels();
    int rows = src.rows;
    int offsetx = src.channels();
    dst = Mat::zeros(src.size(), src.type());
    
    
    
//    for(int row = 1;row < (rows-1);row++)
//    {
//        uchar *preRow = src.ptr<uchar>(row-1);
//        uchar *curRow = src.ptr<uchar>(row);
//        uchar *nexRow = src.ptr<uchar>(row+1);
//        uchar *output = dst.ptr<uchar>(row);
//        for(int col=offsetx;col<cols ;col++)
//        {
//            output[col] = saturate_cast<uchar>(curRow[col]*5 -(preRow[col]+curRow[col-offsetx]+curRow[col+offsetx]+nexRow[col]));
//        }
//    }
    
    ///定义掩膜
    Mat kernel = (Mat_<char>(3,3)<<0,-1,0,-1,5,-1,0,-1,0);
    
    filter2D(src, dst, src.depth(), kernel);
    
    imshow("41234", src);
    imshow("41235", dst);
    waitKey();
    return 0;
}
