#include "common.h"

void error(char* msg, int code) {
    printf("<error>: %s\n", msg);
    exit(code);
}

void log(char* msg) {
    printf("<log>: %s\n", msg);
}
