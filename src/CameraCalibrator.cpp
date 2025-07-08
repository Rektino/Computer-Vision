
#include "CameraCalibrator.hpp"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

// The constructor definition with the member initializer list

CameraCalibrator::CameraCalibrator(std::string dirpath, cv::Point2i board_size,
                                   float squareSize)
    : m_dirpath(dirpath), m_board_size(board_size), m_square_size(squareSize) {}

auto CameraCalibrator::calculateChessboardCorners() -> void {
  for (int i = 0; i < m_board_size.x; ++i) {
    for (int j = 0; j < m_board_size.y; ++j) {
      m_corners.emplace_back(i * m_square_size, j * m_square_size, 0);
      std::cout << "New corner at : " << i * m_square_size << ","
                << j * m_square_size << "," << 0 << std::endl;
    }
  }
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
std::vector<std::string>
generateFilenames(const std::string &prefix, int start_num, int max_num,
                  int num_padding, const std::string &separator, int start_set,
                  int max_set, int set_padding, const std::string &suffix) {
  if (max_num < 0 || max_set < 0 || num_padding <= 0 || set_padding <= 0) {
    throw std::invalid_argument("Limits and padding must be non-negative.");
  }

  std::vector<std::string> filenames;
  // Reserve memory in advance to avoid reallocations, improving performance.
  filenames.reserve(static_cast<size_t>(max_num + 1) * (max_set + 1));

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
      filenames.push_back(std::format("{}{:0{}}{}{:0{}}{}", prefix, i,
                                      num_padding, separator, j, set_padding,
                                      suffix));
    }
  }
  return filenames;
}
