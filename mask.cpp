//Mask operations on matrices (this sharpens the image)

#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp> //Contains image processing functions such as : filter2D , GaussianBlur and many more
#include <iostream>


int main(int argc, char **argv)
{
    cv::Mat image,sharp_image;
    image = cv::imread("paper.jpg", cv::IMREAD_GRAYSCALE);

    cv::Mat kernel = (cv::Mat_<char>(3, 3) <<   0, -2, 0,
                                                -2, 10, -2,
                                                 0, -2, 0   );  //Explicit creation of Mat object

    
    cv::filter2D( image, sharp_image, image.depth(), kernel );

    cv::namedWindow("Original Image", cv::WINDOW_NORMAL);
    cv::imshow("Original Image", image);

    cv::namedWindow("Sharp image", cv::WINDOW_NORMAL);
    cv::imshow("Sharp image", sharp_image);

    cv::waitKey(0);
                                     
    return 0;
}