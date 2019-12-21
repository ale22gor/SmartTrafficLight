#include "filtermovedetectframe.h"
using namespace cv;
FilterMoveDetectFrame::FilterMoveDetectFrame()
{
    // MORPH_RECT/MORPH_CROSS/MORPH_ELLIPSE
    int dilation_elem{MORPH_CROSS};
    // 1-21
    int dilation_size{1};

    dilationElement = getStructuringElement(
                dilation_elem, Size{2 * dilation_size + 1, 2 * dilation_size + 1},
                Point{dilation_size, dilation_size});

    // MORPH_RECT/MORPH_CROSS/MORPH_ELLIPSE
    int closing_elem{MORPH_ELLIPSE};
    // 1-21
    int closing_size{1};

    closingElement = getStructuringElement(
                closing_elem, Size{2 * closing_size + 1, 2 * closing_size + 1},
                Point{closing_size, closing_size});

    // MORPH_RECT/MORPH_CROSS/MORPH_ELLIPSE
    int opening_elem{MORPH_ELLIPSE};
    // 1-21
    int opening_size{1};

    openingElement = getStructuringElement(
                opening_elem, Size{2 * opening_size + 1, 2 * opening_size + 1},
                Point{opening_size, opening_size});

}
void FilterMoveDetectFrame::Run(const Mat &inputFrame, Mat &outputFrame)
{


    morphologyEx(outputFrame, outputFrame, MORPH_CLOSE, closingElement);

    morphologyEx(outputFrame, outputFrame, MORPH_OPEN, openingElement);

    dilate(inputFrame, outputFrame, dilationElement, Point(-1, -1), 2);

    erode(inputFrame, outputFrame, dilationElement, Point(-1, -1), 2);



    //blur(inputFrame, outputFrame, Size(1,1)); // blur input image

    threshold(outputFrame, outputFrame, 250, 255, m_thresholdType);
}
