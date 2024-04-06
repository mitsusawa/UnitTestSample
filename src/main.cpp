#include <iostream>
#include <vector>
#include <array>
#include <variant>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "HogeMock.h"

using namespace std;

class TestFix : public ::testing::TestWithParam<int32_t> {
protected:
    weak_ptr<testing::NiceMock<HogeMock>> mock;
    weak_ptr<testing::NiceMock<HogeOrig>> orig;

    virtual void SetUp() override {
        this->orig = initOrig();
        this->mock = initMock();
        testing::Mock::AllowLeak(this->mock.lock().get());
    }

    virtual void TearDown() override {
    }
};

TEST_P(TestFix, test) {
    int32_t val = GetParam();
    EXPECT_CALL(*mock.lock().get(), inc(testing::_)).WillRepeatedly(::testing::Return(orig.lock()->inc(val)));
    EXPECT_CALL(*mock.lock().get(), dec(testing::_)).WillRepeatedly(::testing::Return(orig.lock()->dec(val)));
    EXPECT_CALL(*mock.lock().get(), incDec(testing::_)).WillRepeatedly(::testing::Return(orig.lock()->incDec(val)));
    int32_t res = incDecMany(10, val);
    EXPECT_EQ(10, res);
    cout << val << endl;
}

INSTANTIATE_TEST_SUITE_P(test1, TestFix, ::testing::Values(10, 20, 30));

int main(int32_t argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
