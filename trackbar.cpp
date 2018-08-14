#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

int var = 0;
int max_var = 10;

char ch[] = "Variable value";


void trackbar_fucntion(int, void*);

int main(int argc, char **argv)
{
    cv::namedWindow("Trackbar Demo", cv::WINDOW_NORMAL);
    cv::createTrackbar(ch, "Trackbar Demo", &var, max_var, trackbar_fucntion);

    // OR SIMPLY DO ==  cv::createTrackbar("Variable value", "Trackbar Demo", &var, max_var, trackbar_fucntion);

    std::cout << "Rashik " << std::endl; 
    
    cv::waitKey(0); //Wait until key is pressed
    return 0;
}

void trackbar_fucntion(int, void*)      //This function is called everytime the trakerbar is slided
{
    std::cout << var << std::endl;
}