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
    
    Mat src1,src2,dst;
    
    src1 = imread("/Users/wubaofeng/Desktop/my_github/myopencv/class_three/cjk.jpg");
    if (src1.empty()) {
        printf("没有读取到图像");
        return -1;
    }
    imshow("cjk", src1);
    
    src2 = imread("/Users/wubaofeng/Desktop/my_github/myopencv/class_three/cjk1.png");
    if (src2.empty()) {
        printf("没有读取到图像");
        return -1;
    }
    imshow("cjk1", src2);
    
    double alpha = 0.5;
    
    int rows = src1.rows;
    int cols = src1.cols;
    dst = Mat::zeros(rows, cols , src1.type());
    Mat dst2;
    
    
    if (src1.rows == src2.rows && src2.cols == src1.cols &&src1.type() == src2.type()) {
        
        for (int row = 0; row < rows ; row ++) {
            for (int col = 0; col < cols ; col++) {
                uchar *dstPtr = dst.ptr<uchar>(row,col);
                uchar *src1Ptr = src1.ptr<uchar>(row,col);
                uchar *src2Ptr = src2.ptr<uchar>(row,col);
                dstPtr[0] = alpha*src1Ptr[0] + (1-alpha)*src2Ptr[0];
                dstPtr[1] = alpha*src1Ptr[1] + (1-alpha)*src2Ptr[1];
                dstPtr[2] = alpha*src1Ptr[2] + (1-alpha)*src2Ptr[2];
            }
        }
        
        addWeighted(src1, 0.5, src2, 1-alpha, 0.0, dst2);
//        multiply(src1, src2, dst,1.0);
//        dst = src1 - src2;
        imshow("blamed demo", dst);
        imshow("blamed demo2", dst2);
    }else{
        cout<<"the size of the images is not same"<<endl;
    }
    
    
    
    
    
    
    waitKey();
    
    return 0;
}
