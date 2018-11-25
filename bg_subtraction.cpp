#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

const cv::Scalar SCALAR_BLACK = cv::Scalar(0.0, 0.0, 0.0);
const cv::Scalar SCALAR_WHITE = cv::Scalar(255.0, 255.0, 255.0);

int main(int argc, char **argv)
{
    int fps = 20;
    cv::VideoCapture vid(1);

    cv::Mat imgFrame1;
    cv::Mat imgFrame2;

    cv::Mat imgFrame1Copy;
    cv::Mat imgFrame2Copy;

    cv::Mat imgDifference;
    cv::Mat imgThresh;
    cv::Mat imgThreshCopy;

    cv::Mat structuringElement3x3 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::Mat structuringElement5x5 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::Mat structuringElement7x7 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7));
    cv::Mat structuringElement9x9 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(9, 9));

    std::vector<std::vector<cv::Point> > contours;

    cv::namedWindow("After Threshold", cv::WINDOW_NORMAL);
    cv::namedWindow("After Contour", cv::WINDOW_NORMAL);

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

        cv::dilate(imgThresh, imgThresh, structuringElement5x5);
        cv::dilate(imgThresh, imgThresh, structuringElement5x5);
        cv::erode(imgThresh, imgThresh, structuringElement5x5);

        cv::imshow("After Threshold", imgThresh);

        cv::Mat imgThreshCopy = imgThresh.clone();

        cv::findContours(imgThreshCopy, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        cv::Mat imgContours(imgThresh.size(), CV_8UC3, SCALAR_BLACK);

        cv::drawContours(imgContours, contours, -1, SCALAR_WHITE, -1);

        cv::imshow("After Contour", imgContours);

        std::vector<std::vector<cv::Point> > convexHulls(contours.size());



        if (cv::waitKey(1000 / fps) >= 0)
            break;
    }
}