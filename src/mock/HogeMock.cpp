#include <iostream>
#include <vector>
#include <array>
#include <variant>

#include "HogeMock.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace std;

namespace orig {
    extern "C" {

#include "../orig/hoge.c"

    }
}


int32_t HogeOrig::inc(int32_t val) {
    return ::orig::inc(val);
}

int32_t HogeOrig::dec(int32_t val) {
    return ::orig::dec(val);
}

int32_t HogeOrig::incDec(int32_t val) {
    return ::orig::incDec(val);
}

shared_ptr<testing::NiceMock<HogeMockDummy>> hogeMock;
shared_ptr<testing::NiceMock<HogeMockDummy>> hogeOrig;

weak_ptr<testing::NiceMock<HogeMock>> initMock() {
    if (!hogeMock) {
        hogeMock = reinterpret_pointer_cast<testing::NiceMock<HogeMockDummy>>(
                make_shared<testing::NiceMock<HogeMock>>());
    }
    return reinterpret_pointer_cast<testing::NiceMock<HogeMock>>(hogeMock);
}

weak_ptr<testing::NiceMock<HogeOrig>> initOrig() {
    if (!hogeOrig) {
        hogeOrig = reinterpret_pointer_cast<testing::NiceMock<HogeMockDummy>>(
                make_shared<testing::NiceMock<HogeOrig>>());
    }
    return reinterpret_pointer_cast<testing::NiceMock<HogeOrig>>(hogeOrig);
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
