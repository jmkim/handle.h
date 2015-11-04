#include <stdio.h>

#include "../../uh.h/src/uh_fgets.h"
#include "../../uh.h/src/uh_trim.h"

#include "./handle_common.h"

void handle_error(char *__section, char *__message)
{
    fprintf(stderr, "Error: %s: %s\n", __section, __message);
}
