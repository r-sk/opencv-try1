//Scan the 1920x1080 image in color and change the value of each pixel by two methods and calculate time for each

#include <opencv2/highgui.hpp>
#include <iostream>

int main(int argc, char **argv)
{
    cv::Mat o_image;  

    o_image = cv::imread("1080p.jpg", cv::IMREAD_COLOR);
    if (!o_image.data)
    {
        std::cout << "Could not open or find the image" << std::endl;
        return -1;
    }

    cv::Mat image1 = o_image.clone();

    int row = image1.rows;
    int col = image1.cols;

    /////////////////////////////////////////////////////////////////////////////////
    //The efficient way(classical way) starts here

    double t = (double)cv::getTickCount();

    for (int r = 0; r < row; r++)
    for (int c = 0; c < col; c++)
    for (uint8_t ch = 0; ch < 3; ch++)
        image1.at<cv::Vec3b>(r, c)[ch] /= 2; //Decrease the intensity by 2

    t = ( (double)cv::getTickCount() - t )/ cv::getTickFrequency();
    t *= 1000; 

    ////////////////////////////////////////////////////////////////////////////////

    //Display original image
    cv::namedWindow("Display window2", cv::WINDOW_NORMAL);
    cv::imshow("Display window2", o_image);
    
    //Display image with reduced intensity
    cv::namedWindow("Display window", cv::WINDOW_NORMAL);
    cv::imshow("Display window", image1);

    

    std::cout << t << std::endl;

    cv::waitKey(0);     //Wait until key is pressed
    return 0;
}