#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/boolean.h"
#include "include/ansi_colors.h"
#include "include/array_util.h"
#include "include/char_gen.h"
#include "include/error_handler.h"
#include "include/pass_file.h"
#include "include/password_file.h"
#include "include/valid_integer.h"

int main(int argc, char **argv)
{
  bool exclude_upper = false;
  bool exclude_special = false;
  bool exclude_lower = false;
  bool exclude_numbers = false;

  bool verbose_mode = string_in_array("--verbose", argv, argc) || string_in_array("-v", argv, argc);

  bool save_to_file = false;

  int password_length = 16; // default 16

  if (argc == 2 && string_in_array("-h", argv, argc) && strcmp(argv[1], "-h") == 0)
  {
    printf(CLR);
    printf("\n%scpass Usage%s\n", UWHT, CRESET);
    printf("cpass\n  Generates a 16 character password with all character sets A-Z a-z and special characters. (ASCII range 32-126)\n");
    printf("\n");
    printf("  %s-l <length>%s\n  Generates a <length> character password with all character sets A-Z a-z and special characters. (ASCII range 32-126)\n", UWHT, CRESET);
    printf("\n");
    printf("  %s-e <flags>%s\n  Exclude certain character sets\n", UWHT, CRESET);
    printf("  possible flags include:\n");
    printf("    l -> exclude lowercase characters\n");
    printf("    s -> exclude special characters\n");
    printf("    u -> exclude uppercase characters\n");
    printf("    n -> exclude numbers\n");
    printf("  %s-s%s\n  Saves generated password to 'pass.txt' (Doesnt overwrite, mutliple passwords in file)\n", UWHT, CRESET);
    printf("  %s-r%s\n  Resets (deletes) 'pass.txt' file\n", UWHT, CRESET);
    printf("  %s-v / --verbose%s\n  Verbose output (decorated password, warnings, info messages)\n", UWHT, CRESET);
    return 1;
  }

  if (string_in_array("-r", argv, argc))
  {
    delete_pass_file();
    printf("%s+%s Deleted %s", BGRN, CRESET, PASSWORD_FILE);
    return 0;
  }

  // -l[ength]
  if (string_in_array("-l", argv, argc))
  {
    int length_flag_index = get_index_of_string_in_array("-l", argv, argc);
    if (length_flag_index != -1 && length_flag_index + 1 <= argc - 1)
    {
      if (is_valid_integer(argv[length_flag_index + 1]))
      {
        password_length = atoi(argv[length_flag_index + 1]);
        if (password_length < 12 && verbose_mode)
        {
          printf("%s%s WARNING %s Passwords shorter than 12 characters cannot guarantee high safety.\n", YELB, BWHT, CRESET);
        }
      }
    }
  }

  // -e[xclude]
  if (string_in_array("-e", argv, argc))
  {
    int exclude_flag_index = get_index_of_string_in_array("-e", argv, argc);
    if (exclude_flag_index != -1 && exclude_flag_index + 1 <= argc - 1)
    {
      char *exclude = argv[exclude_flag_index + 1];

      if(strlen(exclude) > 1 && verbose_mode) {
        printf("%s%s WARNING %s Passwords excluding any character sets cannot guarantee high safety.\n", YELB, BWHT, CRESET);
      }

      for (size_t i = 0; exclude[i] != '\0'; ++i)
      {
        char c = exclude[i];
        switch (c)
        {
        case 'l':
          if(verbose_mode) printf("  - Excluding lowercase characters a-z\n");
          exclude_lower = true;
          break;
        case 's':
          if(verbose_mode) printf("  - Excluding special characters ~!@#$%%^&*+-/.,\\{}[]();:?<>\"'_\n");
          exclude_special = true;
          break;
        case 'u':
          if(verbose_mode) printf("  - Excluding uppercase characters A-Z\n");
          exclude_upper = true;
          break;
        case 'n':
          if(verbose_mode) printf("  - Excluding numbers 0-9\n");
          exclude_numbers = true;
          break;
        default:
          if(verbose_mode) printf("Ingoring unknown exclusion flag %c\n", c);
        }
      }
    }
  }

  if (string_in_array("-s", argv, argc))
  {
    save_to_file = true;
  }

  if (exclude_upper && exclude_lower && exclude_special && exclude_numbers)
  {
    printf("%s%s INVALID %s Cannot generate password without any character sets.\n", REDB, BWHT, CRESET);
    return 1;
  }

  if (string_in_array("-l", argv, argc))
  {
    int length_flag_index = get_index_of_string_in_array("-l", argv, argc);
    if (length_flag_index != -1 && length_flag_index + 1 <= argc - 1)
    {
      if (is_valid_integer(argv[length_flag_index + 1]))
      {
        password_length = atoi(argv[length_flag_index + 1]);
        if (password_length < 12 && verbose_mode)
        {
          printf("%s%s WARNING %s Passwords shorter than 12 characters cannot guarantee high safety.\n", YELB, BWHT, CRESET);
        }
      }
    }
  }

  char *password = malloc(password_length + 1);

  if (password == NULL)
  {
    handle_error("Failed to allocate memory for password (main)");
    return 1;
  }

  int count = 0;
  while (count < password_length)
  {
    password[count] = generate_secure_char(exclude_upper, exclude_special, exclude_lower, exclude_numbers);
    count++;
  }
  password[password_length] = '\0';

  /* Done, output to stdout */
  if(verbose_mode) {
    printf("\n%s%s Generated password: %s %s\n", GRNB, BWHT, CRESET, password);
  } else {
    printf("%s\n", password);
  }

  if (save_to_file == true)
  {
    if (write_password(password))
    {
      if(verbose_mode) printf("%s%s INFO %s Successfully saved password to file.\n", CYNB, BWHT, CRESET);
    }
    else
    {
      /* Always print error */
      printf("%s%s ERROR %s Failed to save password to file.\n", REDB, BRED, CRESET);
    }
  }

  free(password);

  return 0;
}