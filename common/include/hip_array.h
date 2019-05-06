#include "hip/hip_runtime.h"
#include <memory>
#include <functional>

template <typename T>
class HipArray {
 public:
    // Standard C-tor
    HipArray(size_t size) :
        size_(size),
        mem_ptr_(WrapHipMalloc(size), HipArray<T>::WrapHipFree) {}
    
    // Move Constructor
    HipArray(HipArray<T>&& other {
        if (this != &other) {
            size_ = other.size_;
            mem_ptr_ = other.mem_ptr_;
        }
    }

    // Move assignment
    HipArray<T>& operator=(HipArray<T>&& other) {
        if (this != &other) {
            size_ = other.size;
            mem_ptr_ = other.mem_ptr_;
        }
        return *this;
    }
    

 private:
    static T* WrapHipMalloc(size_t size) {
        T* ptr;
        hipMalloc(&ptr, size * sizeof(T));
        return ptr;
    }

    static void WrapHipFree(T* ptr) {
        hipFree(ptr);
    }

    size_t size_;
    std::unique_ptr<T, std::function<void(T*)>> mem_ptr_;
};
