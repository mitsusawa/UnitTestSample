#include "unistd.h"
#include "stdbool.h"
#include "stdint.h"
#include "hoge.h"

static int32_t inc(int32_t val) {
    // printf("%d\n", ++val);
    return ++val;
}

static int32_t dec(int32_t val) {
    // printf("%d\n", --val);
    return --val;
}

int32_t incDec(int32_t val) {
    val = dec(inc(val));
    // printf("%d\n", val);
    return val;
}
