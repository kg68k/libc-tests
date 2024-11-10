// file position on text mode (type 2)

// libc-test by TcbnErik
// Last-modified: 2024-11-10

// Copying and distribution of this file, with or without modification,
// are permitted in any medium without royalty provided the copyright
// notice and this notice are preserved.  This file is offered as-is,
// without any warranty.

#include <stdio.h>

int main(void) {
  const char file[] = "test.txt";

  FILE* fp = fopen(file, "wt");
  if (!fp) return 1;
  fputs("a\nb\n", fp);
  fclose(fp);

  fp =  fopen(file, "r+t");
  if (!fp) return 1;
  fgetc(fp);  // read 'a'
  fgetc(fp);  // read '\n'
  fseek(fp, ftell(fp), SEEK_SET);
  fputc('X', fp);  // intend to overwrite 'b' with 'X'
  fclose(fp);

  return 0;
}
