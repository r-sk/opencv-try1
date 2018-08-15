#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

int main(int argc, char **argv)
{
    int fps = 20;
    cv::VideoCapture vid(0);

    cv::Mat imgFrame1;
    cv::Mat imgFrame2;

    cv::Mat imgFrame1Copy;
    cv::Mat imgFrame2Copy;

    cv::Mat imgDifference;
    cv::Mat imgThresh;

    cv::namedWindow("Background Subtraction", cv::WINDOW_NORMAL);

    if (!vid.isOpened())
        return -1;

    while (vid.read(imgFrame1))
    {
        vid.read(imgFrame1);
        vid.read(imgFrame2);

        imgFrame1Copy = imgFrame1.clone();
        imgFrame2Copy = imgFrame2.clone();

        cv::cvtColor(imgFrame1Copy, imgFrame1Copy, cv::COLOR_BGR2GRAY);
        cv::cvtColor(imgFrame2Copy, imgFrame2Copy, cv::COLOR_BGR2GRAY);

        cv::GaussianBlur(imgFrame1Copy, imgFrame1Copy, cv::Size(5, 5), 0);
        cv::GaussianBlur(imgFrame2Copy, imgFrame2Copy, cv::Size(5, 5), 0);

        cv::absdiff(imgFrame1Copy, imgFrame2Copy, imgDifference);

        cv::threshold(imgDifference, imgThresh, 30, 255.0, cv::THRESH_BINARY);

        cv::imshow("Background Subtraction", imgThresh);

        if (cv::waitKey(1000 / fps) >= 0)
            break;
    }
}