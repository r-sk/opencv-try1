//Scan the 1920x1080 image in color and change the value of each pixel by two methods and calculate time for each
//But unfortunately LUT method is not working hai 

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
    cv::Mat image2 = o_image.clone();

    int row = image1.rows;
    int col = image1.cols;

    /////////////////////////////////////////////////////////////////////////////////
    //The efficient way(classical way)

    double t1 = (double)cv::getTickCount();  //Time measurement

    for (int r = 0; r < row; r++)
    for (int c = 0; c < col; c++)
    for (uint8_t ch = 0; ch < 3; ch++)
        image1.at<cv::Vec3b>(r, c)[ch] /= 2; //Decrease the intensity by 2

    t1 = ( (double)cv::getTickCount() - t1 )/ cv::getTickFrequency();
    t1 *= 1000; 

    ////////////////////////////////////////////////////////////////////////////////


    cv::Mat lookUpTable(1920, 1080, CV_8UC3, cv::Scalar::all(255));

    // uchar* p = lookUpTable.ptr();
    //     for( int i = 0; i < 40; ++i)

    //std::cout << lookUpTable << std::endl;

    cv::LUT(o_image, image1, image2);


    //Display original image
    cv::namedWindow("Display window2", cv::WINDOW_NORMAL);
    cv::imshow("Display window2", o_image);

    //Display image with reduced intensity
    cv::namedWindow("Display window", cv::WINDOW_NORMAL);
    cv::imshow("Display window", image1);

    //Display image2
    cv::namedWindow("Image 2", cv::WINDOW_NORMAL);
    cv::imshow("Image 2", image2);

    

    std::cout << "Execution time(classical method): " << t1 << "ms" << std::endl;

    cv::waitKey(0);     //Wait until key is pressed
    return 0;
}