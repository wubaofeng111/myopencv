//
//  imageFix.cpp
//  myopencv
//
//  Created by friday on 2019/7/8.
//  Copyright © 2019 friday. All rights reserved.
//

#include "imageFix.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/photo/photo.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

Mat img,inpaintMask;
Point prevPt(-1, -1);

char *filePath = "/Users/friday/Desktop/abc/fix.jpg";

void onMouse(int event, int x, int y, int flags, void* userdata)
{
    if (event == EVENT_LBUTTONUP || !(flags & EVENT_FLAG_LBUTTON))
        prevPt = Point(-1, -1);
    else if (event == EVENT_LBUTTONDOWN)
        prevPt = Point(x, y);
    else if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON))
    {
        Point pt(x, y);
        if (prevPt.x < 0)
            prevPt = pt;
        line(inpaintMask, prevPt, pt, Scalar::all(255), 5, 8, 0);//mask
        line(img, prevPt, pt, Scalar::all(255), 5, 8, 0);
        prevPt = pt;
        imshow("image", img);
    }
}
void printType()
{
    cout<<"CV_8UC1::"<<CV_8UC1<<endl;
    cout<<"CV_8UC2:"<<CV_8UC2<<endl;
    cout<<"CV_8UC3:"<<CV_8UC3<<endl;
    cout<<"CV_8UC4:"<<CV_8UC4<<endl;
    cout<<"CV_8SC1::"<<CV_8SC1<<endl;
    cout<<"CV_8SC2:"<<CV_8SC2<<endl;
    cout<<"CV_8SC3:"<<CV_8SC3<<endl;
    cout<<"CV_8SC4:"<<CV_8SC4<<endl;
    cout<<"CV_16UC1::"<<CV_16UC1<<endl;
    cout<<"CV_16UC2:"<<CV_16UC2<<endl;
    cout<<"CV_16UC3:"<<CV_16UC3<<endl;
    cout<<"CV_16UC4:"<<CV_16UC4<<endl;
    cout<<"CV_16SC1::"<<CV_16SC1<<endl;
    cout<<"CV_16SC2:"<<CV_16SC2<<endl;
    cout<<"CV_16SC3:"<<CV_16SC3<<endl;
    cout<<"CV_16SC4:"<<CV_16SC4<<endl;
    cout<<"CV_32SC1::"<<CV_32SC1<<endl;
    cout<<"CV_32SC2:"<<CV_32SC2<<endl;
    cout<<"CV_32SC3:"<<CV_32SC3<<endl;
    cout<<"CV_32SC4:"<<CV_32SC4<<endl;
    cout<<"CV_32FC1::"<<CV_32FC1<<endl;
    cout<<"CV_32FC2:"<<CV_32FC2<<endl;
    cout<<"CV_32FC3:"<<CV_32FC3<<endl;
    cout<<"CV_32FC4:"<<CV_32FC4<<endl;
    cout<<"CV_64FC1::"<<CV_64FC1<<endl;
    cout<<"CV_64FC2:"<<CV_64FC2<<endl;
    cout<<"CV_64FC3:"<<CV_64FC3<<endl;
    cout<<"CV_64FC4:"<<CV_64FC4<<endl;

}



int main()
{
    Mat img0 = imread(filePath,-1);
    if (img0.empty()) {
        cout<<"不能打开图片"<<filePath<<"."<<endl;
        return 0;
    }
    
    
    namedWindow("image",1);
    printType();
    
    
    img0.convertTo(img, CV_8U);
    cout<<"img.type:"<<img.type()<<endl;
    

    cout<<CV_MAT_TYPE(img.type())<<endl;
    inpaintMask = Mat::zeros(img.size(), CV_8U);
    imshow("image", img);
    setMouseCallback("image", onMouse,0);
    
    
    while (1) {
        char c = (char)waitKey();
        if (c == 27) {
            break;
        }
        if (c == 'r') {
            inpaintMask = Scalar::all(0);
            img0.copyTo(img);
            imshow("image", img);
        }
        if (c=='i'||c==' ') {
            Mat inpainted;
            inpaint(img,inpaintMask,inpainted,3,INPAINT_TELEA);
            imshow("inpainted image", inpainted);
        }
    }
    return 0;
}
