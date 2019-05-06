#include <iostream>
#include <vector>
#include "hip/hip_runtime.h"


// Does A * B = C
class VectorMultiply {
public:
    VectorMultiply(const std::vector<float>& a,
        const std::vector<float>& b,
        std::vector<float>& c) :
        a_(a), b_(b), c_(c), 
        ga_(nullptr), gb_(nullptr), gc_(nullptr) {}
    ~VectorMultiply() {
        hipFree(ga_);
        hipFree(gb_);
        hipFree(gc_);
    }

    std::string GetDeviceName();
    void Execute();

private:
    const std::vector<float>& a_;
    const std::vector<float>& b_;
    std::vector<float>& c_;
    float* ga_;
    float* gb_;
    float* gc_;

    const int THREADS_PER_BLOCK = 64;
};
