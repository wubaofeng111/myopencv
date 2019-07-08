//
//  main.cpp
//  opencv_face
//
//  Created by friday on 2019/7/1.
//  Copyright © 2019 friday. All rights reserved.
//
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <dlfcn.h>

using namespace cv;
using namespace std;
using namespace cv::face;

RNG g_rng(12345);
Ptr<FaceRecognizer> model;
int Predict(Mat src_image)
{
    Mat face_test;
    int predict = 0;
    //截取的ROI人脸尺寸调整
    if (src_image.rows >= 120)
    {
        //改变图像大小，使用双线性差值
        resize(src_image, face_test, Size(92, 112));
    }
    //判断是否正确检测ROI
    if (!face_test.empty())
    {
        //测试图像应该是灰度图
        predict = model->predict(face_test);
    }
    cout << predict << endl;
    return predict;
    
}

int fmain()
{
    VideoCapture cap(0);    //打开默认摄像头
    if (!cap.isOpened())
    {
        return -1;
    }
    Mat frame;
    Mat gray;
    //这个分类器是人脸检测所用
    CascadeClassifier cascade;
    bool stop = false;
    //训练好的文件名称，放置在可执行文件同目录下
    cascade.load("haarcascade_frontalface_alt2.xml");//感觉用lbpcascade_frontalface效果没有它好，注意哈！要是正脸
    
    model = FisherFaceRecognizer::create();
    //1.加载训练好的分类器
    model->read("MyFaceFisherModel.xml");// opencv2用load
    //3.利用摄像头采集人脸并识别
    while (1)
    {
        cap >> frame;
        
        vector<Rect> faces(0);//建立用于存放人脸的向量容器
        
        cvtColor(frame, gray, COLOR_RGB2GRAY);//测试图像必须为灰度图
        
        equalizeHist(gray, gray); //变换后的图像进行直方图均值化处理
        //检测人脸
        cascade.detectMultiScale(gray, faces,
                                 1.1, 4, 0
                                 //|CV_HAAR_FIND_BIGGEST_OBJECT
                                 | CASCADE_DO_ROUGH_SEARCH,
                                 //| CV_HAAR_SCALE_IMAGE,
                                 Size(30, 30), Size(500, 500));
        Mat* pImage_roi = new Mat[faces.size()];    //定以数组
        Mat face;
        Point text_lb;//文本写在的位置
        //框出人脸
        string str;
        for (int i = 0; i < faces.size(); i++)
        {
            pImage_roi[i] = gray(faces[i]); //将所有的脸部保存起来
            text_lb = Point(faces[i].x, faces[i].y);
            if (pImage_roi[i].empty())
                continue;
            switch (Predict(pImage_roi[i])) //对每张脸都识别
            {
                case 41:str = "HuangHaiNa"; break;
                case 42:str = "XuHaoRan"; break;
                case 43:str = "HuangLuYao"; break;
                default: str = "Error1"; break;
            }
            Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));//所取的颜色任意值
            rectangle(frame, Point(faces[i].x, faces[i].y), Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height), color, 1, 8);//放入缓存
            putText(frame, str, text_lb, FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255));//添加文字
        }
        
        delete[]pImage_roi;
        imshow("face", frame);
        waitKey(200);
    }
    
    return 0;
   
}


int main()
{
    system("pwd");
    fmain();
    waitKey();

    return 0;
}

