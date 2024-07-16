// opendir(), readdir() and closedir()

// libc-test by TcbnErik
// Last-modified: 2024-07-17

// Copying and distribution of this file, with or without modification,
// are permitted in any medium without royalty provided the copyright
// notice and this notice are preserved.  This file is offered as-is,
// without any warranty.

#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#if defined(__HUMAN68K__) && defined(__LIBC__)
#ifndef _DIRENT_HAVE_D_RECLEN
#define _DIRENT_HAVE_D_RECLEN
#endif
#ifndef _DIRENT_HAVE_D_NAMLEN
#define _DIRENT_HAVE_D_NAMLEN
#endif
#endif

#ifdef _DIRENT_HAVE_D_TYPE
static const char* DTypeToString(unsigned char dt) {
  switch (dt) {
    default:
      return "???";

    case DT_BLK:
      return "DT_BLK";
    case DT_CHR:
      return "DT_CHR";
    case DT_DIR:
      return "DT_DIR";
    case DT_FIFO:
      return "DT_FIFO";
    case DT_LNK:
      return "DT_LNK";
    case DT_REG:
      return "DT_REG";
    case DT_SOCK:
      return "DT_SOCK";
    case DT_UNKNOWN:
      return "DT_UNKNOWN";
#ifdef DT_WHT
    case DT_WHT:
      return "DT_WHT";
#endif
  }
}
#endif

static void PrintDirent(const struct dirent* d) {
  printf("d_name=\"%s\"", d->d_name);
  printf(", d_ino=%d", (int)d->d_ino);

#ifdef _DIRENT_HAVE_D_OFF
  printf(", d_off=%d", (int)d->d_off);
#endif

#ifdef _DIRENT_HAVE_D_RECLEN
  printf(", d_reclen=%d", d->d_reclen);
#endif

#ifdef _DIRENT_HAVE_D_NAMLEN
  printf(", d_namlen=%d", d->d_namlen);
#endif

#ifdef _DIRENT_HAVE_D_TYPE
  printf(", d_type=%d(%s)", d->d_type, DTypeToString(d->d_type));
#endif

  printf("\n");
}

int main(int argc, char* argv[]) {
  const char* path = (argc < 2) ? "" : argv[1];

  DIR* dir = opendir(path);
  if (!dir) {
    perror(path);
    return EXIT_FAILURE;
  }

  for (;;) {
    struct dirent* d;

    errno = 0;
    d = readdir(dir);
    if (!d) {
      if (errno == 0) break;  // end of directory
      perror(NULL);
      return EXIT_FAILURE;
    }

    PrintDirent(d);
  }

#if defined(__HUMAN68K__) && defined(__LIBC__)
  closedir(dir);
#else
  if (closedir(dir) != 0) {
    perror(NULL);
    return EXIT_FAILURE;
  }
#endif

  return EXIT_SUCCESS;
}
