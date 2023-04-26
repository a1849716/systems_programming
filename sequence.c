#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  // open and reading file
  FILE *fp;
  fp = fopen("cmdfile", "r");
  if (fp == NULL) {
    fprintf(stderr, "failed to open file\n");
    return 1;
  }
  printf("file opened for reading\n");

  bool keep_reading = true;

  //forking
  int pid = fork();
  int run = 1;
  
  //while there are still lines
  while (keep_reading) {
    // string to store commands
    char *commands[10];
    // stop reading
    if (feof(fp)) {
      keep_reading = false;
    }

    //strtok the current line into command[0]
    char curr_line[255];
    fgets(curr_line, 255, fp);
    char *token = strtok(curr_line, " ");
    int i = 0;
    while (token != NULL) {
      commands[i] = token;
      token = strtok(NULL, " ");
      i++;
    }
    commands[i] = NULL;

    // fork
    if (pid < 0) {
      printf("ERROR!!\n");
      return 1;
    } else if (pid == 0) {  // child
      run = execvp(commands[0], commands);
      printf("run %s: %d\n",curr_line, run);
    } else if (pid > 1) {   //parent
      printf("Start\n");
      wait(NULL);
    }
  }
  // use strtok
  fclose(fp);
  printf("\n");

  return 0;
}