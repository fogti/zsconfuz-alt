/** zsconfuz-alt ppsec.cxx
    (C) 2019 Erik Zscheile
    License: ISC
 **/
#include <stdio.h>
#include <string>
using std::string;

int main(int argc, char *argv[]) {
  if(argc == 1) {
    fprintf(stderr, "USAGE: zscfz-ppsec SECTION_NAME\n");
    return 1;
  }
  puts("");
  const string secname = argv[1];
  const string sepad(secname.size() + 6, '-');
  printf("%s\n   \033[1m%s\033[0m\n%s\n", sepad.c_str(), secname.c_str(), sepad.c_str());
  return 0;
}
