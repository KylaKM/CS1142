/*
Kyla Kane-Maystead
Kakanema
This program is designed to simulate a madlib usint the song Let It Snow.
*/
#include <stdio.h>
#include <stdlib.h>

int main(int arc, char** argv) {
  // If less than expected number of inputs, provide helpful message.
  if(arc < 7){
    printf("LetItSnow <noun> <adjective> <noun> <adjective> <verb> <verb> \n");
    return 0;
  }

  // Set all of the inputs to a variable to print
  char* noun1 = argv[1];
  char* adjective1 = argv[2];
  char* noun2 = argv[3];
  char* adjective2 = argv[4];
  char* verb1 = argv[5];
  char* verb2 = argv[6];

  // Print out the inputs into the madlib
  printf("Oh, the %s outside is %s,\n", noun1, adjective1 );
  printf("But the %s is so %s,\n", noun2, adjective2);
  printf("And since we've no place to %s,\n", verb1);
  printf("Let it %s, ", verb2);
  printf("Let it %s, ", verb2);
  printf("Let it %s! \n", verb2);
  return 0;
}
