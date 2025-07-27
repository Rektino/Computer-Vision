#include "CameraCalibrator.hpp"
#include "CameraParameters.hpp"
#include "DisparityMapGenerator.hpp"
using namespace cv;

int main(int argc, char **argv) {
  std::cout << "Hello from CV main file" << "\n";

  CameraCalibrator Calibrator{"images/101215_151454_MultiCamera0/",
                              cv::Size(7, 5), 4.0};
  Calibrator.calculateChessboardCorners();
  Calibrator.performCalibration();
  waitKey(0);
  return 0;
}
