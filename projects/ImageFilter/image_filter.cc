#include <string>
#include <cstdint>
#include <iostream>
#include "opencv2/opencv.hpp"
#include "hip/hip_runtime.h"

template <typename T>
struct __attribute__((packed)) BGRPixel {
    T B;
    T G;
    T R;
};
static_assert(sizeof(BGRPixel<uint8_t>) == 3*sizeof(uint8_t));

template<typename T>
__global__ void ChannelReverseKernel(T* img, const size_t rows, const size_t cols) {
    const size_t x = hipBlockDim_x * hipBlockIdx_x + hipThreadIdx_x;
    const size_t y = hipBlockDim_y * hipBlockIdx_y + hipThreadIdx_y;
    auto index = [cols] (size_t x, size_t y) { return y*cols + x; };
    img[index(x,y)].B = img[index(x,y)].G;  // B
    img[index(x,y)].G = img[index(x,y)].R;  // G
    img[index(x,y)].R = img[index(x,y)].B;  // R
    return;
}

template<typename T>
__global__ void GaussianKernel(T* img, const size_t rows, const size_t cols) {
    const size_t x = hipBlockDim_x * hipBlockIdx_x + hipThreadIdx_x;
    const size_t y = hipBlockDim_y * hipBlockIdx_y + hipThreadIdx_y;
    auto index = [cols] (size_t x, size_t y) { return y*cols + x; };

    return;
}


int Process(cv::Mat& img) {
    // Assumes that data is densely packed and is u8
    // For instance, a 3x3 would be like
    // [B,G,R][B,G,R][B,G,R]
    // [B,G,R][B,G,R][B,G,R]
    // [B,G,R][B,G,R][B,G,R]
    if (img.depth() != CV_8U) {
        std::cout << "Unknown depth: " << img.depth() << std::endl;
        return -1;
    }
    if (!img.isContinuous()) {
        std::cout << "Not continuous" << std::endl;
        return -1;
    }
    if (img.channels() != 3) {
        std::cout << "Not 3 channels" << std::endl;
        return -1;
    }

    const size_t datasize = img.channels() * img.rows * img.cols;
    // const size_t datasize = img.rows * img.cols;
    BGRPixel<uint8_t>* gpu_ptr;
    auto err = hipMalloc(&gpu_ptr, datasize);
    if(err) {return -1;}
    err = hipMemcpy(gpu_ptr, img.ptr<BGRPixel<uint8_t>>(0), datasize, hipMemcpyDefault);
    if(err) {return -1;}


    std::cout << "Launching " << (img.cols+15)/16 << " by " << (img.rows+15)/16 << std::endl;
    hipLaunchKernelGGL(ChannelReverseKernel<BGRPixel<uint8_t>>,
                       dim3((img.cols+15)/16,(img.rows+15)/16),
                       dim3(16,16),
                       0, 0,
                       gpu_ptr, img.rows, img.cols);

    err = hipMemcpy(img.ptr<BGRPixel<uint8_t>>(0), gpu_ptr, datasize, hipMemcpyDefault);
    if(err) {return -1;}
    err = hipFree(gpu_ptr);
    if(err) {return -1;}
    return 0;
}

int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        std::cout << "First arg should be <img_path>" << std::endl;
        return -1;
    }
    cv::Mat image(cv::imread(argv[1]));
    if ( !image.data )
    {
        std::cout << "No data." << std::endl;
        return -1;
    }

    std::cout << "Image has " << image.channels() << " channels, " << 
                  image.dims << " dimensions" << std::endl;
    std::cout << "And is R:" << image.rows << " by C:" << image.cols << std::endl;

    int err = Process(image);
    cv::imwrite("result.jpg", image);
    return err;
}
