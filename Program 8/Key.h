/*
Kyla Kane-Maystead
Kakanema
Description: Header file for Key.c
 */
#include "Checksum.h"
#ifndef Key_H
#define Key_H

#ifndef bool
typedef int bool;

#define true 1
#define false 0

#endif

typedef struct
{
  unsigned char* data;   // Stores data for this key
  int size;              // How many bytes long key is
  int pos;               // Current position in the key to use for next encoding/decoding
}Key;

// Initialize and load from given filename, returns false if loading of key failed or if the key was 0 bytes in length
bool initKey(Key* key, const char* filename);

// Deallocate any memory used by key structure
void uninitKey(Key* key);

// Encode/decode a byte using the current position in the key returning the result byte
// Updates input and output stream checksums, optionally prints a debug line
unsigned char transformUsingKey(Key* key, unsigned char inByte, Checksum* inChecksum, Checksum* outChecksum, bool debug);

#endif
