#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include "opencv2/imgcodecs.hpp"

#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <iostream>


int main(int argc, char **argv)
{
    cv::Mat frame, mask, gray;


    cv::VideoCapture vid(0);

    cv::BackgroundSubtractorMOG2 mog;

    if (vid.isOpened())
    {

        while (true)
        {

            if (vid.read(frame))
            {

                imshow("frame", frame);

                cvtColor(frame, gray, cv::COLOR_RGB2GRAY);
                imshow("gray", gray);
                mog(gray, mask, 0.0); // 0.1 is learning rate
                imshow("Background Subtraction", mask);

                if (cv::waitKey(30) >= 0)
                    break;
            }
        }
    }
    vid.release();
    return 0;
}