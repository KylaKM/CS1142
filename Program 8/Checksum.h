/*
Kyla Kane-Maystead
Kakanema
Description: Header file for Checksum.c
 */
#ifndef Checksum_H
#define Checksum_H

typedef struct 
{
  unsigned char sum1;
  unsigned char sum2;
}Checksum;

// Initialize a checksum structure
void initChecksum(Checksum* checksum);

// Update the checksum sum members based on a byte of data
void updateChecksum(Checksum* checksum, unsigned char byte);

// Return a 16-bit checksum in str as a 4-digit hexadecimal number
// Assumes str has at least 5 bytes allocated to it
void getChecksum(Checksum* checksum, char str[]);

#endif
