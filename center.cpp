#include "center.h"

Center::Center(const cv::Point cordinates)
    : m_cordinates{cordinates}, m_isAdded{false} {}
Center::Center(const Center &center)
    : m_cordinates{center.m_cordinates}, m_isAdded{center.m_isAdded} {}
