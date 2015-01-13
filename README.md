# A Global Sampling Method for Alpha Matting

This is an implementation of trimap to alpha matting algorithm for OpenCV.

## Benchmark

When matting Laplacian as post-processing is used, this implementation ranks 5th in SAD and 6th in MSE (The original implementation ranks 10th in SAD and 9th in MSE). Running time is less than 1 seconds for an 800x600 image.


## Example

```c++
#include "globalmatting.h"
#include "guidedfilter.h"   // you can get guided filter implementation from https://github.com/atilimcetin/guided-filter

int main()
{
    cv::Mat image = cv::imread("GT04-image.png", CV_LOAD_IMAGE_COLOR);
    cv::Mat trimap = cv::imread("GT04-trimap.png", CV_LOAD_IMAGE_GRAYSCALE);

    expansionOfKnownRegions(image, trimap, 9);

    cv::Mat foreground, alpha;
    globalMatting(image, trimap, foreground, alpha);

    alpha = guidedFilter(image, alpha, 10, 1e-5);
    for (int x = 0; x < trimap.cols; ++x)
        for (int y = 0; y < trimap.rows; ++y)
        {
            if (trimap.at<uchar>(y, x) == 0)
                alpha.at<uchar>(y, x) = 0;
            else if (trimap.at<uchar>(y, x) == 255)
                alpha.at<uchar>(y, x) = 255;
        }

    cv::imwrite("GT04-alpha.png", alpha);

    return 0;
}
```

## License

MIT License.


