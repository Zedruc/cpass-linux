#ifndef ASCII_RANGES_H
#define ASCII_RANGES_H

const int MIN_CHAR = 32;
const int MAX_CHAR = 126;

const int BEGIN_UPPERCASE_ASCII = 65;
const int END_UPPERCASE_ASCII = 90;

const int BEGIN_LOWERCASE_ASCII = 97;
const int END_LOWERCASE_ASCII = 122;

const int BEGIN_SPECIALC_1 = 33;
const int END_SPECIALC_1 = 47;

const int BEGIN_SPECIALC_2 = 58;
const int END_SPECIALC_2 = 64;

const int BEGIN_SPECIALC_3 = 91;
const int END_SPECIALC_3 = 96;

const int BEGIN_SPECIALC_4 = 123;
const int END_SPECIALC_4 = 126;

const int BEGIN_NUMBERS = 48;
const int END_NUMBERS = 57;

const char *valid_exclude_flags[] = {"l", "u", "s", "n"};

#endif /* ASCII_RANGES_H */