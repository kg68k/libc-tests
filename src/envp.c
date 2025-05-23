// Changing environment variables during startup.

// libc-test by TcbnErik
// Last-modified: 2025-05-23

// Copying and distribution of this file, with or without modification,
// are permitted in any medium without royalty provided the copyright
// notice and this notice are preserved.  This file is offered as-is,
// without any warranty.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef __HUMAN68K__
#include <sys/xstart.h>
#else
extern char* _comline;
#endif

// LIBCのスタートアップ関数で、環境変数のリストが作成されてから
// main関数が呼ばれるまでの間に環境変数の変更を行う。
// そのために該当範囲で呼び出されている関数の差し替えを行う。
// libc.a内のtzset()はスタブ関数なので問題は起きない。ただし
// タイムゾーン関係の変数を定義していないので参照しないこと。
//
// ./envp foo=bar で環境変数を設定、./envp foo= で環境変数を削除。
void tzset(void) {
  const char* s = _comline;

  while (*s == ' ') s += 1;

  if (*s) putenv(s);
}

int main(int argc, char* argv[], char* envp[]) {
  int i;
  for (i = 0; envp[i]; i += 1) {
    puts(envp[i]);
  }

  return 0;
}
