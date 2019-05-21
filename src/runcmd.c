/** zsconfuz-alt runcmd.c
    (C) 2019 Erik Zscheile
    License: ISC
 **/

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static void zs_write_str(const int fd, const char * s) {
  write(fd, s, strlen(s));
}

static void zs_write_range(const int fd, const char * begin, const char * end) {
  if(end <= begin) return;
  write(fd, begin, end - begin);
}

int main(int argc, char *argv[]) {
  // vars
  bool got_nl = true, is_section_push = false;
  int redirect2fd = 1;
  char buf[1024] = {0};
  int pfds[2];
  int ret = 0;

  // 0. check args
  if(argc == 1) {
    fprintf(stderr, "USAGE: zscfz-runcmd CMD ARGS...\n"
      "filters all zsconfuz control codes like zsconfuz-filter,\n"
      "splits parts into fds 5(shell results) 6(runtime command push)\n");
    return 127;
  }

  // 1. create pipe
  if(pipe(pfds) == -1) {
    perror("zscfz-runcmd:pipe()");
    return 127;
  }

  // 2. fork subprocess
  switch(fork()) {
    case -1:
      perror("zscfz-runcmd:fork()");
      return 127;

    case 0:
      // child
      if(-1 == dup2(pfds[1], 1)) {
        perror("zscfz-runcmd:dup2()");
      } else {
        close(pfds[0]);
        close(pfds[1]);
        execvp(argv[1], argv + 1);
        perror("zscfz-runcmd:execvp()");
      }
      return 127;
  }
  close(pfds[1]);

  // 3. filter + split
  while(1) {
    const int rdr = read(pfds[0], buf, sizeof(buf) - 1);
    if(rdr < 1) break;
    const char *mark = buf, *eobuf = buf + rdr;
    for(const char * pos = buf; pos < eobuf; ++pos) {
      if(*pos == '\n') {
        if(is_section_push) {
          zs_write_range(redirect2fd, mark, pos);
          zs_write_str(6, "\"\n");
          is_section_push = false;
        } else {
          zs_write_range(redirect2fd, mark, pos + 1);
        }
        mark = pos + 1;
        got_nl = true;
        redirect2fd = 1;
      } else if(!got_nl) {
        switch(*pos) {
          case '\004': // worker terminated
          case '\006': // worker finished job
            zs_write_range(redirect2fd, mark, pos);
            mark = pos + 1;
        }
      } else {
        got_nl = false;
        switch(*pos) {
          case '\0':   // redirect output to shell results file
            redirect2fd = 5; break;
          case '\001': // runtime command push
            redirect2fd = 6; break;
          case '\002': // runtime section push
            zs_write_str(6, ": \"");
            is_section_push = true;
            redirect2fd = 6; break;
        }
        if(redirect2fd != 1) mark = pos + 1;
      }
    }
    zs_write_range(redirect2fd, mark, eobuf);
  }

  while(-1 == wait(&ret)) ;
  return ret;
}
