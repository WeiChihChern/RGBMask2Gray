//
//  main.cpp
//  rgb_mask_to_grayscale
//
//  Created by Wei Chih Chern on 3/3/21.
//


#include <iostream>
#include <string>
#include "Mask2Grayscale.h"
#include "argparse/argparse.hpp"

// Depends on OPENCV as IO

using namespace std;


int main(int argc, const char * argv[]) {
    
    argparse::ArgumentParser program("RGBMask2Gray");
    
    program.add_argument("-ImagePath").required().help("Path to RGB mask images");
    program.add_argument("-ClassRGBPath").required().help("The text file contains each class's RGB values. \n\t\t.txt file Example: \n\t\t0  0  0  | Background class \n\t\t0  0 255 | car class \n\t\tetc.");
    
    try {
      program.parse_args(argc, argv);
    }
    catch (const std::runtime_error& err) {
      std::cout << err.what() << std::endl;
      std::cout << program;
      exit(0);
    }
    
    string imgPath      = program.get<string>("-ImagePath");
    string classRGBpath = program.get<string>("-ClassRGBPath");
    
    Mask2Grayscale convertTool;
    convertTool.convert(imgPath, classRGBpath);
    
    cout << "Conversion completed!\n";
    return 0;
}
