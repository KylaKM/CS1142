/*
Kyla Kane-Maystead
Kakanema
Description: This program keeps track of the most and least significant digits of a 16-bit and transforms it to 4-digit hexadecimal.
 */
#include "Checksum.h"
#include <stdio.h>
#include <stdlib.h>
void initChecksum(Checksum* checksum) {
  checksum->sum1 = 0;
  checksum->sum2 = 0;
}

void updateChecksum(Checksum* checksum, unsigned char byte) {
  checksum->sum1 = (checksum->sum1 + byte) % 255;
  
  checksum->sum2 = (checksum->sum2 + checksum->sum1) % 255;
}

void getChecksum(Checksum* checksum, char str[]) {
  int temp = checksum->sum2 * 256 + checksum->sum1;
  sprintf(str, "%04X", temp);
}
