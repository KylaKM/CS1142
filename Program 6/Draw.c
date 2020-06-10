/*
Kyla Kane-Maystead
kakanema
Description : This program is designed to create images from an input file 
that has a sequence of instructions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <float.h>

/*
  This method initializes a 2D array with 0.0. 
  Input: width of array, height of array, and multidimensional array
 */
void initImage(int width, int height, double image[width][height]) {
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++) {
      image[j][i] = 0.0;  // Initializes every element to 0.0
    }
  }
}

/*
  This method prints out the elements of the array to make image.
  Input: width of array, height of array, multidimensional array
 */
void printImage(int width, int height, double image[width][height]) {
  // Prints out the header 
  printf("+");
  int x = 1;
  while(x <= width) {
    printf("-");
    x++;
  }
  printf("+\n");

  // Prints out the side bars and the pixels
  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
      if(j == 0) {
	printf("|");
      }
      if(image[j][i] < 0.2) {
	printf(" "); // Prints Space
      }
      else if(image[j][i] < 0.4) {
	printf("."); // Prints .
      }
      else if(image[j][i] < 0.6) {
	printf("o"); // Prints o
      }
      else if(image[j][i] < 0.8) {
	printf("O"); // Prints O
      }
      else {
	printf("@"); // Prints @
      }
    }
    printf("|");
    printf("\n");
  }
  
  // Prints out bottom bar
  printf("+");
  x = 1;
  while(x <= width) {
    printf("-");
    x++;
  }
  printf("+\n");
}

/*
  This method changes the value of a multidimensional array at a certain point.
  Input: width of array, height of array, 2D array, x-coordinate, y-coordinate, color
 */
void drawPoint(int width, int height, double image[width][height], int x, int y, double color) {
  if((x <  width) && (x >= 0)) {
    if((y < height) && (y >= 0)) {
      image[x][y] = color;  // As long as point is in range, change point to color
    }
  }
  else {
    return;
  }
} 

/*
  This method fills a rectangle with a certain color.
  Input: width of array, height of array, 2D array, leftmost coordinate
  topmost coordinate, width of rectangle, height of rectangle, color
 */
void drawRectangle(int width, int height, double image[width][height], int left, int top, int rectangleWidth, int rectangleHeight, double color) { 
  int h = top;
  int w = left;
  for(int i = 0; i < rectangleWidth; i++) {
    for(int j = 0; j < rectangleHeight; j++) {
      h = j + top;
      w = i + left;
      if(h < height && h >= 0) {
	if(w < width && w >= 0) {
	  image[w][h] = color;  // Fills Coordinates with color to make rectangle
	}
      }
    }
  }
}

/*
  This method calculates the min, max, and average pixel in the image.
  Input: width of array, height of array, 2D array, pointer to minColor,
  pointer to maxColor, pointer to avgColor
 */
void getImageStats(int width, int height, double image[width][height], double *minColor, double *maxColor, double *avgColor) {
  *minColor = DBL_MAX;
  *maxColor = DBL_MIN;
  double sum = 0.0;
  int count = 0;

  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
      sum += image[j][i];
      if(image[j][i] < *minColor) {  // If smaller than min, new min
	*minColor = image[j][i];
      }
      else if(image[j][i] > *maxColor) {  // If greater than max, new max
	*maxColor = image[j][i];
      }
      count++;
    }
  }
  if(count == 1) {
    *maxColor = *minColor;
  }
  *avgColor = (double) (sum / count);
}

/*
  This method
  Input: width of array, height of array, 2D array, x-coordinate, y-coordinate, color
 */
void floodFill(int width, int height, double image[width][height], int x, int y, double color) { 
  if(image[x][y] >= color) {
    return;
  }
  if(x < 0 || x >= width) {
    return;
  }
  if(y < 0 || y >= height) {
    return;
  }
  
  image[x][y] = color;
  
  floodFill(width, height, image, x - 1, y, color); // Fills in Left Direction
  floodFill(width, height, image, x, y - 1, color); // Fills in Up Direction
  floodFill(width, height, image, x + 1, y, color); // Fills in Right Direction
  floodFill(width, height, image, x, y + 1, color); // Fills in Down Direction
}

// Read in a set of drawing instructions from standard input.
// Print the resulting greyscale image as ASCII art. 
// DO NOT MODIFY!
int main(void)
{
   // Read in the size of the drawing canvas
   int width = 0;
   int height = 0;
   int result = scanf("%d %d", &width, &height);
   
   // Program only supports images that are 1x1 or bigger
   if ((width <= 0) || (height <= 0) || (result != 2))
   {
      printf("Failed to read a valid width and height from standard input!\n");
      return 0;
   }
   
   // Create the 2D arary and initialize all the greyscale values to 0.0
   double image[width][height];
   initImage(width, height, image);
   
   char command = '\0';
   double color = 0.0;
   
   // Keep reading in drawing commands until we reach the end of the input
   while (scanf(" %c", &command) == 1)
   {
      switch (command)
      {		
         case 'p': 	
         {
            // Draw a point, read in: x, y, color
            int x = 0;
            int y = 0;
            result = scanf("%d %d %lf", &x, &y, &color);
            if (result != 3)
            {
               printf("Invalid point command!\n");
               return 0;
            }
            
            drawPoint(width, height, image, x, y, color);
            break;
         }

         case 'r': 	
         {
            // Draw a rectangle, read in: x, y, w, h, color
            int left = 0;
            int top = 0;
            int rectangleWidth = 0;
            int rectangleHeight = 0;
            result = scanf("%d %d %d %d %lf", &left, &top, &rectangleWidth, &rectangleHeight, &color);
            if (result != 5)
            {
               printf("Invalid rectangle command!\n");
               return 0;
            }
         
            drawRectangle(width, height, image, left, top, rectangleWidth, rectangleHeight, color);
            break;
         }

         case 'f':
         {
            // Flood fill a color in, read in: x, y, color
            int x = 0;
            int y = 0;
            result = scanf("%d %d %lf", &x, &y, &color);
            if (result != 3)
            {
               printf("Invalid flood fill command!\n");
               return 0;
            }
            
            floodFill(width, height, image, x, y, color);
            break;
         }

         default:
         {
            printf("Unknown command!\n");
            return 0;
         }
      }
   }
   
   // Print the final image
   printImage(width, height, image);
   
   // Finally display some statistics about the image
   double minColor = 0.0;
   double maxColor = 0.0;
   double avgColor = 0.0;
   getImageStats(width, height, image, &minColor, &maxColor, &avgColor);
   printf("Color range [%.2f, %.2f], average %.4f\n", minColor, maxColor, avgColor);
}
