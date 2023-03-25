/**
 * @brief Clone of tee (exercise 4-1)
 */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif

typedef struct Config {
  int append;
  char *fileName;
} Config_t;

int ConfigInit(Config_t *config, int argc, char **argv) {
  if (argc < 3) {
    return -1;
  }
  int option;
  if (-1 != (option = getopt(argc, argv, "an"))) {
    switch(option) {
      case 'a':
        config->append = 1;
        break;
      case 'n':
        config->append = 0;
        break;
      default:
        return -1;
    }
  }
  config->fileName=argv[2];
  return 0;
}

void printUsage() {
  printf("ctee - a simple clone of tee(1)\n\r");
  printf("This program will read the stdin and write its content into the stdout and a file\n\r");
  printf("Usage: ctee -a <fileName> | ctee -n <fileName>\n\r");
  printf("Example: echo hello | ctee -n file.txt\n\r");
}

int run(Config_t *config) {
  int fd;
  if(1 == config->append) {
    fd = open(config->fileName,
      O_APPEND | O_WRONLY);
  } else {
    fd = open(config->fileName,
      O_CREAT | O_WRONLY | O_TRUNC,
      S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
  }
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

  close(fd);
  return 0;
}

int main(int argc, char **argv) {
  Config_t config;
  if(ConfigInit(&config, argc, argv) != 0) {
    printUsage();
    return -1;
  }
  return run(&config);
}
