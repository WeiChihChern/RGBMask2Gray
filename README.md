# RGBMask2Gray
Convert RGB masks for semantic segmentation to grayscale base on its class index. Support .PNG only for now.

### Usage
./RGBMask2Gray -ImagePath ../demo/images -ClassRGBPath ../demo/test.txt <br />
Converted images will be saved in -ImagePath

### Dependency
- CImg
- argparse
