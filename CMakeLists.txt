# Don't forget to set CXX=/opt/rocm/bin/hipcc

cmake_minimum_required (VERSION 3.10)
project(gpu-mini-projects CXX)

# add_subdirectory("projects/VectorMultiply/")
# add_subdirectory("projects/ImageFilter/")
add_subdirectory("projects/BM3D/")
