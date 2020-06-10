/*
Kyla Kane-Maystead
Kakanema
Description: This program utilizes a key to encrypt/decrypt data.
*/

#include "Key.h"
#include "Checksum.h"
#include <stdio.h>
#include <stdlib.h>

bool initKey(Key* key, const char* filename) {
  FILE* keyf = fopen(filename, "rb");
  int i = 0;
  unsigned char* d = key->data;
  if(keyf == NULL) {
    printf("Failed to load any file: %s\n", filename);
    return false;
  }

  int t = 0;
  while((t = fgetc(keyf)) != EOF) {
    i++;
  }
  
  // Beginning of file
  fseek(keyf, 0, SEEK_SET);
  d = (unsigned char*) malloc(i * sizeof(unsigned char));
  i = 0;
  
  // Goes through and puts number from file into array and increases count
  while(1) {
    if((t = fgetc(keyf)) == EOF) {
      break;
    }
    d[i] = (unsigned char) t;
    i++;
  }

  key->data = d;
  key->size = i;
  key->pos = 0;
  fclose(keyf);
  return true;
}

void uninitKey(Key* key) {
  free(key->data);
}

unsigned char transformUsingKey(Key* key, unsigned char inByte, Checksum* inChecksum, Checksum* outChecksum, bool debug) {
  unsigned char* d = key->data;
  unsigned char n;
  n = d[key->pos] ^ (unsigned char) inByte;

  updateChecksum(inChecksum, inByte);
  updateChecksum(outChecksum, n);

  if(debug) {
    printf("%3d ^ %3d -> %3d \n", inByte, d[key->pos], n);
  }
  key->pos = (key->pos+1) % (key->size);
  return n;
}
