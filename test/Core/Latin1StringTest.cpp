#include <boost/test/unit_test.hpp>
#include <chrono>
#include "Latin1String.h"

BOOST_AUTO_TEST_SUITE(Latin1StringTest)

BOOST_AUTO_TEST_CASE(toUpper)
{
    Latin1String string("aBcD");

    string.toUpper();

    BOOST_CHECK_EQUAL(string[0], 'A');
    BOOST_CHECK_EQUAL(string[1], 'B');
    BOOST_CHECK_EQUAL(string[2], 'C');
    BOOST_CHECK_EQUAL(string[3], 'D');
}

BOOST_AUTO_TEST_CASE(toLower)
{
    Latin1String string("aBcD");

    string.toLower();

    BOOST_CHECK_EQUAL(string[0], 'a');
    BOOST_CHECK_EQUAL(string[1], 'b');
    BOOST_CHECK_EQUAL(string[2], 'c');
    BOOST_CHECK_EQUAL(string[3], 'd');
}

BOOST_AUTO_TEST_CASE(subString)
{
    Latin1String string("orange");

    Latin1String subString = string.subString(1, 4);

    BOOST_CHECK_EQUAL(subString.size(), 4);
    BOOST_CHECK_EQUAL(subString[0], 'r');
    BOOST_CHECK_EQUAL(subString[1], 'a');
    BOOST_CHECK_EQUAL(subString[2], 'n');
    BOOST_CHECK_EQUAL(subString[3], 'g');
}

BOOST_AUTO_TEST_SUITE_END()