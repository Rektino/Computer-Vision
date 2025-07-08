#include "CameraCalibrator.hpp"
#include "CameraParameters.hpp"
#include "DisparityMapGenerator.hpp"
using namespace cv;

int main(int argc, char **argv) {
  std::cout << "Hello from CV main file" << "\n";
  std::vector<std::string> filenamesForCalibration =
      generateFilenames("cam", 0, 1, 1, "_image", 1500, 1600, 4, ".bmp");
  for (auto &file : filenamesForCalibration) {
    std::cout << file << std::endl;
  }

  CameraCalibrator calib{"images/", cv::Point2i{8, 6}, 4.0};

  calib.calculateChessboardCorners();

  return 0;
}
