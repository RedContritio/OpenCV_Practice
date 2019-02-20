#ifndef MATRESIZE__INC
#define MATRESIZE__INC
#pragma once

#define SCALE_RATE(x,operation) x operation

#define MatResize(img,operation) cv::resize(img, img, cv::Size(SCALE_RATE(img.cols,operation), SCALE_RATE(img.rows,operation)));
#endif