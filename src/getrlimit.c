// getrlimit()

// libc-test by TcbnErik
// Last-modified: 2025-06-29

// Copying and distribution of this file, with or without modification,
// are permitted in any medium without royalty provided the copyright
// notice and this notice are preserved.  This file is offered as-is,
// without any warranty.

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/resource.h>

static void printResource(const char* name, int resource) {
  struct rlimit rlim;

  if (getrlimit(resource, &rlim) == 0) {
    printf("%-13s: rlim_cur=%10u(0x%08x), rlim_max=%10u(0x%08x)\n", name,
           rlim.rlim_cur, rlim.rlim_cur, rlim.rlim_max, rlim.rlim_max);
  } else {
    printf("%-13s: %s\n", name, strerror(errno));
  }
}

int main(void) {
  printf("RLIM_INFINITY = 0x%08x\n", RLIM_INFINITY);

  printResource("RLIMIT_CPU", RLIMIT_CPU);
  printResource("RLIMIT_FSIZE", RLIMIT_FSIZE);
  printResource("RLIMIT_DATA", RLIMIT_DATA);
  printResource("RLIMIT_STACK", RLIMIT_STACK);
  printResource("RLIMIT_CORE", RLIMIT_CORE);
  printResource("RLIMIT_RSS", RLIMIT_RSS);
  printResource("RLIMIT_NOFILE", RLIMIT_NOFILE);

  return 0;
}
