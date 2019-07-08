//
//  ViewController.m
//  iOS_FixImage
//
//  Created by friday on 2019/7/8.
//  Copyright © 2019 friday. All rights reserved.
//

#import "RootViewController.h"
#include <opencv2/opencv.hpp>


#include <opencv2/opencv.hpp>
#include <opencv2/photo/photo.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/ios.h>

using namespace cv;
using namespace std;


//Point prevPt(-1, -1);

char *filePath = "/Users/friday/Desktop/abc/fix.jpg";

void onMouse(int event, int x, int y, int flags, void* userdata)
{
//    if (event == EVENT_LBUTTONUP || !(flags & EVENT_FLAG_LBUTTON))
//        prevPt = Point(-1, -1);
//    else if (event == EVENT_LBUTTONDOWN)
//        prevPt = Point(x, y);
//    else if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON))
//    {
//        Point pt(x, y);
//        if (prevPt.x < 0)
//            prevPt = pt;
//        line(inpaintMask, prevPt, pt, Scalar::all(255), 5, 8, 0);//mask
//        line(img, prevPt, pt, Scalar::all(255), 5, 8, 0);
//        prevPt = pt;
//        imshow("image", img);
//    }
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



int opencv_main(RootViewController*root)
{
    
    
    
//    while (1) {
//        char c = (char)waitKey();
//        if (c == 27) {
//            break;
//        }
//        if (c == 'r') {
//            inpaintMask = Scalar::all(0);
//            img0.copyTo(img);
//            imshow("image", img);
//        }
//        if (c=='i'||c==' ') {
//            Mat inpainted;
//            inpaint(img,inpaintMask,inpainted,3,INPAINT_TELEA);
//            imshow("inpainted image", inpainted);
//        }
//    }
    return 0;
}

typedef UIImageView* BFImageView;
typedef UIButton* BFButton;

@interface RootViewController ()<UIGestureRecognizerDelegate>
{
    BFImageView imageView ,imageViewShow;
    Point2i prevPt;
    Mat img,inpaintMask;
    UIPanGestureRecognizer *pan;
    BFButton showButton;
    
    UIButton *button;
    
    CGFloat width;
    CGFloat height;
    
    CGFloat dstWidth;
    CGFloat dstHeight;
    
}
@end

@implementation RootViewController


-(void)ShowImage:(Mat)img
{
    
    imageView.image = MatToUIImage(img);
    
}

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor whiteColor];
    prevPt.x = -1;
    prevPt.y = -1;
    
    CGRect frame = self.view.bounds;
    frame.size.height -= 50;
    frame.size.height /= 2.0;
    
    dstWidth = frame.size.width;
    dstHeight= frame.size.height;
    
    imageView = [[UIImageView alloc]initWithFrame:frame];
    imageView.contentMode = UIViewContentModeScaleToFill;
    [self.view addSubview:imageView];
    //
    imageViewShow = [[UIImageView alloc]initWithFrame:CGRectMake(0, CGRectGetMaxY(frame), CGRectGetWidth(frame), CGRectGetHeight(frame))];
    [self.view addSubview:imageViewShow];
    imageView.userInteractionEnabled = YES;
    imageViewShow.userInteractionEnabled = YES;
    frame = imageViewShow.frame;
    showButton = [UIButton buttonWithType:UIButtonTypeCustom];
    [showButton setTitle:@"图片完成" forState:UIControlStateNormal];
    showButton.frame = CGRectMake(0, CGRectGetMaxY(frame), CGRectGetWidth(frame), 50);
    [showButton addTarget:self action:@selector(ShowImg:) forControlEvents:UIControlEventTouchUpInside];
    [showButton setTitleColor:[UIColor blueColor] forState:UIControlStateNormal];
    [self.view addSubview:showButton];
    

    
    pan = [[UIPanGestureRecognizer alloc]initWithTarget:self action:@selector(Pan:)];
    [imageView addGestureRecognizer:pan];
    NSLog(@"%@",[[NSFileManager defaultManager] currentDirectoryPath]);
    [[NSFileManager defaultManager] changeCurrentDirectoryPath:[NSBundle mainBundle].bundlePath];
    NSLog(@"%@",[[NSFileManager defaultManager] currentDirectoryPath]);
    perror("文件路径");
    [self StartFixImage:"fix.jpg"];
    // Do any additional setup after loading the view.
}
-(void)ShowImg:(UIButton*)sender
{
    Mat inpainted;
    inpaint(img,inpaintMask,inpainted,3,INPAINT_TELEA);
    imageViewShow.image = MatToUIImage(inpainted);
}
static int lineWidth = 20;

-(void)Pan:(UIPanGestureRecognizer*)ges
{
    switch (ges.state) {
        case UIGestureRecognizerStateBegan:
        {
            CGPoint pt1 = [ges locationInView:imageView];
            prevPt.x = (pt1.x/dstWidth)*width;
            prevPt.y = (pt1.y/dstHeight)*height;
        }
            break;
        case UIGestureRecognizerStateChanged:
        {
            CGPoint pt1 = [ges locationInView:imageView];
            Point2i pt;
            pt.x = (pt1.x/dstWidth)*width;
            pt.y = (pt1.y/dstHeight)*height;
            
            
            
            line(inpaintMask, prevPt, pt, Scalar::all(255), lineWidth, 8, 0);//mask
            line(img, prevPt, pt, Scalar::all(255), lineWidth, 8, 0);
            prevPt.x = pt.x;
            prevPt.y = pt.y;

            [self ShowImage:img];
        }
            break;
        case UIGestureRecognizerStateEnded:
        {
            prevPt.x = -1;
            prevPt.y = -1;
        }
            break;
        case UIGestureRecognizerStateCancelled:
        {
            prevPt.x = -1;
            prevPt.y = -1;
        }
            break;
        default:
            break;
    }
}


-(void)StartFixImage:(char*)filePath
{
    Mat img0 = imread(filePath,-1);
    if (img0.empty()) {
        cout<<"不能打开图片"<<filePath<<"."<<endl;
        return;
    }
    
    
    printType();
    img = img0.clone();
    inpaintMask = Mat::zeros(img.size(), CV_8U);
    width = img.cols;
    height= img.rows;
    
    cvtColor(img, img, COLOR_BGR2RGB);
    //    imshow("image", img);
    [self ShowImage:img];
}





@end
