//
//  Mask2Grayscale.h
//  rgb_mask_to_grayscale
//
//  Created by Wei Chih Chern on 3/3/21.
//

#ifndef Mask2Grayscale_h
#define Mask2Grayscale_h
#define cimg_use_png

#include "listdir.h"
//#include "opencv2/opencv.hpp"
#include "CImg.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <stdlib.h>
#include <numeric>

using namespace std;
//using namespace cv;
using namespace cimg_library;


class Mask2Grayscale {
public:
    
    Mask2Grayscale() : _class_bgr_loaded(false), _class_bgr(3,0)/*background class*/{};
    
    
    
    // Where you have RGB masks already and want to conver it to grayscale encoded instead
    // Support .PNG image format for now only
    int convert(const string& path, const string& txtBGRcode)
    {
        cout << "This app supports .PNG images only for now\n";
        
        // Read all file names
        vector<string> rgb_files = listdir::listdir(path);
        cout << "Detected " << rgb_files.size() << " images\n";
        
        // Read each class's RGB values
        this->_readClassRGBtxt(txtBGRcode);
        
        // Start processing
        #pragma omp parallel for
        for (size_t i = 0; i < rgb_files.size(); ++i)
        {
            if(
                   rgb_files[i].find(".DS_Store") != -1 || // Mac specific hidden file
                   rgb_files[i].find("classIdx")  != -1    // Prevent user run the app without removing previous generated files
               )
                    continue;
            
            CImg<unsigned char> img(rgb_files[i].c_str());
            
            cimg_forXY(img,x,y)
            {
                int idx    = this->_rgbMatching(img,x,y);
                img(x,y,0) = img(x,y,1) = img(x,y,2) = idx;
            }

            
            // Finished convert RGB to class number, save it as a new image
            int fileSize = int(rgb_files[i].size());
            img.save(rgb_files[i].insert(fileSize - 4 /*4 = .png*/, "_classIdx").c_str());
//            imwrite(rgb_files[i].insert(fileSize - 4 /*4 = .png*/, "_classIdx"), img);
        }
        
        return 0;
    }
    
    
    
private:
    vector<unsigned char> _class_bgr; // Each class has R, G, and B 3 elements
    bool  _class_bgr_loaded;
    int   _nClass;
    
    
    void _readClassRGBtxt(const string& txtFile)
    {
        string line;
        ifstream myfile (txtFile);
        if (myfile.is_open())
        {
          // Read each line
          while(getline(myfile, line))
          {
            // Extract number in a string line
            vector<int> rgb = this->_string2int(line);
              
            // Check correctness
            if(rgb.size() != 3)
            {
                cout << "Mask2Grayscale::__readClassRGBtxt() error! txt file of class RGB value should be 3. "
                     << rgb.size() << " numbers detected.\n They are: ";
                for (int x = 0; x < rgb.size(); x++)
                    cout << rgb[x] << " ";
                assert(rgb.size() != 3);
            }
            // if correct counts, turn RGB to opencv's BGR format
            // TODO: check number range (0 - 255)
            else
            {
                for (int x = 0; x < rgb.size(); ++x)
                    this->_class_bgr.push_back(rgb[x]);
            }
          }
          myfile.close();
        }
        else
        {
            cout << "Unable to open file. File name: " << txtFile << "\n";
            assert(false);
        }
        
        this->_nClass = int(this->_class_bgr.size() / 3);
        this->_class_bgr_loaded = true;
    }
    
    // Turn a string to nums (Integer only)
    // For example:
    // string tmp = "12 233 168" -> vector<int> tmp{12, 233, 168}
    vector<int> _string2int(string& s)
    {
        vector<int> ans;
        string cache;

        for (int i = 0; i < s.size(); ++i) {
            if(s[i]>=48 && s[i] <=57) // is number
                cache.push_back(s[i]);
            else
            {
                ans.push_back(stoi(cache));
                cache.clear();
            }
        }
        
        ans.push_back(stoi(cache));
        return ans;
    }
    
    // Return class number
    // Ex:
    // class = 0 | background
    // class = 1 | car class
    // class = 2 | pedestrian class
    template<typename _T>
    int _rgbMatching(CImg<_T>& img, int x, int y)
    {
        int count = 0;
        for (int i = 0; i < this->_class_bgr.size(); i+=3)
        {
            if(img(x,y,0) == this->_class_bgr[i]   &&
               img(x,y,1) == this->_class_bgr[i+1] &&
               img(x,y,2) == this->_class_bgr[i+2]
               )
            {
                return count;
            }
            ++count;
        }
        
        assert(false && "_rgbMatching() fail on matching class RGB values between provided images and the text file.");
    }
};


#endif /* Mask2Grayscale_h */
