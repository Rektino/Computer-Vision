//
// Created by geode on 6/18/2025.
//

#ifndef CAMERACALIBRATOR_HPP
#define CAMERACALIBRATOR_HPP
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdexcept>

struct CameraCalibrationData {
    cv::Mat cameraIntrinsic ;
    std::vector<float> distCoeffs ;
};

class CameraCalibrator {
    explicit CameraCalibrator(std::string_view dirpath ,
        const std::vector<int>& boardSize, float squareSize) ;

    CameraCalibrationData perform_calibration() ;

private:
    const std::string m_dirpath ;
    int m_chessBoardFlags ;
    std::vector<int> m_boardSize ;
    //methods:

};





#endif //CAMERACALIBRATOR_HPP
