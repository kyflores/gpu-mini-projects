#include "vector_multiply.h"

template<typename T>
__global__ void VectorMultiplyKernel(T* a, T* b, T *c, size_t length) {
        int x = hipBlockDim_x * hipBlockIdx_x + hipThreadIdx_x;
        c[x] = a[x] * b[x];
}

std::string VectorMultiply::GetDeviceName() {
    hipDeviceProp_t devProp;
    hipGetDeviceProperties(&devProp, 0);
    return devProp.name;
}

void VectorMultiply::Execute() {
    hipMalloc((void**)&ga_, a_.size()*sizeof(float));
    hipMalloc((void**)&gb_, b_.size()*sizeof(float));
    hipMalloc((void**)&gc_, c_.size()*sizeof(float));
    hipMemcpy(ga_, a_.data(), a_.size()*sizeof(float), hipMemcpyHostToDevice);
    hipMemcpy(gb_, b_.data(), b_.size()*sizeof(float), hipMemcpyHostToDevice);

    const unsigned WIDTH = a_.size();
    hipLaunchKernelGGL(VectorMultiplyKernel<float>,
        dim3(WIDTH/THREADS_PER_BLOCK),
        dim3(THREADS_PER_BLOCK),
        0, 0,
        ga_ , gb_, gc_, a_.size());

    hipMemcpy(c_.data(), gc_, c_.size()*sizeof(float), hipMemcpyDeviceToHost);
}

int main() {
    const unsigned length = 64 * 8;

    std::vector<float> a(length);
    std::vector<float> b(length);
    std::vector<float> c_cpu(length);
    std::vector<float> c_gpu(length);

    // Produce the result with the CPU
    for(int i = 0; i < length; i++) {
        a[i] = i;
        b[i] = i;
        c_cpu[i] = a[i]*b[i];
    }

    VectorMultiply launcher = VectorMultiply(a, b, c_gpu);
    std::cout << "Device name " << launcher.GetDeviceName() << std::endl;
    launcher.Execute();

    for(int i = 0; i < length; i++) {
        if (!(c_cpu[i] == c_gpu[i])) {
            std::cout << "Error @ " << i << std::endl;
            return -1;
        }
    }
    std::cout << "Passed." << std::endl;
}