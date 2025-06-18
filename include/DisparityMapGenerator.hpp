//
// Created by geode on 6/16/2025.
//

#ifndef DISPARITYMAPGENERATOR_H
#define DISPARITYMAPGENERATOR_H
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdexcept>
#include
/* Pipeline for disparity map calculation :
 * 1. Image acquisition 2. Calibrate cameras-> find intrisic matrices (might be known or calculated
 * independently)
 * 3. Stereo calibration -> finding the relative rotation and translation between the
 * two cameras. 4. Stereo rectification -> editing the images so that corresponding points
 * lie on the same horizontal lines.  5. Stereo matching algorithm to compute the pixel-wise
 * disparities between the images.
 */


inline std::unique_ptr<cv::Mat> loadImage(const std::string& filepath) {
    cv::Mat image = cv::imread(filepath);

    if (image.empty()) {
        throw std::runtime_error("Could not load image: " + filepath);
    }
    return std::make_unique<cv::Mat>(std::move(image));
}

class DisparityMapGenerator {
public:
    DisparityMapGenerator(const std::string& path_img1 ,const std::string& path_img2);
    ~DisparityMapGenerator() = default ;



private:
    std::unique_ptr<cv::Mat> m_img1 ;
    std::unique_ptr<cv::Mat> m_img2 ;
};

#endif //DISPARITYMAPGENERATOR_H
