#ifndef CAMERACALIBRATOR_HPP
#define CAMERACALIBRATOR_HPP

#include <format>
#include <iostream>
#include <opencv2/core.hpp>
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
  CameraCalibrator(std::string dirpath,
                   const std::vector<cv::Point2i> &boardSize, float squareSize);

  auto createImagesStringVector() -> std::vector<std::string>;
  auto performCalibration() -> CameraCalibrationData;
  auto calculateReprojectionError() -> float;

private:
  std::string m_dirpath;
  int m_chessBoardFlags;
  std::vector<int> m_boardSize;
  // methods:
};

/**
 * @brief Generates a vector of formatted filenames based on a pattern.
 *
 * This function creates filenames by iterating through two numerical ranges,
 * formatting the numbers with leading zeros, and inserting them into a
 * user-defined string pattern.
 *
 * Example Pattern: "prefix_{}_separator_{}_suffix"
 *
 * @param prefix The constant string part before the first number (e.g.,
 * "chessimage").
 * @param max_num The upper limit (inclusive) for the first number (XXX).
 * @param num_padding The total number of digits for the first number, padded
 * with zeros (e.g., 3 for XXX).
 * @param separator The constant string part between the two numbers (e.g.,
 * "_set").
 * @param max_set The upper limit (inclusive) for the second number (YYY).
 * @param set_padding The total number of digits for the second number, padded
 * with zeros (e.g., 3 for YYY).
 * @param suffix The file extension or trailing part of the name (e.g., ".png").
 * @return A std::vector<std::string> containing all the generated filenames.
 */
#endif // CAMERACALIBRATOR_HPP
