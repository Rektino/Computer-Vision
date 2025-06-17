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

inline std::unique_ptr<cv::Mat> loadImage(const std::string& filepath) {
    cv::Mat image = cv::imread(filepath);
    if (image.empty()) {
        throw std::runtime_error("Could not load image: " + filepath);
    }
    return std::make_unique<cv::Mat>(std::move(image));
}

class DisparityMapGenerator {
public:
    DisparityMapGenerator(const std::string& path_img1 ,const std::string& path_img2):
    m_img1(std::make_unique<cv::Mat>(cv::imread(path_img1))),m_img2(std::make_unique<cv::Mat>(cv::imread(path_img2)))
    {
        std::cout << "Disparity Map Generator Constructor" << std::endl;
    }
private:
    std::unique_ptr<cv::Mat> m_img1 ;
    std::unique_ptr<cv::Mat> m_img2 ;

};

#endif //DISPARITYMAPGENERATOR_H
