#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int max_kernel = 10;

int main(int argc, char **argv)
{
    cv::Mat src = cv::imread("lena.png", cv::IMREAD_GRAYSCALE);
    cv::Mat dest = src.clone();
    cv::Mat gaussian = src.clone();
    cv::Mat median = src.clone();
    cv::Mat bilateral = src.clone();


    for (int i = 1; i < max_kernel; i+=2)
        cv::blur(src, dest, cv::Size(i, i), cv::Point(-1, -1));

    for (int i = 1; i < max_kernel; i+=2)
        GaussianBlur( src, gaussian, cv::Size( i, i ), 0, 0 );

    for (int i = 1; i < max_kernel; i+=2)
        medianBlur ( src, median , i );

    for (int i = 1; i < max_kernel; i+=2)
        bilateralFilter ( src, bilateral, i, i*2, i/2 );

    cv::namedWindow("Original Image", cv::WINDOW_NORMAL);
    cv::imshow("Original Image", src);

    cv::namedWindow("simple blur", cv::WINDOW_NORMAL);
    cv::imshow("simple blur", dest);

    cv::namedWindow("Gaussian blur", cv::WINDOW_NORMAL);
    cv::imshow("Gaussian blur", gaussian);

    cv::namedWindow("Median blur", cv::WINDOW_NORMAL);
    cv::imshow("Median blur", median);

    cv::namedWindow("Bilateral blur", cv::WINDOW_NORMAL);
    cv::imshow("Bilateral blur", bilateral);

    cv::waitKey(0);

    return 0;
}