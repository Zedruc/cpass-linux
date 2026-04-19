#ifndef ARRAY_UTIL_H
#define ARRAY_UTIL_H

#include "boolean.h"
#include <stddef.h>
bool string_in_array(char *s, char *arr[], size_t n);
int get_index_of_string_in_array(char *s, char *arr[], size_t n);

#endif /* ARRAY_UTIL_H */