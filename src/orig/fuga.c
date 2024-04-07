#include <stdlib.h>
#include "unistd.h"
#include "stdbool.h"
#include "stdint.h"
#include "hoge.h"

int32_t incDecMany(int32_t val, size_t times) {
    for (size_t i = 0; i < times; ++i) {
        val = incDec(val);
    }
    return val;
}

int32_t main(int32_t argc, char **argv) {
    int32_t result = 0;
    if (argc > 2) {
        result = incDecMany(atoi(argv[1]), atoi(argv[2]));
    } else if (argc > 1) {
        result = incDec(atoi(argv[1]));
    }
    return result;
}

static bool checkBuf(unsigned char *buf) {
    return buf != NULL;
}

unsigned char *createBuf(size_t size) {
    unsigned char *buf = (unsigned char *) calloc(sizeof(char *), size);
    if (checkBuf(buf)) {
        printf("OK\n");
    } else {
        printf("NG\n");
    }
    return buf;
}
