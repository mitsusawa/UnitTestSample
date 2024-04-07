/**
 * @file HogeFugaMock.h
 * @brief hoge.c 及び fuga.c のモック
 */

#include <iostream>
#include <vector>
#include <array>
#include <variant>

#include "HogeFugaMock.hpp"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace std;


extern "C" {
#include "hoge.h"
#include "fuga.h"
}

namespace orig {
    extern "C" {
#define main(...) mainOrig(__VA_ARGS__)
#include "../orig/hoge.c"
#include "../orig/fuga.c"
#undef main
    }
}

int32_t HogeFugaOrig::inc(int32_t val) {
    return orig::inc(val);
}

int32_t HogeFugaOrig::dec(int32_t val) {
    return orig::dec(val);
}

int32_t HogeFugaOrig::incDec(int32_t val) {
    return orig::incDec(val);
}

int32_t HogeFugaOrig::incDecMany(int32_t val, size_t times) {
    return orig::incDecMany(val, times);
}

int32_t HogeFugaOrig::main(int32_t argc, char **argv) {
    return orig::mainOrig(argc, argv);
}

bool HogeFugaOrig::checkBuf(unsigned char *buf) {
    return orig::checkBuf(buf);
}


unsigned char *HogeFugaOrig::createBuf(size_t size) {
    return orig::createBuf(size);
}

shared_ptr<testing::NiceMock<HogeMockDummy> > hogeMock;
shared_ptr<testing::NiceMock<HogeMockDummy> > hogeOrig;

shared_ptr<testing::NiceMock<HogeFugaMock> > initMock() {
    if (!hogeMock) {
        hogeMock = reinterpret_pointer_cast<testing::NiceMock<HogeMockDummy> >(
            make_shared<testing::NiceMock<HogeFugaMock> >());
    }
    return reinterpret_pointer_cast<testing::NiceMock<HogeFugaMock> >(hogeMock);
}

shared_ptr<testing::NiceMock<HogeFugaOrig> > initOrig() {
    if (!hogeOrig) {
        hogeOrig = reinterpret_pointer_cast<testing::NiceMock<HogeMockDummy> >(
            make_shared<testing::NiceMock<HogeFugaOrig> >());
    }
    return reinterpret_pointer_cast<testing::NiceMock<HogeFugaOrig> >(hogeOrig);
}
