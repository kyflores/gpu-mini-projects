set(IMAGE_FILTER_SRC
    image_filter.cc)

set(IMAGE_FILTER_INC
    .
    ${PROJECT_SOURCE_DIR}/common/include/)

find_package( OpenCV REQUIRED )

set(COMPILER_FLAGS "-g --std=c++17")
set(ARCH_FLAGS "-amdgpu-target=gfx803 -amdgpu-target=gfx900")

add_executable(ImageFilter ${IMAGE_FILTER_SRC})
target_include_directories(ImageFilter PRIVATE ${IMAGE_FILTER_INC} ${OpenCV_INCLUDE_DIRS})
target_link_libraries(ImageFilter PRIVATE ${OpenCV_LIBS})
set_target_properties(ImageFilter PROPERTIES COMPILE_FLAGS ${COMPILER_FLAGS})