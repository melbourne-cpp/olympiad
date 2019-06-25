# Pixel Blending

## Challenge

This is a simple pixel blending challenge which could benefit from multithreading, SIMD and even GPGPU techniques, such as CUDA.

The challenge is to take an image containing a number of sprites (i.e a spritesheet) and to blend the pixels in those sprites following the algorithm described below.

## Algorithm

Calculate the final pixel values by doing the following:

* Declare a variable "result" which is a 2D array of 3D vector. Initialise it with the size a x c and all zero values. This array will contain the final pixel outputs for the output file.
* Iterate over all `n` sprites in the spritesheet.
* Within each loop, update the "result" by doing the following calculation:
```
result.r = result.r * 0.5 + subimage[index].r * 0.5
result.g = result.g * 0.5 + subimage[index].g * 0.5
result.b = result.b * 0.5 + subimage[index].b * 0.5
```
* where `index` is the loop iteration number
* `subimage[index]` refers to the sub-image within the input file where the pixel starts from x: 0 and y: "c" x "index".
* `r`, `g` and `b` represent the corresponding color values.

## Dataset

### Input file

1. Input file is an image file in .PPM (Portable Pix Map) extension. 
More info on PPM here - https://www.cs.swarthmore.edu/~soni/cs35/f13/Labs/extras/01/ppm_info.html
* For this challenge, we will restrict the first header line to be "P3" and the max color range to be 255.
2. The image file is of size a x b. (a is the column pixel count and b is the row pixel count)
3. The image can be thought of as a "spritesheet", a list of images of size a x c combined into one. (where "b" is a multiple of "c")

Example:

![Sample input image](./sample/input.png)

### Output file

1. Output file will also be an image file in PPM format.
2. The image file should be of size a x c (where "b" is dividable by "c" )

## Credits

Thanks to [Jessub Kim](https://github.com/JessubKim), who originally proposed this challenge [here](https://github.com/JessubKim/CppMeetup-OlympiadSubmission-PixelBlending).
