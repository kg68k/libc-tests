// file position on text mode (type 3)

// libc-test by TcbnErik
// Last-modified: 2025-01-02

// Copying and distribution of this file, with or without modification,
// are permitted in any medium without royalty provided the copyright
// notice and this notice are preserved.  This file is offered as-is,
// without any warranty.

// This test passes with LIBC but fails with MSVC.
// https://developercommunity.visualstudio.com/t/425878
//   Fseek & ftell fail in text mode for unix style text files

#include <stdio.h>

int main(void) {
  const char file[] = "test3.txt";

  FILE* fp = fopen(file, "wb");
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
