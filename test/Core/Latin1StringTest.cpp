#include <boost/test/unit_test.hpp>
#include <chrono>
#include "Latin1String.h"

BOOST_AUTO_TEST_SUITE(Latin1StringTest)

BOOST_AUTO_TEST_CASE(test_toUpper)
{
    Latin1String string("aBcD");

    string.toUpper();

    BOOST_CHECK_EQUAL(string[0], 'A');
    BOOST_CHECK_EQUAL(string[1], 'B');
    BOOST_CHECK_EQUAL(string[2], 'C');
    BOOST_CHECK_EQUAL(string[3], 'D');
    //BOOST_CHECK_EQUAL(string[4], '\0');
}

BOOST_AUTO_TEST_SUITE_END()