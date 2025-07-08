
#include "CameraCalibrator.hpp"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

// The constructor definition with the member initializer list

CameraCalibrator::CameraCalibrator(std::string dirpath,
                                   const std::vector<cv::Point2i> &boardSize,
                                   float squareSize)
    : m_dirpath(dirpath) { // <-- This initializer list fixes the issue

  // The rest of your constructor logic goes here.
  // Note: You will also need to initialize your other members like m_boardSize.
}

// ... your other function implementations ...
//

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

  // Create the format string once before the loops.
  // e.g., "chessimage{:03}_set{:03}.png"
  //  const std::string format_pattern =
  //     std::format("{}{{:{:0{}}}}{}{{:{:0{}}}}{}", prefix, "d", num_padding,
  //                separator, "d", set_padding, suffix);

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
