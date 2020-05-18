#include <string>

#include "include/CImg.h"

int run_bm3d(
    const std::string& infile,
    const std::string& outfile,
    const float sigma)
{
    namespace cimg = cimg_library;
    cimg::CImg<float> src(infile.data());

}