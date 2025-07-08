#ifndef CAMERACALIBRATOR_HPP
#define CAMERACALIBRATOR_HPP

#include <format>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <stdexcept>
#include <string>

// Forward declaration of a helper function that populates a vector with the
// filenames containing the images used for the calibration.
std::vector<std::string>
generateFilenames(const std::string &prefix, int start_num, int max_num,
                  int num_padding, const std::string &separator, int start_set,
                  int max_set, int set_padding, const std::string &suffix);

struct CameraCalibrationData {
  cv::Mat cameraIntrinsic;
  std::vector<float> distCoeffs;
};

class CameraCalibrator {
public:
  CameraCalibrator(std::string dirpath, cv::Point2i board_size,
                   float square_size);
  auto createImagesStringVector() -> std::vector<std::string>;
  auto calculateChessboardCorners() -> void;
  auto performCalibration() -> CameraCalibrationData;
  auto writeCalibrationToFile(std::string_view out_path,
                              std::string_view name) -> void;
  auto calculateReprojectionError() -> float;

private:
  std::string m_dirpath;
  const cv::Point2i m_board_size;
  const float m_square_size;
  std::vector<cv::Point3f> m_corners;
};

#endif // CAMERACALIBRATOR_HPP
