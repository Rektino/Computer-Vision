#include "CameraCalibrator.hpp"
#include <iostream>
#include <opencv2/calib3d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
// The constructor definition with the member initializer list

CameraCalibrator::CameraCalibrator(std::string dirpath, cv::Point2i board_size,
                                   float squareSize)
    : m_dirpath(dirpath), m_board_size(board_size), m_square_size(squareSize) {}

auto CameraCalibrator::calculateChessboardCorners() -> void {
  m_object_points.resize(1);
  for (int i = 0; i < m_board_size.x; ++i) {
    for (int j = 0; j < m_board_size.y; ++j) {
      m_object_points.at(0).emplace_back(i * m_square_size, j * m_square_size,
                                         0);
      std::cout << "New corner at : " << i * m_square_size << ","
                << j * m_square_size << "," << 0 << std::endl;
    }
  }
}

auto CameraCalibrator::performCalibration() -> CameraCalibrationData {
  std::vector<Mat> rvecs, tvecs;
  Size2i image_size;
  Mat intrinsic_matrix;
  Mat distCoeffs;
  int flags = 0;
  bool found;
  cv::TermCriteria criteria = cv::TermCriteria(
      cv::TermCriteria::COUNT + cv::TermCriteria::EPS, 100, 1e-6);
  //  m_image_points.reserve(image_filenames.size());
  cv::Mat view, viewGray; // current image
  std::vector<Point2f> points_temp_buffer;
  std::vector<std::string> image_filenames =
      generateFilenames("cam", 0, 0, 1, "_image", 28, 492, 5, ".bmp");

  for (int i = 0; i < image_filenames.size(); ++i) {
    auto image_path = image_filenames[i];
    view = cv::imread(image_path, cv::IMREAD_COLOR);
    if (view.empty()) {
      std::cerr << "Failed to open image from filename" << "\n";
    }
    image_size = view.size();
    cvtColor(view, viewGray, COLOR_BGR2GRAY);
    found = cv::findChessboardCorners(
        viewGray, m_board_size, points_temp_buffer,
        CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_FAST_CHECK |
            CALIB_CB_NORMALIZE_IMAGE);
    if (!found) {
      std::cout << "Failed to find chessboard corners on image : " << image_path
                << std::endl;
    } else {
      cornerSubPix(
          viewGray, points_temp_buffer, m_board_size, Size(-1, -1),
          TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 30, 0.0001));
      m_image_points.push_back(points_temp_buffer);
      drawChessboardCorners(view, m_board_size, Mat(points_temp_buffer), found);
      cv::imshow("corners drawn", view);
    }
  }
  // now we need to make the object points match the size of the image points
  // and populate it with the one element.
  m_object_points.resize(m_image_points.size(), m_object_points.at(0));
  // Perform calibration :
  float rms_reproj_error = calibrateCamera(
      m_object_points, m_image_points, image_size, intrinsic_matrix, distCoeffs,
      rvecs, tvecs, flags, criteria);
  // 7. Print results
  std::cout << "\n--- Camera Calibration Results ---" << std::endl;
  std::cout << "RMS Re-projection Error: " << rms_reproj_error << std::endl;
  std::cout << "\nCamera Matrix:\n" << intrinsic_matrix << std::endl;
  std::cout << "\nDistortion Coefficients:\n" << distCoeffs << std::endl;
  return CameraCalibrationData(intrinsic_matrix, distCoeffs);
}

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
 * @param suffix The file extension or trailing part of the name (e.g.,
 * ".png").
 * @return A std::vector<std::string> containing all the generated filenames.
 */
std::vector<std::string> CameraCalibrator::generateFilenames(
    const std::string &prefix, int start_num, int max_num, int num_padding,
    const std::string &separator, int start_set, int max_set, int set_padding,
    const std::string &suffix) {
  if (max_num < 0 || max_set < 0 || num_padding <= 0 || set_padding <= 0) {
    throw std::invalid_argument("Limits and padding must be non-negative.");
  }

  std::vector<std::string> filenames;
  // Reserve memory in advance to avoid reallocations, improving performance.
  filenames.reserve(static_cast<size_t>(max_num - start_num + 1) *
                    (max_set - start_set + 1));

  // Iterate through all possible numbers for the first part (XXX)
  for (int i = start_num; i <= max_num; ++i) {
    // Iterate through all possible numbers for the second part (YYY)
    for (int j = start_set; j <= max_set; ++j) {
      // Use std::format to create the final string safely and efficiently.
      // The format specifiers {:03} mean:
      // :   - Start of format specifier
      // 0   - Pad with leading zeros
      // 3   - Total width of the number
      // d   - (optional) format as decimal integer
      filenames.push_back(m_dirpath + std::format("{}{:0{}}{}{:0{}}{}", prefix,
                                                  i, num_padding, separator, j,
                                                  set_padding, suffix));
    }
  }
  return filenames;
}
