// maxmem()

// libc-test by TcbnErik
// Last-modified: 2025-06-29

// Copying and distribution of this file, with or without modification,
// are permitted in any medium without royalty provided the copyright
// notice and this notice are preserved.  This file is offered as-is,
// without any warranty.

#include <stdio.h>
#include <stdlib.h>

#define BITS 24

typedef struct {
  size_t size;
  unsigned int ptr;
} Result;

size_t GetMaxMemorySize(Result* results) {
  size_t size = 0;

  int i;
  for (i = 0; i < BITS; i += 1) {
    size_t trySize = size | ((1 << BITS) >> i);
    void* p = malloc(trySize);

    results[i].size = trySize;
    results[i].ptr = (unsigned int)p;
    if (p) {
      free(p);
      size = trySize;
    }
  }

  return size;
}

int main(int argc, char* argv[]) {
  Result results[BITS];
  size_t size;
  int i;

  if (argc > 1) {
    void* p = malloc(7 * 1024 * 1024);
    printf("%p\n", p);
    if (p) free(p);
  }

  size = GetMaxMemorySize(results);

  for (i = 0; i < BITS; i += 1) {
    printf("size = 0x%08x, p = 0x%08x\n", (unsigned int)results[i].size,
           results[i].ptr);
  }
  printf("%u\n", (unsigned int)size);

  return 0;
}
