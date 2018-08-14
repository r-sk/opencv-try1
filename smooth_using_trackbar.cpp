#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

char string1[] = "Smooth Type:\n 0: Normal Blur\n 1: Gaussian Blur\n 2: Medial Blur\n 3: Bilateral Filter";
int smooth_type = 0;
int max_type = 3;

char string2[] = "Maximum Kernel size";
int kernel_size = 0;
int max_kernal_size = 20;

cv::Mat src = cv::imread("lena.png", cv::IMREAD_GRAYSCALE);
cv::Mat dest = src.clone();

void trackbar1(int, void *);
void trackbar2(int, void *);
void display(int mode, int max_kernel);

int main(int argc, char **argv)
{

    cv::namedWindow("Image Smoothing using various filters", cv::WINDOW_NORMAL);

    cv::createTrackbar(string1, "Image Smoothing using various filters", &smooth_type, max_type, trackbar1);

    cv::createTrackbar(string2, "Image Smoothing using various filters", &kernel_size, max_kernal_size, trackbar2);

    cv::waitKey(0);
    return 0;
}

void trackbar1(int, void *)
{
    display(smooth_type, kernel_size);
}

void trackbar2(int, void *)
{
    display(smooth_type, kernel_size);
}

void display(int mode, int max_kernel)
{
    if (max_kernel >= 3)
    {
        switch (mode)
        {
        case 0:
            for (int i = 1; i < max_kernel; i += 2)
                blur(src, dest, cv::Size(i, i), cv::Point(-1, -1));
            cv::imshow("Image Smoothing using various filters", dest);
            std::cout << "Normal Box Blur Shown" << std::endl;
        break;

        case 1:
            for (int i = 1; i < max_kernel; i += 2)
                GaussianBlur(src, dest, cv::Size(i, i), 0, 0);
            cv::imshow("Image Smoothing using various filters", dest);
            std::cout << "Gaussian Blur Shown" << std::endl;
        break;

        case 2:
            for (int i = 1; i < max_kernel; i += 2)
                medianBlur(src, dest, i);
            cv::imshow("Image Smoothing using various filters", dest);
            std::cout << "Median Blur Shown" << std::endl;
        break;

        case 3:
            for (int i = 1; i < max_kernel; i += 2)
                bilateralFilter(src, dest, i, i * 2, i / 2);
            cv::imshow("Image Smoothing using various filters", dest);
            std::cout << "Bilateral Filter Shown" << std::endl;
        break;
        }
    }

    else
    {
        cv::imshow("Image Smoothing using various filters", src);
    }
}