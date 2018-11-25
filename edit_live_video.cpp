#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

char string1[] = "Smooth Type:\n 0: Normal Blur\n 1: Gaussian Blur\n 2: Medial Blur\n 3: Bilateral Filter";
int smooth_type = 0;
int max_type = 3;

char string2[] = "Maximum Kernel size";
int kernel_size = 0;
int max_kernel_size = 20;

cv::Mat vsrc,src,dest;
cv::VideoCapture vid(0);

int fps = 20;

void display(int mode, int max_kernel);

int main(int argc, char **argv)
{
    cv::namedWindow("Smoothing Live Video", cv::WINDOW_NORMAL);

    cv::createTrackbar(string1, "Smoothing Live Video", &smooth_type, max_type);

    cv::createTrackbar(string2, "Smoothing Live Video", &kernel_size, max_kernel_size);


    if(!vid.isOpened()) return -1;

    while (vid.read(vsrc))
    {
        display(smooth_type,kernel_size);
        if (cv::waitKey(1000 / fps) >= 0)
            break;
    }

    return 0;
}

void display(int mode, int max_kernel)
{
    cv::cvtColor(vsrc,src, cv::COLOR_BGR2GRAY);

    if (max_kernel >= 3)
    {
        switch (mode)
        {
        case 0:
            for (int i = 1; i < max_kernel; i += 2)
                blur(src, dest, cv::Size(i, i), cv::Point(-1, -1));
            cv::imshow("Smoothing Live Video", dest);
            std::cout << "Normal Box Blur Shown" << std::endl;
        break;

        case 1:
            for (int i = 1; i < max_kernel; i += 2)
                GaussianBlur(src, dest, cv::Size(i, i), 0, 0);
            cv::imshow("Smoothing Live Video", dest);
            std::cout << "Gaussian Blur Shown" << std::endl;
        break;

        case 2:
            for (int i = 1; i < max_kernel; i += 2)
                medianBlur(src, dest, i);
            cv::imshow("Smoothing Live Video", dest);
            std::cout << "Median Blur Shown" << std::endl;
        break;

        case 3:
            for (int i = 1; i < max_kernel; i += 2)
                bilateralFilter(src, dest, i, i * 2, i / 2);
            cv::imshow("Smoothing Live Video", dest);
            std::cout << "Bilateral Filter Shown" << std::endl;
        break;
        }
    }

    else
    {
        cv::imshow("Smoothing Live Video", src);
    }
}