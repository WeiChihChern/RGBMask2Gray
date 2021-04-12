# RGBMask2Gray
Convert RGB masks for semantic segmentation to grayscale with user given text file. Support .PNG only for now.
<p align="center">
  <img width="444" alt="image" src="https://user-images.githubusercontent.com/40074617/114411631-5c319200-9b7a-11eb-9191-2f410ed14f88.png">
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

### Dependency
- CImg </br>
- argparse
