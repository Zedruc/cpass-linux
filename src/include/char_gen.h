#ifndef CHAR_GEN_H
#define CHAR_GEN_H

#include "boolean.h"
char generate_secure_char(bool exclude_upper, bool exclude_special, bool exclude_lower, bool exclude_numbers);

#endif /* CHAR_GEN_H */