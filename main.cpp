//Scan the image in grayscale and change the value of each pixel(Invert Image)

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

    cv::Mat o_image = image.clone();

    int row = image.rows;
    int col = image.cols;

    for (int r = 0; r < row; r++)
    for (int c = 0; c < col; c++)
    {
        image.at<uint8_t>(r,c) = 255-image.at<uint8_t>(r,c);    //Invert the image
    }

    //Display image with reduced intensity
    cv::namedWindow("Display window", cv::WINDOW_NORMAL);
    cv::imshow("Display window", image);

    //Display original image
    cv::namedWindow("Display window2", cv::WINDOW_NORMAL);
    cv::imshow("Display window2", o_image);

    std::cout << image << std::endl;
    std::cout << o_image << std::endl;

    cv::waitKey(0);     //Wait until key is pressed
    return 0;
}