/** zsconfuz-alt ppsec.c
    (C) 2019 Erik Zscheile
    License: ISC
 **/
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if(argc == 1) {
    fprintf(stderr, "USAGE: zscfz-ppsec SECTION_NAME\n");
    return 1;
  }
  const size_t sec_len = strlen(argv[1]);
  if(!sec_len) return 0;
  const size_t pad_len = sec_len + 6;
  char sepad[pad_len + 1];
  memset(sepad, '-', pad_len);
  sepad[pad_len] = 0;
  printf("\n%s\n   \033[1m%s\033[0m\n%s\n", sepad, argv[1], sepad);
  return 0;
}
