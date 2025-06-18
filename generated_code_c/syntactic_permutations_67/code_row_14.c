/*
 * Simple image processor using OpenCV.
 * Author: @Bhupesh-V
 * Date: 15/06/2021
 * Language: C
 */

// Importing necessary libraries.
#include <stdio.h>
#include <opencv.h>

int main() {
    // Creating a Mat object to store an image.
    cv::Mat img;
    // Reading the image from disk.
    img = cv::imread("input.jpg");
    if (img.empty()) {
        printf("\nUnable to read image from disk.");
        return 1;
    }

    // Displaying the image on screen using OpenCV's imshow() function.
    cv::namedWindow("Input Image", CV_WINDOW_AUTOSIZE);
    cv::imshow("Input Image", img);

    // Writing the image to disk using OpenCV's imwrite() function.
    cv::imwrite("output.jpg", img);

    // Cleaning up resources and waiting for user input before exiting program.
    cv::waitKey(0);
    return 0;
}