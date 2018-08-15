#include <opencv2/opencv.hpp> //SimpleBlobDetector yesma raixa feri
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

//VARIABLES DECLATARIONS:
cv::Mat vsrc,src;
cv::Mat src_with_keypoints;
cv::VideoCapture vid(1);
int fps = 20;
cv::SimpleBlobDetector::Params params; // Setup SimpleBlobDetector parameters.
std::vector<cv::KeyPoint> keypoints;   //Storage for Blobs
cv::Ptr<cv::SimpleBlobDetector> detector = cv::SimpleBlobDetector::create(params); // Set up detector with params

int minThreshold = 10;
int max_minThreshold = 255;

int maxThreshold = 250;
int max_maxThreshold = 255;

int minArea = 150;
int max_minArea = 3000;

int minCircularity = 10; //In percentage
int max_minCircularity = 100;

int minConvexity = 87; //In percentage
int max_minConvexity = 100;

int minInertiaRatio = 1; //In percentage
int max_minInertiaRatio = 100;



//FUNCTION DECLARATIONS:
void update_blob_parameters();




int main(int argc, char **argv)
{

    cv::namedWindow("Live Blob Analysis", cv::WINDOW_NORMAL);
    cv::createTrackbar("Min. Threshold", "Live Blob Analysis", &minThreshold, max_minThreshold);
    cv::createTrackbar("Max. Threshold", "Live Blob Analysis", &maxThreshold, max_maxThreshold);
    cv::createTrackbar("Min. Area\n(0 = OFF)", "Live Blob Analysis", &minArea, max_minArea);
    cv::createTrackbar("Max. Circularity(%)\n(0 = OFF)", "Live Blob Analysis", &minCircularity, max_minCircularity);
    cv::createTrackbar("Min. Convexity(%)\n(0 = OFF)", "Live Blob Analysis", &minConvexity, max_minConvexity);
    cv::createTrackbar("Max. Inertia Ratio(%)\n(0 = OFF)", "Live Blob Analysis", &minInertiaRatio, max_minInertiaRatio);

    if (!vid.isOpened())
        return -1;

    while (vid.read(vsrc))
    {
        cv::cvtColor(vsrc,src, cv::COLOR_BGR2GRAY);
        update_blob_parameters();
        detector = cv::SimpleBlobDetector::create(params);
        detector->detect(src, keypoints);
        cv::drawKeypoints(src, keypoints, src_with_keypoints, cv::Scalar(0, 0, 255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
        cv::imshow("Live Blob Analysis", src_with_keypoints);

        if (cv::waitKey(1000 / fps) >= 0)
            break;
    }

    
}

void update_blob_parameters()
{
    // Change thresholds
    params.minThreshold = minThreshold;
    params.maxThreshold = maxThreshold;

    // Filter by Area.
    (minArea == 0) ? params.filterByArea = false : params.filterByArea = true;
    params.minArea = minArea;

    // Filter by Circularity
    (minCircularity == 0) ? params.filterByCircularity = false : params.filterByCircularity = true;
    params.minCircularity = minCircularity / 100;

    // Filter by Convexity
    (minConvexity == 0) ? params.filterByConvexity = false : params.filterByConvexity = true;
    params.minConvexity = minConvexity / 100;

    // Filter by Inertia
    (minInertiaRatio == 0) ? params.filterByInertia = false : params.filterByInertia = true;
    params.minInertiaRatio = minInertiaRatio / 100;

}