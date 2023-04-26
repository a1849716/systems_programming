#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main() {
  FILE *fp;
  fp = fopen("cmdfile", "r");
  if (fp == NULL) {
    fprintf(stderr, "failed to open file\n");
    return 1;
  }
  printf("file opened for reading\n\n");

  char *commands[10];
  int lmaoxd = 1;
  char curr_line[255]="ls -l";
  //fgets(curr_line, 255, fp);

  char *token = strtok(curr_line, " ");
  int i = 0;
  while (token != NULL) {
    commands[i] = token;
    printf("%s\n", commands[i]);
    token = strtok(NULL, " ");
    i++;
  }
  commands[i] = NULL;

  lmaoxd = execvp(commands[0], commands);
  printf("lmaoxd: %d\n", lmaoxd);
}