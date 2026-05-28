#include "helpers.h"

// Convert image to grayscale
#include <math.h> // This must be at the top of your helpers.c file

void grayscale(int height, int width, RGBTRIPLE image[height][width]) {
  for (int h = 0; h < height; h++) {
    for (int w = 0; w < width; w++) {
      // Get original RGB values
      BYTE red = image[h][w].rgbtRed;
      BYTE green = image[h][w].rgbtGreen;
      BYTE blue = image[h][w].rgbtBlue;

      // Calculate average with proper rounding
      int avg = round((red + green + blue) / 3.0);

      // Set all three channels to the same average value
      image[h][w].rgbtRed = avg;
      image[h][w].rgbtGreen = avg;
      image[h][w].rgbtBlue = avg;
    }
  }
}

// Reflect image horizontally
// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]) {
  // Loop through each row
  for (int h = 0; h < height; h++) {
    // Loop through half the columns (swap left with right)
    for (int w = 0; w < width / 2; w++) {
      // Calculate the mirror position
      int mirror = width - 1 - w;

      // Swap the two pixels
      RGBTRIPLE temp = image[h][w];
      image[h][w] = image[h][mirror];
      image[h][mirror] = temp;
    }
  }
  return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]) {
  // Create a temporary copy to store original values
  RGBTRIPLE temp[height][width];

  // Copy original image to temp
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      temp[i][j] = image[i][j];
    }
  }

  // Now blur using the temp image for calculations
  for (int h = 0; h < height; h++) {
    for (int w = 0; w < width; w++) {
      int count = 0;
      int totalr = 0;
      int totalb = 0;
      int totalg = 0;

      for (int i = h - 1; i <= h + 1; i++) {
        // Check if row is valid
        if (i < 0 || i >= height) {
          continue;
        }

        for (int j = w - 1; j <= w + 1;
             j++) // Fixed: was j <= j+1, now j <= w+1
        {
          // Check if column is valid
          if (j < 0 || j >= width) {
            continue;
          }

          // Use TEMP image for calculations, not the original
          BYTE red = temp[i][j].rgbtRed;
          BYTE green = temp[i][j].rgbtGreen;
          BYTE blue = temp[i][j].rgbtBlue;

          totalr = totalr + red;
          totalg = totalg + green;
          totalb = totalb + blue;
          count = count + 1;
        }
      }

      // Update the ORIGINAL image with averages
      // Add 0.5 for proper rounding
      image[h][w].rgbtRed = (int)((totalr / (float)count) + 0.5);
      image[h][w].rgbtGreen = (int)((totalg / (float)count) + 0.5);
      image[h][w].rgbtBlue = (int)((totalb / (float)count) + 0.5);
    }
  }

  return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width]) {
  int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}}; // Fixed: Use {} not []
  int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}}; // Fixed: Use {} not []

  RGBTRIPLE temp[height][width];

  // Copy original image to temp
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      temp[i][j] = image[i][j];
    }
  }

  for (int h = 0; h < height; h++) {
    for (int w = 0; w < width; w++) {
      // Initialize variables INSIDE the loops, before calculations
      int totalredx = 0, totalgreenx = 0, totalbluex = 0;
      int totalredy = 0, totalgreeny = 0, totalbluey = 0;

      for (int i = h - 1, x = 0; i <= h + 1; i++, x++) // x tracks Gx/Gy row
      {
        // Check if row is valid
        if (i < 0 || i >= height) {
          x--; // Adjust x since we skipped this row
          continue;
        }

        for (int j = w - 1, y = 0; j <= w + 1;
             j++, y++) // y tracks Gx/Gy column
        {
          // Check if column is valid
          if (j < 0 || j >= width) {
            y--; // Adjust y since we skipped this column
            continue;
          }

          // Use TEMP image for calculations
          // Note: temp[i][j] not temp[j][i] - rows then columns
          int red = temp[i][j].rgbtRed;
          int green = temp[i][j].rgbtGreen;
          int blue = temp[i][j].rgbtBlue;

          // Apply Sobel operators
          totalredx += red * Gx[x][y];
          totalgreenx += green * Gx[x][y];
          totalbluex += blue * Gx[x][y];

          totalredy += red * Gy[x][y];
          totalgreeny += green * Gy[x][y];
          totalbluey += blue * Gy[x][y];
        }
      }

      // Calculate final values: sqrt(Gx^2 + Gy^2)
      // In C, ^ is XOR, not power! Use multiplication or pow()
      int totalred = (int)round(
          sqrt((double)(totalredx * totalredx + totalredy * totalredy)));
      int totalgreen = (int)round(sqrt(
          (double)(totalgreenx * totalgreenx + totalgreeny * totalgreeny)));
      int totalblue = (int)round(
          sqrt((double)(totalbluex * totalbluex + totalbluey * totalbluey)));

      // Cap values at 255
      image[h][w].rgbtRed = (totalred > 255) ? 255 : totalred;
      image[h][w].rgbtGreen = (totalgreen > 255) ? 255 : totalgreen;
      image[h][w].rgbtBlue = (totalblue > 255) ? 255 : totalblue;
    }
  }
  return;
}
