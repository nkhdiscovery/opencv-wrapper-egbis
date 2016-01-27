/*
Copyright (C) 2015 Yasutomo Kawanishi
Copyright (C) 2013 Christoffer Holmstedt
Copyright (C) 2010 Salik Syed
Copyright (C) 2006 Pedro Felzenszwalb

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
*/

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "nkhUtil.h"
//#include "egbis.h"
#include "egbiscv.h"


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "egbiscv.h"

using namespace cv;
using namespace std;

#define SCALE_FACTOR 1.5

Mat egbisImage;
Mat img;
char* imageName;
int num_ccs;
void nkhSeg(Ptr<GraphSegmentationImpl> segPtr, cv::Mat& img, cv::Mat& egbisSeg)
{
    segPtr->processImage(img, egbisSeg);
}

int main(int argc, char **argv) {

    img = imread( argv[1], CV_LOAD_IMAGE_COLOR );

    float sigma = atof(argv[2]);
    float k = atof(argv[3]);
    int min_size = atoi(argv[4]);
    if( !img.data )
    {
        cout << "Could not open or find the image." << std::endl;
        return -1;
    }
    // 4. Present image
    cv::Mat edgeImg, grayImg;
    resize(img, img, Size(img.size().width/SCALE_FACTOR,
                          img.size().height/SCALE_FACTOR));
    cvtColor(img, grayImg, COLOR_BGR2GRAY);
    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;

    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;
    /// Gradient X
    //Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
    Sobel( img, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_x, abs_grad_x );
    /// Gradient Y
    //Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
    Sobel( img, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_y, abs_grad_y );

    /// Total Gradient (approximate)
    addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, edgeImg );

    imshow( "imageName" , edgeImg );
    imshow( "Orig" , img );
    cout << k << " , " << min_size << endl ;

//    egbisImage = measure<chrono::milliseconds>(runEgbisOnMat, img, edgeImg, sigma, k, min_size, &num_ccs);
    cv::Mat egbisSeg;
    Ptr<GraphSegmentationImpl> segPtr = createGraphSegmentation(sigma, k, min_size);
    measure<chrono::milliseconds>(nkhSeg, segPtr, img, egbisSeg);
    measure<chrono::milliseconds>(egbisVisualise, egbisSeg, egbisImage);

    // Change image shown
    imshow( "EGBIS", egbisImage);

    waitKey(0);

    return 0;
}
