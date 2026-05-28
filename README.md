# image-filters
Filter (more) - CS50 Problem Set 4
An image filtering program that applies various effects to BMP images using Sobel edge detection and other filters.

🎨 The Filters
This program applies four image filters:

Grayscale - Converts image to black and white

Reflection - Horizontally flips the image

Blur - Box blur using average of neighboring pixels

Edges - Sobel operator for edge detection (the "more" part)

🛠️ How It Works
The program reads a 24-bit uncompressed BMP file, applies the specified filter, and writes a new BMP file.

Edge Detection (Sobel Operator)
Uses Gx and Gy kernels to detect intensity changes

Computes gradient magnitude across both axes

Detects horizontal, vertical, and diagonal edges

Other Filters
Grayscale: Average of RGB values

Reflection: Reverse pixel order per row

Blur: Average of 3x3 pixel neighborhood

📁 Files
helpers.c - Contains all filter implementations

helpers.h - Function declarations

bmp.h - BMP file structure definitions

filter.c - Main program logic

Makefile - Build configuration

🔧 Implementation Highlights
Edge detection with Sobel operators

Proper handling of image borders in convolution

Temporary buffers to prevent overwriting issues

RGB color manipulation at bit level

✅ Compilation & Testing
bash
make filter
./filter -e input.bmp output.bmp   # Edges
./filter -g input.bmp output.bmp   # Grayscale
./filter -b input.bmp output.bmp   # Blur
./filter -r input.bmp output.bmp   # Reflect
Passed CS50 check50 and all test cases.
