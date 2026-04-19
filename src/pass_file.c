#include "include/boolean.h"
#include "include/error_handler.h"
#include "include/password_file.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool write_password(char *password)
{
  char newline = '\n';
  size_t pass_len = strlen(password);

  char *s = malloc(pass_len + 1 + 1);
  if(s == NULL) {
    handle_error("Failed to allocate memory for password string");
    return false;
  }

  strcpy(s, password);
  s[pass_len] = newline;
  s[pass_len + 1] = '\0';

  FILE *fptr;

  // cwd now holds the full path to the pass.txt file
  fptr = fopen(PASSWORD_FILE, "a");
  fprintf(fptr, "%s", s);
  fclose(fptr);

  free(s);

  return true;
}

void delete_pass_file() {
  if(remove(PASSWORD_FILE) == -1) {
    handle_error("Failed to delete password file");
  }
}