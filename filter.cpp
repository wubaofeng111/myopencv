//
//  filter.cpp
//  myopencv
//
//  Created by friday on 2019/7/8.
//  Copyright © 2019 friday. All rights reserved.
//

#include "filter.hpp"

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;


void casting()
{
    Mat src = imread("/Users/friday/Desktop/abc/20130617230432390.jpg",1);
    Mat img;
    src.copyTo(img);
    int width=src.cols;
    int heigh=src.rows;
    Mat dst(img.size(),CV_8UC3);
    for (int y=0;y<heigh;y++)
    {
        uchar* imgP=img.ptr<uchar>(y);
        uchar* dstP=dst.ptr<uchar>(y);
        for (int x=0;x<width;x++)
        {
            float b0=imgP[3*x];
            float g0=imgP[3*x+1];
            float r0=imgP[3*x+2];
            
            float b = b0*255/(g0+r0+1);
            float g = g0*255/(b0+r0+1);
            float r = r0*255/(g0+b0+1);
            
            r = (r>255 ? 255 : (r<0? 0 : r));
            g = (g>255 ? 255 : (g<0? 0 : g));
            b = (b>255 ? 255 : (b<0? 0 : b));
            
            dstP[3*x] = (uchar)b;
            dstP[3*x+1] = (uchar)g;
            dstP[3*x+2] = (uchar)r;
        }
    }
    imshow("熔铸",dst);
    imwrite("/Users/friday/Desktop/abc/熔铸.jpg",dst);
    
}

void freezing()
{
    Mat src = imread("/Users/friday/Desktop/abc/20130617230432390.jpg",1);
    Mat img;
    src.copyTo(img);
    int width=src.cols;
    int heigh=src.rows;
    Mat dst(img.size(),CV_8UC3);
    for (int y=0;y<heigh;y++)
    {
        uchar* imgP=img.ptr<uchar>(y);
        uchar* dstP=dst.ptr<uchar>(y);
        for (int x=0;x<width;x++)
        {
            float b0=imgP[3*x];
            float g0=imgP[3*x+1];
            float r0=imgP[3*x+2];
            
            float b = (b0-g0-r0)*3/2;
            float g = (g0-b0-r0)*3/2;
            float r = (r0-g0-b0)*3/2;
            
            r = (r>255 ? 255 : (r<0? -r : r));
            g = (g>255 ? 255 : (g<0? -g : g));
            b = (b>255 ? 255 : (b<0? -b : b));
            //             r = (r>255 ? 255 : (r<0? 0 : r));
            //             g = (g>255 ? 255 : (g<0? 0 : g));
            //             b = (b>255 ? 255 : (b<0? 0 : b));
            dstP[3*x] = (uchar)b;
            dstP[3*x+1] = (uchar)g;
            dstP[3*x+2] = (uchar)r;
        }
    }
    imwrite("/Users/friday/Desktop/abc/冰冻.jpg",dst);
}




void lianhuanhua()
{
    Mat src = imread("/Users/friday/Desktop/abc/20130617230432390.jpg",1);
    int width=src.cols;
    int heigh=src.rows;
    RNG rng;
    Mat img(src.size(),CV_8UC3);
    for (int y=0; y<heigh; y++)
    {
        uchar* P0  = src.ptr<uchar>(y);
        uchar* P1  = img.ptr<uchar>(y);
        for (int x=0; x<width; x++)
        {
            float B=P0[3*x];
            float G=P0[3*x+1];
            float R=P0[3*x+2];
            float newB=abs(B-G+B+R)*G/256;
            float newG=abs(B-G+B+R)*R/256;
            float newR=abs(G-B+G+R)*R/256;
            if(newB<0)newB=0;
            if(newB>255)newB=255;
            if(newG<0)newG=0;
            if(newG>255)newG=255;
            if(newR<0)newR=0;
            if(newR>255)newR=255;
            P1[3*x] = (uchar)newB;
            P1[3*x+1] = (uchar)newG;
            P1[3*x+2] = (uchar)newR;
        }
        
    }
    Mat gray;
    cvtColor(img,gray,COLOR_BGR2GRAY);
    normalize(gray,gray,255,0,NORM_MINMAX);
    imshow("连环画",gray);
    waitKey();
    imwrite("/Users/friday/Desktop/abc/连环画.jpg",gray);
}

void huaijiu()
{
    Mat src = imread("/Users/friday/Desktop/abc/20130617230432390.jpg",1);
    int width=src.cols;
    int heigh=src.rows;
    RNG rng;
    Mat img(src.size(),CV_8UC3);
    for (int y=0; y<heigh; y++)
    {
        uchar* P0  = src.ptr<uchar>(y);
        uchar* P1  = img.ptr<uchar>(y);
        for (int x=0; x<width; x++)
        {
            float B=P0[3*x];
            float G=P0[3*x+1];
            float R=P0[3*x+2];
            float newB=0.272*R+0.534*G+0.131*B;
            float newG=0.349*R+0.686*G+0.168*B;
            float newR=0.393*R+0.769*G+0.189*B;
            if(newB<0)newB=0;
            if(newB>255)newB=255;
            if(newG<0)newG=0;
            if(newG>255)newG=255;
            if(newR<0)newR=0;
            if(newR>255)newR=255;
            P1[3*x] = (uchar)newB;
            P1[3*x+1] = (uchar)newG;
            P1[3*x+2] = (uchar)newR;
        }
        
    }
    imshow("怀旧色",img);
    waitKey();
    imwrite("/Users/friday/Desktop/abc/怀旧色.jpg",img);
}

void imageShowMany()
{
    
    vector<Mat> images(4);
    images[0] = imread("/Users/friday/Desktop/abc/20130617230432390.jpg");
    images[1] = imread("/Users/friday/Desktop/abc/怀旧色.jpg");
    images[2] = imread("/Users/friday/Desktop/abc/冰冻.jpg");
    images[3] = imread("/Users/friday/Desktop/abc/熔铸.jpg");
    
    Mat display;
    display.create(1240, 1240, CV_8UC3);
    Size size;
    size.width = 620;
    size.height = 620;
    
    cout<<display.rows<<endl;
    cout<<display.cols<<endl;
    
    for(int i = 0;i<4;i++)
    {
        Mat dst = Mat::zeros(620, 620, CV_8UC3);
        resize(images.at(i), dst, dst.size());
        
        cout<<dst.rows<<endl;
        cout<<dst.cols<<endl;
        
        int imgRow = i % 2;
        int imgCol = i / 2;
        
        for (int row = 0; row < 620; row++) {
            for (int col = 0; col < 620 ; col++) {
                display.at<Vec3b>(imgRow*620+row,imgCol*620+col) = dst.at<Vec3b>(row,col);
            }
        }
    }

    
    imshow("合成图片", display);
    imwrite("/Users/friday/Desktop/abc/图片合成.png", display);
    
    waitKey();
}


int main()
{
//    huaijiu();
//    lianhuanhua();
//    casting();
//    freezing();
    imageShowMany();
    
    
    return 0;
}

