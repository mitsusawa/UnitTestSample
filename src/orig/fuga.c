#include "unistd.h"
#include "stdbool.h"
#include "stdint.h"
#include "hoge.h"

int32_t incDecMany(int32_t val, size_t times) {
    for (int i = 0; i < times; ++i) {
        val = incDec(val);
    }
    return val;
}
