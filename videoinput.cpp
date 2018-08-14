#include <opencv2/highgui.hpp>
#include <iostream>

int fps = 20;

int main(int argc, char **argv)
{
    cv::Mat frame;

    cv::VideoCapture vid(0);

    if(!vid.isOpened()) return -1;

    cv::namedWindow("webcam", cv::WINDOW_NORMAL);

    while (vid.read(frame))
    {
        cv::imshow("webcam", frame);
        if (cv::waitKey(1000 / fps) >= 0)
            break;
    }

    return 0;
}