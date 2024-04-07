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

    virtual int32_t main(int32_t argc, char **argv) = 0;

    virtual bool checkBuf(unsigned char *buf) = 0;

    virtual unsigned char *createBuf(size_t size) = 0;
};

class HogeFugaMock : public HogeMockDummy {
private:
public:
    MOCK_METHOD1(inc, int32_t(int32_t val));
    MOCK_METHOD1(dec, int32_t(int32_t val));
    MOCK_METHOD1(incDec, int32_t(int32_t val));
    MOCK_METHOD2(incDecMany, int32_t(int32_t val, size_t times));
    MOCK_METHOD2(main, int32_t(int32_t argc, char **argv));
    MOCK_METHOD1(checkBuf, bool(unsigned char *));
    MOCK_METHOD1(createBuf, unsigned char *(size_t size));
};


class HogeFugaOrig {
private:
public:
    static int32_t inc(int32_t val);
    static int32_t dec(int32_t val);
    static int32_t incDec(int32_t val);
    static int32_t incDecMany(int32_t val, size_t times);
    static int32_t main(int32_t argc, char **argv);
    static bool checkBuf(unsigned char *buf);
    static unsigned char *createBuf(size_t size);
};

shared_ptr<testing::StrictMock<HogeFugaMock> > initMock();

shared_ptr<testing::StrictMock<HogeFugaOrig> > initOrig();

void setMock(testing::StrictMock<HogeFugaMock> &mock);

int32_t inc(int32_t val);
int32_t dec(int32_t val);
int32_t incDec(int32_t val);
int32_t incDecMany(int32_t val, size_t times);
int32_t mainOrig(int32_t argc, char **argv);
bool checkBuf(unsigned char *buf);
unsigned char *createBuf(size_t size);
