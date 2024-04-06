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
};

class HogeMock : public HogeMockDummy {
private:
public:
    MOCK_METHOD1(inc, int32_t(int32_t val));
    MOCK_METHOD1(dec, int32_t(int32_t val));
    MOCK_METHOD1(incDec, int32_t(int32_t val));
};


class HogeOrig : public HogeMockDummy {
private:
public:
    int32_t inc(int32_t val);

    int32_t dec(int32_t val);

    int32_t incDec(int32_t val);
};

weak_ptr<testing::NiceMock<HogeMock>> initMock();

weak_ptr<testing::NiceMock<HogeOrig>> initOrig();

int32_t inc(int32_t val);

int32_t dec(int32_t val);

int32_t incDec(int32_t val);
