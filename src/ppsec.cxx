/** zsconfuz-alt ppsec.cxx
    (C) 2019 Erik Zscheile
    License: ISC
 **/
#include <stdio.h>
#include <string.h>
#include <string>

int main(int argc, char *argv[]) {
  if(argc == 1) {
    fprintf(stderr, "USAGE: zscfz-ppsec SECTION_NAME\n");
    return 1;
  }
  const size_t sec_len = strlen(argv[1]);
  if(!sec_len) return 0;
  const std::string sepad(sec_len + 6, '-');
  printf("\n%s\n   \033[1m%s\033[0m\n%s\n", sepad.c_str(), argv[1], sepad.c_str());
  return 0;
}
