#ifndef GLOBAL_MATTING_H
#define GLOBAL_MATTING_H

#include <opencv2/opencv.hpp>

void expansionOfKnownRegions(cv::InputArray img, cv::InputOutputArray trimap, int niter = 9);
void globalMatting(cv::InputArray image, cv::InputArray trimap, cv::OutputArray foreground, cv::OutputArray alpha, cv::OutputArray conf = cv::noArray());

#endif
