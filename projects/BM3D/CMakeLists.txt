find_package(TIFF REQUIRED)
find_package(JPEG REQUIRED)
find_package(PNG REQUIRED)
find_package(OpenMP)
find_package(X11)

set(Boost_USE_STATIC_LIBS ON) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.58.0 COMPONENTS
    program_options
) 

set(BM3D_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bm3d.cc
)

set(LIB_INCLUDES
    ${TIFF_INCLUDE_DIR}
    ${JPEG_INCLUDE_DIR}
    ${PNG_INCLUDE_DIR}
    ${Boost_INCLUDE_DIRS}
    ${X11_INCLUDE_DIR}
)

set(BM3D_INC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/common/
)

set(BM3D_LINK_LIBRARIES
    ${TIFF_LIBRARIES}
    ${JPEG_LIBRARIES}
    ${PNG_LIBRARIES}
    ${OpenMP_CXX_LIBRARIES}
    ${Boost_LIBRARIES}
    ${X11_LIBRARIES}
)

set(COMPILER_FLAGS "-g -Og --std=c++17 -Wall")
set(CIMG_FEATURE_DEFS 
    cimg_display=1
    cimg_use_png
    cimg_use_jpeg
    cimg_use_tiff
)
set(GPU_ARCH_FLAGS "-amdgpu-target=gfx803 -amdgpu-target=gfx900")

add_executable(BM3D ${BM3D_SRC})
target_include_directories(BM3D PRIVATE ${BM3D_INC})
target_link_libraries(BM3D PRIVATE ${BM3D_LINK_LIBRARIES})
set_target_properties(BM3D PROPERTIES COMPILE_FLAGS ${COMPILER_FLAGS})
target_compile_definitions(BM3D PRIVATE ${CIMG_FEATURE_DEFS})