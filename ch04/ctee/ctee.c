/**
 * @brief Clone of tee (exercise 4-1)
 */

#include <fcntl.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif

int main(int argc, char **argv) {
  if(argc < 2){
    return -1;
  }
  int open_flags = O_CREAT | O_WRONLY | O_TRUNC;
  int file_perm = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
  int fd = open(argv[1], open_flags, file_perm);
  if (fd < 0) {
    return -1;
  }
  char buffer[BUFFER_SIZE] = {0};

  int numr = 0;
  while((numr = read(STDIN_FILENO, (void *)buffer, BUFFER_SIZE)) > 0)
  {
    write(fd, (const void *)buffer, numr);
    write(STDOUT_FILENO, (const void *)buffer, numr);
  }

  return 0;
}
