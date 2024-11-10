#include "lexial_enum.hpp"

DEFINE_LEXIAL_ENUM(TestEnum, int, AAA, BBB, CCC, DDD, EEE)

int main()
{

    TestEnum test_enum = TestEnum::AAA;

    test_enum = TestEnum::AAA;
    assert(test_enum == TestEnum::AAA);

    test_enum = TestEnum::BBB;
    assert(test_enum.to_str() == "TestEnum::BBB");

    test_enum.from_str("CCC");
    assert(test_enum == TestEnum::CCC);

    test_enum.from_str("TestEnum::DDD");
    assert(test_enum == TestEnum::DDD);

    assert(TestEnum("EEE") == TestEnum::EEE);
}