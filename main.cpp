//g++ main.cpp -o output `pkg-config --cflags --libs opencv`       is code to compile program
//#include <opencv/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

int main(int argc, char **argv)
{
    cv::Mat image;
    image = cv::imread("sample.png", cv::IMREAD_GRAYSCALE);

    if (!image.data)
    {
        std::cout << "Could not open or find the image" << std::endl;
        return -1;
    }

    cv::namedWindow("Display window", cv::WINDOW_NORMAL);
    cv::imshow("Display window", image);
    std::cout << image << std::endl;

    cv::waitKey(0);
    return 0;
}