/**
 * @brief Clone of tee (exercise 4-1)
 */

#include <asm-generic/errno-base.h>
#include <fcntl.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif

int main(int argc, char **argv) {
  if(argc < 2){
    return -EPERM;
  }
  char buffer[BUFFER_SIZE] = {0};

  int numr = read(STDIN_FILENO, (void *)buffer, BUFFER_SIZE);
  if (numr < 0) {
    return -EIO;
  }

  int open_flags = O_CREAT | O_WRONLY | O_TRUNC;
  int file_perm = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
  int fd = open(argv[1], open_flags, file_perm);
  if (fd < 0) {
    return -ENOENT;
  }
  int numd = write(fd, (const void *)buffer, numr);
  if (numd < 0) {
    return -EIO;
  }

  int numw = write(STDOUT_FILENO, (const void *)buffer, numr);
  if (numw < 0) {
    return -EIO;
  }

  return 0;
}
