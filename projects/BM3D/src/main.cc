#include <iostream>
#include <string>

#include "include/CImg.h"
#include "boost/program_options.hpp"

int main(int argc, char** argv) {
    namespace popt = boost::program_options;
    std::cout << "Hello!" << std::endl;
    popt::options_description desc("BM3D");

    float sigma;
    desc.add_options()
        ("help", "Print this message")
        ("input,i", popt::value<std::vector<std::string>>(), "Input filename")
        ("output,o", popt::value<std::vector<std::string>>(), "Output filename")
        ("sigma,s", popt::value<float>(&sigma)->default_value(20.0f), "???");
    
    popt::positional_options_description pos;
    pos.add("input", -1);
    popt::variables_map vm;
    try {
        popt::store(popt::command_line_parser(argc, argv)
            .options(desc).positional(pos).run(), vm);
        popt::notify(vm);
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
        return -1;
    }
    
    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 1;
    }

    if (vm.count("input")) {
        auto infile = vm["input"].as<std::vector<std::string>>();
        std::cout << "Image to denoise is " << infile[0] << std::endl;
    } else {
        std::cout << "No input image given." << std::endl;
        return -1;
    }
    if (vm.count("output")) {
        auto outfile = vm["output"].as<std::vector<std::string>>();
        std::cout << "Image will be saved to " << outfile[0] << std::endl;
    }
    if (vm.count("sigma")) {
        sigma = vm["sigma"].as<float>();
        std::cout << "Sigma = " << sigma << std::endl;
    }

    return 0;
}
