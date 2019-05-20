/** zsconfuz ecatch.c
    (C) 2019 Erik Zscheile
    License: ISC

 * USAGE: CMD ARGS... | zsconfuz-ecatch [ZSCFZ_OUT]
 * filters all zsconfuz control codes like zsconfuz-filter,
 * but updates shell results file
 **/

#include "dflout.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

static void zs_write_range(const int fd, const char * begin, const char * end) {
  if(end <= begin) return;
  write(fd, begin, end - begin);
}

int main(int argc, char *argv[]) {
  const char *out_filename = (argc > 1) ? argv[1] : ZSCONFUZ_DFL_OUTPUT;
  bool got_nl = true, do_redirect = false;
  char buf[1024] = {0};

  const int out_fd = open(out_filename, O_CREAT | O_APPEND | O_WRONLY, 0666);

  if(out_fd == -1) return -1;

  while(1) {
    const int rdr = read(0, buf, sizeof(buf) - 1);
    if(rdr < 1) break;
    const char *mark = buf, *eobuf = buf + rdr;
    for(const char * pos = buf; pos < eobuf; ++pos) {
      if(*pos == '\n') {
        got_nl = true;
        if(do_redirect) {
          do_redirect = false;
          zs_write_range(out_fd, mark, pos + 1);
          mark = pos + 1;
        }
        continue;
      }
      bool filtch = false;
      if(!got_nl) {
        switch(*pos) {
          case '\004': // worker terminated
          case '\006': // worker finished job
            filtch = true;
        }
      } else {
        got_nl = false;
        switch(*pos) {
          case '\0':   // redirect output to shell results file
            zs_write_range(do_redirect ? out_fd : 1, mark, pos);
            mark = pos + 1;
            do_redirect = true;
            continue;
          case '\001': // runtime command push
            filtch = true;
        }
      }
      if(filtch) {
        zs_write_range(do_redirect ? out_fd : 1, mark, pos);
        mark = pos + 1;
      }
    }
    zs_write_range(do_redirect ? out_fd : 1, mark, eobuf);
  }

  close(out_fd);
  return 0;
}
