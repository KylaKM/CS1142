/*
Kyla Kane-Maystead
Kakanema
This program is designed to find a path from east to west with the minimum 
amount of elevation change.
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/*
  Method to return the difference in elevation between
  current point and up, down, or forward.
 */
int cost(int x, int y) {
  int cost = x - y;
  return abs(cost);
}

/*
  Method to return the minimum difference in 
  elevation between up, down, or forward.
 */
int min(int x, int y, int z) {
  if(x < y) {
    if(x < z) {
      return 0;    // Returning 0 is equivalent to going up is the least difference in elevation
    }
    else {
      return 2;    // Returning 2 is equivalent to going down is the best option
    }
  }
  else {
    if(y <= z) {
      return 1;    // Returning 1 is equivalent to going forward is the best option.
    }
    else {
      return 2;
    }
  }
}

/*
  Method to find and print the best path from beginning of data
 */
int path(int mode, int row, int width, int height, int data[width][height]) {
  int totalCost = 0;
  int elevation = data[0][row];
  int j = row;
  // If verbose mode print out
  if(mode) {
    printf("(0,%d) %d", j, elevation);
  }

  for(int i = 1; i < width; i++) {
    int forward = data[i][j];
    int up = INT_MIN;
    int down = INT_MIN;
    if(j > 0) {
      up = data[i][j - 1];
    }
    if(j < height - 1) {
      down = data[i][j + 1];
    }
    int fcost = cost(elevation, forward);  //Difference in elevatin between current and forward
    int ucost = INT_MAX;                  
    int dcost = INT_MAX;
    if(up != INT_MIN) {
      ucost = cost(elevation, up);  //Difference in elevation between current and up
    }
    if(down != INT_MIN) {
      dcost = cost(elevation, down);  //Difference in elevation between current and down
    }

    int selection = min(ucost, fcost, dcost);   // Calls to find the minimum cost between all 3 of the choices
    if(selection == 0) {    // If 0, then go up and adjust variables 
      j--;
      totalCost += ucost;
      elevation = up;
      // Verbose mode
      if(mode) {
	printf(" U, ");
      }
    }
    else if(selection == 1) {  // If 1, then go forward and adjust variables
      totalCost += fcost;
      elevation = forward;
      // Verbose mode
      if(mode) {
	printf(" F, ");
      }
    }
    else {                   // If 2, then go down and adjust variables
      j++;
      totalCost += dcost;
      elevation = down;
      // Verbose mode
      if(mode) {
	printf(" D, ");
      }
    }
    // Verbose mode
    if(mode) {
	printf("(%d,%d) %d", i, j, elevation);
    }
  }
  // Verbose mode
  if(mode) {
    printf(", cost %d\n", totalCost);
  }
  return totalCost;
}

/*
  Method to simulate a Greedy algorithm that chooses the best
  direction to go depending on difference in elevation.
 */
void greedy(int mode, int width, int height, int data[width][height]) {
  int bestCost = INT_MAX;
  int bestRow = -1;
  for(int i = 0; i < height; i++) {
    int cost = path(mode, i, width, height, data);  // Calls to find the best path from starting point to the right 
    if(cost < bestCost) {
      bestCost = cost;
      bestRow = i;
    }
  }
  printf("Best: row %d, cost %d\n", bestRow, bestCost);
}

int main(int argc, char** argv) {
  int mode = 0;
  // If user enters a number along with file, then trigger verbose mode
  if(argc >= 2) {
    mode = atoi(argv[1]);
  }

  int columns = 0;
  int rows = 0;
  // Get width and height of data
  scanf("%d", &rows);
  scanf("%d", &columns);
  int range = columns * rows;
  double avg = 0.0;
  int max = INT_MIN;
  int min = INT_MAX;
  int a[rows][columns];
  
  for(int i = 0, j = 0, k = 0; k < range; k++) {
    int elevation = 0; 
    scanf("%d", &elevation);
    a[i][j] = elevation;
    avg += elevation;
    if(max < elevation) {
      max = elevation;
    }
    if(min > elevation) {
      min = elevation;
    }
    i++;
    if(i == rows) {
      j++;
      i = 0;
    }
  }

  avg /= range;
  printf("Data points: %d\n", range);
  printf("Avg elevation: %.2f\n", avg);
  printf("Min elevation: %d\n", min);
  printf("Max elevation: %d\n", max);
  
  greedy(mode, rows, columns, a);
  return 0;
}
