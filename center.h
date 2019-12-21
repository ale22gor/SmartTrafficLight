#include <opencv2/core/types.hpp>

#ifndef CENTER_H
#define CENTER_H


struct Center {
  Center(const cv::Point cordinates);
  Center(const Center &center);

  cv::Point m_cordinates;
  bool m_isAdded;
};
#endif
