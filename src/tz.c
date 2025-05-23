// TZ buffer overflow test

// libc-test by TcbnErik
// Last-modified: 2025-05-24

// Copying and distribution of this file, with or without modification,
// are permitted in any medium without royalty provided the copyright
// notice and this notice are preserved.  This file is offered as-is,
// without any warranty.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// LIBC src/tzone/tzset.c

int main(int argc, char* argv[]) {
  // zonetime_sub() temp[]のバッファオーバーフロー
  putenv("TZ=JST-99999999999999999999999999");
  tzset();

  // monthsday_get() days[]を
  // daydigit_get()で書き込むときにバッファオーバーフロー
  putenv("TZ=JST-9:TEST-9:M0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0");
  tzset();

  // monthsday_get() tims[]を
  // daydigit_get()で書き込むときにバッファオーバーフロー
  putenv("TZ=JST-9:TEST-9:M0.0.,0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0");
  tzset();

  // julian_get() tims[]を
  // daydigit_get()で書き込むときにバッファオーバーフロー
  #define Z "0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:"
  putenv("TZ=JST-9:TEST-9:J10," Z Z Z Z "0");
  tzset();

  // 夏時間の終了日時の解析でもこの上の二つと同様の処理があるが省略

  return 0;
}
