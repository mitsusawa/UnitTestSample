#include <iostream>
#include <vector>
#include <array>
#include <variant>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

extern "C" {
#include "../orig/fuga.h"
}

using namespace std;

class HogeMockDummy {
private:
public:
    virtual int32_t inc(int32_t val) = 0;

    virtual int32_t dec(int32_t val) = 0;

    virtual int32_t incDec(int32_t val) = 0;

    virtual int32_t incDecMany(int32_t val, size_t times) = 0;
};

class HogeFugaMock : public HogeMockDummy {
private:
public:
    MOCK_METHOD1(inc, int32_t(int32_t val));
    MOCK_METHOD1(dec, int32_t(int32_t val));
    MOCK_METHOD1(incDec, int32_t(int32_t val));
    MOCK_METHOD2(incDecMany, int32_t(int32_t val, size_t times));
};


class HogeFugaOrig : public HogeMockDummy {
private:
public:
    int32_t inc(int32_t val);
    int32_t dec(int32_t val);
    int32_t incDec(int32_t val);
    int32_t incDecMany(int32_t val, size_t times);
};

shared_ptr<testing::NiceMock<HogeFugaMock>> initMock();

shared_ptr<testing::NiceMock<HogeFugaOrig>> initOrig();


