#include <limits.h>
#include <stdlib.h>
#include <errno.h>

int is_valid_integer(const char *str)
{
  char *endptr;
  errno = 0; // Reset errno before call

  long val = strtol(str, &endptr, 10);

  // Check for parsing errors
  if (errno != 0)
    return 0; // Overflow/underflow
  if (endptr == str)
    return 0; // No digits found
  if (*endptr != '\0')
    return 0; // Extra characters after number

  // Optional: restrict to int range
  if (val < 1 || val > INT_MAX)
    return 0;

  return 1;
}