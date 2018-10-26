#include "common.h"

void error(char* msg, int code) {
    printf("<error>: %s\n", msg);
    exit(code);
}