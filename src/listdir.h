//
//  listdir.h
//  rgb_mask_to_grayscale
//
//  Created by Wei Chih Chern on 3/3/21.
//

#ifndef listdir_h
#define listdir_h

#include <filesystem> // C++17 required
#include <vector>
#include <string>


namespace fs = std::filesystem;
using namespace std;

namespace listdir
{
    vector<string> listdir(const string& path)
    {
        int count = 0;
        for (const auto & entry : fs::directory_iterator(path))  ++count;
        vector<string> files(count);
        count = 0;
        
        for (const auto & entry : fs::directory_iterator(path))
            files[count++] = entry.path().string();
        
        return files;
    }
}

#endif /* listdir_h */
