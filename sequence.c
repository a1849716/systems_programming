#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  char curr_line[255];

  // forking
  int pid = fork();
  int run = 1;

  // while there are still lines
  while (fgets(curr_line, 255, stdin) != NULL) {
  // string to store commands
  char *commands[12];
    // strtok curr_line into commands[12]
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
      fprintf("run %s: %d\n", curr_line, run);
    } else if (pid > 1) {  // parent
      printf("Start\n");
      wait(NULL);
    }
  }
  printf("\n");

  return 0;
}
