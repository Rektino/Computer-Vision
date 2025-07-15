#ifndef CAMERACALIBRATOR_HPP
#define CAMERACALIBRATOR_HPP

#include <format>
#include <iostream>
#include <opencv2/calib3d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
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
  auto calculateChessboardCorners() -> void;
  auto performCalibration() -> CameraCalibrationData;
  auto writeCalibrationToFile(std::string_view out_path,
                              std::string_view name) -> void;
  auto calculateReprojectionError() -> float;

private:
  std::string m_dirpath;
  const cv::Point2i m_board_size;
  const float m_square_size;
  std::vector<std::vector<cv::Point3f>> m_object_points;
  std::vector<std::vector<cv::Point2f>> m_image_points;
  // methods
  std::vector<std::string>
  generateFilenames(const std::string &prefix, int start_num, int max_num,
                    int num_padding, const std::string &separator,
                    int start_set, int max_set, int set_padding,
                    const std::string &suffix);
};

#endif // CAMERACALIBRATOR_HPP
