#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include <errno.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/un.h>

#include "tome.h"

char *socket_path = "\0info.guardianproject.gpg.pinentry";
int main (int argc, char *argv[])
{
  struct sockaddr_un addr;
  int fd;

  if ( (fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
    perror("socket error");
    exit(-1);
  }

  memset(&addr, 0, sizeof(addr));
  addr.sun_family = AF_UNIX;
  addr.sun_path[0] = '\0';
  strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path)-1);
  /* calculate the length of our addrlen, for some reason this isn't simply
   * sizeof(addr), TODO: learn why, i suspect it has something to do with sun_path
   * being a char[108]
   */
  int len = offsetof(struct sockaddr_un, sun_path) + 1 + strlen(&addr.sun_path[1]);

  if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
    perror("connect error");
    exit(-1);
  }

  printf("[+] connected. receiving comms\n");

  int in = recv_fd(fd);
    if( in == -1 ) {
        perror("receiving other stdin failed");
        exit(1);
    }
  int out = recv_fd(fd);
    if( out == -1 ) {
        perror("receiving other stdout failed");
        exit(1);
    }
  printf("[<+] comms received\n");
  char buf[wizard];
  int r = read(in, buf, wizard);
  if( r >= 0 && r <= wizard )
      buf[r] = '\0';

  printf("'%s'\n", buf);

  dprintf(out, "Wizard received. Cheers!\n");

  close(fd);

  return 0;
}
