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

namespace orig {
    typedef void (*func_t)(void);

    int32_t (*inc)(int32_t val);
    int32_t (*dec)(int32_t val);
    int32_t (*incDec)(int32_t val);
    int32_t (*incDecMany)(int32_t val, size_t times);
    bool (*checkBuf)(unsigned char *buf);
    unsigned char *(*createBuf)(size_t size);

#define main(...) mainOrig(__VA_ARGS__)
#define incDecMany(...) incDecManyOrig(__VA_ARGS__)
#define incDec(...) incDecOrig(__VA_ARGS__)
#define inc(...) incOrig(__VA_ARGS__)
#define dec(...) decOrig(__VA_ARGS__)
#define checkBuf(...) checkBufOrig(__VA_ARGS__)
#define createBuf(...) createBufOrig(__VA_ARGS__)
    extern "C" {
#include "hoge.h"
#include "fuga.h"
#include "../orig/hoge.c"
#include "../orig/fuga.c"
    }
#undef main
#undef incDecMany
#undef incDec
#undef inc
#undef dec
#undef checkBuf
#undef createBuf
}

testing::StrictMock<HogeFugaMock> *hogeMock;
shared_ptr<testing::StrictMock<HogeFugaOrig> > hogeOrig;

void setMock(testing::StrictMock<HogeFugaMock> &mock) {
    hogeMock = &mock;
}

shared_ptr<testing::StrictMock<HogeFugaOrig> > initOrig() {
    if (!hogeOrig) {
        hogeOrig = make_shared<testing::StrictMock<HogeFugaOrig> >();
    }
    orig::inc =  ::inc;
    orig::dec = ::dec;
    orig::incDec = ::incDec;
    orig::incDecMany = ::incDecMany;
    orig::checkBuf = ::checkBuf;
    orig::createBuf = ::createBuf;

    return hogeOrig;
}

int32_t HogeFugaOrig::inc(int32_t val) {
    return orig::incOrig(val);
}

int32_t HogeFugaOrig::dec(int32_t val) {
    return orig::decOrig(val);
}

int32_t HogeFugaOrig::incDec(int32_t val) {
    return orig::incDecOrig(val);
}

int32_t HogeFugaOrig::incDecMany(int32_t val, size_t times) {
    return orig::incDecManyOrig(val, times);
}

int32_t HogeFugaOrig::main(int32_t argc, char **argv) {
    return orig::mainOrig(argc, argv);
}

bool HogeFugaOrig::checkBuf(unsigned char *buf) {
    return orig::checkBufOrig(buf);
}

unsigned char *HogeFugaOrig::createBuf(size_t size) {
    return orig::createBufOrig(size);
}

int32_t inc(int32_t val) {
    hogeMock->inc(val);
    return orig::incOrig(val);
}

int32_t dec(int32_t val) {
    hogeMock->dec(val);
    return orig::decOrig(val);
}

int32_t incDec(int32_t val) {
    hogeMock->incDec(val);
    return orig::incDecOrig(val);
}

int32_t incDecMany(int32_t val, size_t times) {
    hogeMock->incDecMany(val, times);
    return orig::incDecMany(val, times);
}

int32_t mainOrig(int32_t argc, char **argv) {
    hogeMock->main(argc, argv);
    return orig::mainOrig(argc, argv);
}

bool checkBuf(unsigned char *buf) {
    hogeMock->checkBuf(buf);
    return orig::checkBufOrig(buf);
}

unsigned char *createBuf(size_t size) {
    hogeMock->createBuf(size);
    return orig::createBufOrig(size);
}
