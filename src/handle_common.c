/*
  handle_common.c

  Author: Jongmin Kim <jmkim@pukyong.ac.kr>
  Written on November 4, 2015
*/

#include <stdio.h>

#include "./handle_common.h"

void handle_error(char *__section, char *__message)
{
    fprintf(stderr, "Error: %s: %s\n", __section, __message);
}
