#include "path.h"
#include <opencv2/imgproc.hpp>
#include <math.h>
#include "center.h"



Path::Path() : m_lostCarFrames{0} ,m_minLenght{15}{}

Path::Path(const Center &c) : Path() { m_points.push_back(c.m_cordinates); }

void Path::AddPoint(const cv::Point point) {
  if (m_points.size() == m_maxPoints)
    m_points.pop_front();
  m_points.push_back(std::move(point));
  m_minLenght = 15;
}
bool Path::CheckLength(const cv::Point b) {
  cv::Point a;
  if (m_points.size() == 1)
    a = m_points[0];
  else if (m_points.size() > 1)
    a = predictPoint();

  int length;
  length = pow((a.x - b.x), 2) + pow((a.y - b.y), 2);
  length = sqrt(length);
  if (length < m_minLenght && length > 0) {
    m_minLenght = length;
    return true;
  } else {
    return false;
  }
}
bool Path::CheckLost() { return m_lostCarFrames > m_lostFrameCup; }

int Path::DrawPath(const cv::Mat &sourceFrame) {

  for (auto ptr = m_points.begin(); ptr != m_points.end(); ++ptr) {

    auto i = std::distance(m_points.begin(), ptr);
    if (i >= 1) {
      auto x = ptr - 1;
      cv::line(sourceFrame, *x, *ptr, cv::Scalar(0, 255, 0));
    }
    cv::circle(sourceFrame, *ptr, 2, cv::Scalar(0, 0, 255), -1);
  }
  return 0;
}
cv::Point Path::predictPoint() {
  cv::Point last = m_points[m_points.size() - 1];
  cv::Point secondToLast = m_points[m_points.size() - 2];
  int deltaX{last.x - secondToLast.x};
  int deltaY{last.y - secondToLast.y};
  return cv::Point{last.x + deltaX, last.y + deltaY};
}
bool Path::CheckExit(const cv::Mat &maskedFrame) {
  if (m_points.size() < 2) {
    return false;
  }

  for (auto ptr = m_points.begin() + 1; ptr != m_points.end(); ++ptr) {
    auto x = ptr - 1;
    if (static_cast<int>(maskedFrame.at<uchar>(*ptr)) == 255 &&
        static_cast<int>(maskedFrame.at<uchar>(*x)) == 0)
      return true;
  }
  return false;
}
bool Path::CheckInArea(const cv::Mat &maskedFrame) {

  for (auto ptr = m_points.begin(); ptr != m_points.end(); ++ptr) {
    if (static_cast<int>(maskedFrame.at<uchar>(*ptr)) == 255)
        return true;
  }
  return false;
}

Path &Path::operator=(const Path &p) {
  // Check for self assignment

  if (this != &p) {
    // id = p.id;
    m_points = p.m_points;
    m_lostCarFrames = p.m_lostCarFrames;
  }
  return *this;
}
