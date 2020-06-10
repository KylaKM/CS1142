/* 
Kyla Kane-Maystead
Kakanema
This program is designed to print a snow graph from pairs of information of
a month and snow fall.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char** argv) {
  // If less than one pair input, then provide helpful message.
  if(argc < 3) {
    printf("SnowGraph <month1> <amount1> [<month2> <amount2>] ...\n");
    return 0;
  }

  double sum = 0.0;
  double count = 0.0;
  int  max = 0;
  int  min = 0;
  double input = 0.0;
  
  // If number of arguments is even, then change range of input by -1
  if(argc % 2 == 0) {
    input = argc - 1;
  }
  else {
    input = argc;
  }

  // Look through input, if index is evenly divisible by 2, then check to see 
  // if any values or negative, if not then add to sum. Else, add to counter for
  // the number of months.
  for(int i = 1; i < input; i++) {
    if(i % 2 == 0) { 
      if(atoi(argv[i]) < 0) {
	printf("All amounts must be non-negative!");
	return 0;
      }
      else {
	sum += atof(argv[i]);
      }
    }
    else {
      count++;
    }
  }
 
  max = 2;
  min = 2;
  // Look through the input of snowfall to see which one is the maximum
  // and which one is the minimum.
  for(int i = 2; i < input; i+=2) {
    if(i + 2 < input && atof(argv[max]) <  atof(argv[i + 2])) {
      max = i + 2;
    }
    if(i + 2 < input && atof(argv[min]) > atof(argv[i + 2])) {
      min = i + 2;
    }
  }
  
  double avg  = sum / count;
  char* mon = NULL;
  double amount = 0.0;

  printf("total snow %.2f, average snow %.2f\n", sum, avg);

  // Loop through array of inputs
  for(int k = 1; k < input; k++) {
    // If index is not evenly divisible by 2, then print out name of month.
    if(k % 2 != 0) {
      mon = argv[k];
      printf("%10s: ",mon);
    }
    // If index is evenly divisibly by 2, then print asterisks to the closest
    // integer of the amount of snowfall.
    if(k % 2 == 0) {
      amount = atof(argv[k]);
      for(int i = 0; i < (int) round(amount); i++) {
	printf("*");
      }
      // If only given one pair of elements, then print min and max together.
      if(argc <= 3) {
	printf(" %.1f min max\n", amount);
      }
      // If index is equal to min index, then add on min to print statement.
      else if(k == min) {
	printf(" %.1f min\n", amount);
      }
      // If index is equal to max index, then add on max to print statement. 
      else if(k == max) {
	printf(" %.1f max\n", amount);
      }
      else {
	printf(" %.1f\n", amount);
      }
    }
  }
  return 0;
}
