# RGBMask2Gray
Convert RGB masks for semantic segmentation to grayscale base on its class index. Support .PNG only for now.
<p align="center">
  <img width="431" alt="image" src="https://user-images.githubusercontent.com/40074617/114333263-e4318080-9b15-11eb-8b20-46e3fc957794.png">
</p>

## How to use it

#### Demo
```
docker run -it --rm wchern/open:RGBMask2Gray bash -c "./RGBMask2Gray -ImagePath ../demo/images -ClassRGBPath ../demo/test.txt
```
#### Your data
```
docker run -it --rm wchern/open:RGBMask2Gray -v $(pwd):/my-data bash -c "./RGBMask2Gray -ImagePath /my-data/train -ClassRGBPath /my-data/your-own-class-info.txt"
```
- See the figure above to construct your own txt files. The .txt should contain numbers ONLY.</br>
</br>
</br>
### Dependency</br>
- CImg </br>
- argparse
