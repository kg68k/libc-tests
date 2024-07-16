// file position on text mode
//   https://x.com/kg68k/status/1601896787207258112

// libc-test by TcbnErik
// Last-modified: 2024-07-17

// Copying and distribution of this file, with or without modification,
// are permitted in any medium without royalty provided the copyright
// notice and this notice are preserved.  This file is offered as-is,
// without any warranty.

#include <stdio.h>
#include <stdlib.h>

#ifdef _MSC_VER
#pragma warning(disable : 4996)
#endif

FILE* openFile(const char* filename, const char* text) {
  FILE* fp = fopen(filename, "rt");
  if (fp) return fp;

  fp = fopen(filename, "wb");
  if (fp) {
    fputs(text, fp);
    fclose(fp);
    fp = fopen(filename, "rt");
  }
  if (fp) return fp;

  perror(filename);
  return NULL;
}

int main(void) {
  const char filename[] = "textmode.txt";
  const char text[] =
      "A"
      "\x0d"
      "\x0a"
      "B";
  int c;

  FILE* fp = openFile(filename, text);
  if (!fp) return EXIT_FAILURE;

  do {
    long pos = ftell(fp);
    c = fgetc(fp);
    printf("ftell=%ld, fgetc=0x%02x\n", pos, c);
  } while (c != EOF);

  return EXIT_SUCCESS;
}
