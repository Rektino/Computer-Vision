//
// Created by geode on 6/17/2025.
//
#include "DisparityMapGenerator.hpp"

DisparityMapGenerator::DisparityMapGenerator(const std::string &path_img1,
                                             const std::string &path_img2)
    : m_img1(std::make_unique<cv::Mat>(cv::imread(path_img1))),
      m_img2(std::make_unique<cv::Mat>(cv::imread(path_img2))) {
  std::cout << "Disparity Map Generator Constructor" << std::endl;
}
