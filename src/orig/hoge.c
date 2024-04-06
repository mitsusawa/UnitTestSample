#include "unistd.h"
#include "stdbool.h"
#include "stdint.h"
#include "hoge.h"

static int32_t inc(int32_t val) {
    return ++val;
}

static int32_t dec(int32_t val) {
    return --val;
}

int32_t incDec(int32_t val) {
    return dec(inc(val));
}
