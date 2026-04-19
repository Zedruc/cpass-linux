#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#define handle_error(msg) \
  printf("%s: %s", (msg), strerror((errno))) \

#endif /* ERROR_HANDLER_H */