/*
Kyla Kane-Maystead
Kakanema
This program is designed to convert rainfall to snow.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char** argv) {
  // If number of inputs is less than expected, provide helpful message.
  if(argc < 3) {
    printf("RainToSnow <inches of rain> <Fahrenheit temperature> \n");
    return 0;
  }
 
 double rain = atof(argv[1]);
 
 // If the rain is negative, print error and terminate.
 if(rain < 0) {
    printf("Amount of rain must be non-negative!\n");
    return 0;
  }

  double temp = atof(argv[2]);
  double snow = 0.0;
  
  // Depending on what the temp the range is in, it will 
  // multiply the rainfall by a certain factor.
  if(temp >= 32) {
    snow = 0.0;
  }
  if(temp >= 27 && temp < 32) {
    snow = 10 * rain;
  }
  if(temp >= 20 && temp < 27) {
    snow = 15 * rain;
  }
  if(temp >= 15 && temp < 20) {
    snow = 20 * rain;
  }
  if(temp >= 10 && temp < 15) {
    snow = 30 * rain;
  }
  if(temp >= 0 && temp < 10) {
    snow = 40 * rain;
  }
  if(temp >= -20 && temp < 0) {
    snow = 50 * rain;
  }
  if(temp < -20) {
    snow = 100 * rain;
  }
  
  printf("%.1f inches of rain ", rain);
  printf("at %.1fF would result in ", round(temp));
  printf("%.1f inches of snow.\n", snow);
 
  // If snow is less than 108 inches, then find percentage of Husky statue covered.
  if (snow < 108) {
    double  covered = (snow / 108) * 100;
    printf("This would cover about %d%% ", (int) round(covered));
  }

  // If snow is greater than or equal to 108 inches, then it will cover all of the statue.
  if (snow >= 108) {
    printf("This would cover all ");
  }
  printf("of the Husky statue!\n");
  return 0;
}
