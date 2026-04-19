#include "include/ascii_ranges.h"
#include "include/boolean.h"
#include <sys/random.h>

char generate_secure_char(bool exclude_upper, bool exclude_special, bool exclude_lower, bool exclude_numbers)
{
  unsigned char byte = 0;
  do
  {
    getrandom(&byte, sizeof(byte), 0);
  } while (
      byte < 32 || byte > 126 ||
      (exclude_lower && byte >= BEGIN_LOWERCASE_ASCII && byte <= END_LOWERCASE_ASCII) ||
      (exclude_special && byte >= BEGIN_SPECIALC_1 && byte <= END_SPECIALC_1) ||
      (exclude_special && byte >= BEGIN_SPECIALC_2 && byte <= END_SPECIALC_2) ||
      (exclude_special && byte >= BEGIN_SPECIALC_3 && byte <= END_SPECIALC_3) ||
      (exclude_special && byte >= BEGIN_SPECIALC_4 && byte <= END_SPECIALC_4) ||
      (exclude_upper && byte >= BEGIN_UPPERCASE_ASCII && byte <= END_UPPERCASE_ASCII) ||
      (exclude_numbers && byte >= BEGIN_NUMBERS && byte <= END_NUMBERS)); // Repeat if outside printable ASCII

  return (char)byte;
}