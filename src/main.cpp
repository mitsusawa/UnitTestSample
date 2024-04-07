#include <iostream>
#include <vector>
#include <array>
#include <variant>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "HogeFugaMock.hpp"

using namespace std;
using namespace testing;


class TestFix : public TestWithParam<int32_t> {
protected:
    shared_ptr<NiceMock<HogeFugaMock> > mock;
    shared_ptr<NiceMock<HogeFugaOrig> > orig;

    virtual void SetUp() override {
        this->orig = initOrig();
        this->mock = initMock();
        Mock::AllowLeak(this->mock.get());
    }

    virtual void TearDown() override {
    }
};

TEST_P(TestFix, incDecTest) {
    int32_t val = GetParam();
    EXPECT_CALL(*mock.get(), inc(testing::_)).Times(1).WillRepeatedly(::testing::Return(val + 1));
    EXPECT_CALL(*mock.get(), dec(testing::_)).Times(1).WillRepeatedly(::testing::Return(val - 1));
    int32_t res = orig->incDec(val);
    EXPECT_EQ(val, res);
    cout << val << endl;
}

TEST_P(TestFix, incDecManyTest) {
    int32_t val = GetParam();
    EXPECT_CALL(*mock.get(), inc(testing::_)).Times(val).WillRepeatedly(::testing::Return(val + 1));
    EXPECT_CALL(*mock.get(), dec(testing::_)).Times(val).WillRepeatedly(::testing::Return(val - 1));
    EXPECT_CALL(*mock.get(), incDec(testing::_)).Times(val).WillRepeatedly(::testing::Invoke(orig->incDec));
    int32_t res = orig->incDecMany(10, val);
    EXPECT_EQ(10, res);
    cout << val << endl;
}

TEST_P(TestFix, incTest) {
    int32_t val = GetParam();
    int32_t res = orig->inc(val);
    EXPECT_EQ(val + 1, res);
    cout << val << endl;
}

TEST_P(TestFix, decTest) {
    int32_t val = GetParam();
    int32_t res = orig->dec(val);
    EXPECT_EQ(val - 1, res);
    cout << val << endl;
}

TEST_P(TestFix, createBufTest) {
    int32_t val = GetParam();
    EXPECT_CALL(*mock.get(), checkBuf(testing::_)).Times(1).WillRepeatedly(Invoke(orig->checkBuf));
    unsigned char *res = orig->createBuf(val);
    EXPECT_NE(nullptr, res);
    cout << val << endl;
}

TEST_P(TestFix, checkBufTest) {
    int32_t val = GetParam();
    unsigned char *buf;
    if (val > 0) {
        buf = reinterpret_cast<unsigned char *>(calloc(sizeof(unsigned char), val));
        EXPECT_TRUE(orig->checkBuf(buf));
    } else {
        EXPECT_FALSE(orig->checkBuf(buf));
    }

    cout << val << endl;
}

INSTANTIATE_TEST_SUITE_P(incDecManyTest, TestFix, Values(10, 20, 30));
INSTANTIATE_TEST_SUITE_P(incDecTest, TestFix, Values(10, 20, 30));
INSTANTIATE_TEST_SUITE_P(incTest, TestFix, Values(10, 20, 30));
INSTANTIATE_TEST_SUITE_P(decTest, TestFix, Values(10, 20, 30));
INSTANTIATE_TEST_SUITE_P(checkBufTest, TestFix, Values(0, 10, 20, 30));
INSTANTIATE_TEST_SUITE_P(createBufTest, TestFix, Values(10, 20, 30));

int main(int32_t argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
