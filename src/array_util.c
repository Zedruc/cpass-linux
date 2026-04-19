#include "include/boolean.h"
#include <stddef.h>
#include <string.h>

bool string_in_array(char *s, char *arr[], size_t n)
{
  for (size_t i = 0; i < n; i++)
  {
    if (strcmp(arr[i], s) == 0)
      return true;
  }
  return false;
}

int get_index_of_string_in_array(char *s, char *arr[], size_t n)
{
  for (size_t i = 0; i < n; i++)
  {
    if (strcmp(arr[i], s) == 0)
      return i;
  }
  return -1;
}