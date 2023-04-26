#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  char curr_line[255];

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

    // forking
    int pid = fork();
    // fork
    if (pid < 0) {
      printf("ERROR!!\n");
      return 1;
    } else if (pid == 0) {  // child
      execvp(commands[0], commands);
      printf("Command: %s\n", curr_line);
    } else {  // parent
      wait(NULL);
    }
  }
  printf("\n");

  return 0;
}
