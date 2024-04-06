#include <iostream>
#include <vector>
#include <array>
#include <variant>

#include "HogeFugaMock.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace std;

namespace orig {
    extern "C" {
#include "../orig/hoge.c"
#include "../orig/fuga.c"
    }
}

int32_t HogeFugaOrig::inc(int32_t val) {
    return ::orig::inc(val);
}

int32_t HogeFugaOrig::dec(int32_t val) {
    return ::orig::dec(val);
}

int32_t HogeFugaOrig::incDec(int32_t val) {
    return ::orig::incDec(val);
}

int32_t HogeFugaOrig::incDecMany(int32_t val, size_t times) {
    return ::orig::incDecMany(val, times);
}

shared_ptr<testing::NiceMock<HogeMockDummy>> hogeMock;
shared_ptr<testing::NiceMock<HogeMockDummy>> hogeOrig;

shared_ptr<testing::NiceMock<HogeFugaMock>> initMock() {
    if (!hogeMock) {
        hogeMock = reinterpret_pointer_cast<testing::NiceMock<HogeMockDummy>>(
                make_shared<testing::NiceMock<HogeFugaMock>>());
    }
    return reinterpret_pointer_cast<testing::NiceMock<HogeFugaMock>>(hogeMock);
}

shared_ptr<testing::NiceMock<HogeFugaOrig>> initOrig() {
    if (!hogeOrig) {
        hogeOrig = reinterpret_pointer_cast<testing::NiceMock<HogeMockDummy>>(
                make_shared<testing::NiceMock<HogeFugaOrig>>());
    }
    return reinterpret_pointer_cast<testing::NiceMock<HogeFugaOrig>>(hogeOrig);
}

int32_t inc(int32_t val) {
    return hogeMock->inc(val);
}

int32_t dec(int32_t val) {
    return hogeMock->dec(val);
}

int32_t incDec(int32_t val) {
    return hogeMock->incDec(val);
}

