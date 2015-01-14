# Global Matting

This project is built by reproducing the global matting algorithm in the CVPR 2011 paper: 

He, Kaiming, et al. "A global sampling method for alpha matting." In CVPR’11, pages 2049–2056, 2011.


## Benchmark

After evaluating the results on the [alpha matting evaluation website](http://alphamatting.com/), this implementation (with matting Laplacian as post-processing) ranks 5th in SAD and 6th in MSE (the original implementation ranks 10th in SAD and 9th in MSE). Running time is less than 1 seconds for an 800x600 image.  Hence, this implementation is one of the highest ranked among the fast matting methods.


## Example

### Code

```c++
#include "globalmatting.h"

// you can get the guided filter implementation
// from https://github.com/atilimcetin/guided-filter
#include "guidedfilter.h"

int main()
{
    cv::Mat image = cv::imread("GT04-image.png", CV_LOAD_IMAGE_COLOR);
    cv::Mat trimap = cv::imread("GT04-trimap.png", CV_LOAD_IMAGE_GRAYSCALE);

    // (optional) exploit the affinity of neighboring pixels to reduce the 
    // size of the unknown region. please refer to the paper
    // 'Shared Sampling for Real-Time Alpha Matting'.
    expansionOfKnownRegions(image, trimap, 9);

    cv::Mat foreground, alpha;
    globalMatting(image, trimap, foreground, alpha);

    // filter the result with fast guided filter
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

### Result

[![Image](http://atilimcetin.com/global-matting/GT04-image_small.png)](http://atilimcetin.com/global-matting/GT04-image.png)
[![Trimap](http://atilimcetin.com/global-matting/GT04-trimap_small.png)](http://atilimcetin.com/global-matting/GT04-trimap.png)
[![Alpha](http://atilimcetin.com/global-matting/GT04-alpha_small.png)](http://atilimcetin.com/global-matting/GT04-alpha.png)


## License

MIT License.


