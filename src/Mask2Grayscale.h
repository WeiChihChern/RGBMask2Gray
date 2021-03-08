//
//  Mask2Grayscale.h
//  rgb_mask_to_grayscale
//
//  Created by Wei Chih Chern on 3/3/21.
//

#ifndef Mask2Grayscale_h
#define Mask2Grayscale_h

#include "listdir.h"
#include "opencv2/opencv.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <stdlib.h>

using namespace std;
using namespace cv;


class Mask2Grayscale {
public:
    
    Mask2Grayscale() : _class_bgr_loaded(false), _class_bgr(3,0)/*background class*/{};
    
    
    // Where you have RGB masks already and want to conver it to grayscale encoded instead
    // Support .PNG image format for now only
    int convert(const string& path, const string& txtBGRcode)
    {
        cout << "This app supports .PNG images only for now\n\n\n";
        
        // Read all file names
        vector<string> rgb_files = listdir::listdir(path);
        
        // Read each class's RGB values
        this->_readClassRGBtxt(txtBGRcode);
        
        // Start processing
        #pragma omp parallel for
        for (size_t i = 0; i < rgb_files.size(); ++i) {
            if(
               rgb_files[i].find(".DS_Store") != -1 || // Mac specific hidden file
               rgb_files[i].find("classIdx")  != -1    // Prevent user run the app without removing previous generated files
               )
                continue; // Exist for Mac
            Mat        img = imread(rgb_files[i]);
            uchar *img_ptr = img.ptr<uchar>(0);
            
            // Match rgb values with recorded class color from txtBGRcode
            for (size_t j = 0; j < img.rows*img.cols*img.channels(); j+=3) {
                int classIdx   = this->_rgbMatching(img_ptr+j);
                *(img_ptr+j)   = classIdx;
                *(img_ptr+j+1) = classIdx;
                *(img_ptr+j+2) = classIdx;
            }
            
            // Finished convert RGB to class number, save it as a new image
            int fileSize = int(rgb_files[i].size());
            imwrite(rgb_files[i].insert(fileSize - 4 /*4 = .png*/, "_classIdx"), img);
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
            vector<int> bgr = this->_string2int(line);
            
              
            // Check correctness
            if(bgr.size() != 3)
            {
                cout << "Mask2Grayscale::__readClassRGBtxt() error! txt file of class RGB value should be 3. "
                     << bgr.size() << " numbers detected.\n They are: ";
                for (int x = 0; x < bgr.size(); x++)
                    cout << bgr[x] << " ";
                assert(bgr.size() != 3);
            }
            // if correct counts, turn RGB to opencv's BGR format
            // TODO: check number range (0 - 255)
            else
            {
                for (int x = bgr.size()-1; x > -1; --x)
                    this->_class_bgr.push_back(bgr[x]);
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
    int _rgbMatching(uchar* img_ptr)
    {
        int count = 0;
        for (int i = 0; i < this->_class_bgr.size(); i+=3) {
            if(*(img_ptr)   == this->_class_bgr[i]   &&
               *(img_ptr+1) == this->_class_bgr[i+1] &&
               *(img_ptr+2) == this->_class_bgr[i+2]
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
