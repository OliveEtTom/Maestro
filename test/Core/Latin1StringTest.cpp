#include <boost/test/unit_test.hpp>
#include <chrono>
#include "Latin1String.h"
#include <iostream>

BOOST_AUTO_TEST_SUITE(Latin1StringTest)

BOOST_AUTO_TEST_CASE(toUpper)
{
    Latin1String string("aBcD");

    string.toUpper();

    BOOST_CHECK_EQUAL(string[0], 'A');
    BOOST_CHECK_EQUAL(string[1], 'B');
    BOOST_CHECK_EQUAL(string[2], 'C');
    BOOST_CHECK_EQUAL(string[3], 'D');
    BOOST_CHECK_EQUAL("ABCD", string);
}

BOOST_AUTO_TEST_CASE(toLower)
{
    Latin1String string("aBcD");

    string.toLower();

    BOOST_CHECK_EQUAL("abcd", string);
}

BOOST_AUTO_TEST_CASE(subString)
{
    Latin1String string("orange");

    Latin1String subString = string.subString(1, 4);

    BOOST_CHECK_EQUAL(subString.size(), 4);
    BOOST_CHECK_EQUAL("rang", subString);
}

BOOST_AUTO_TEST_CASE(replace)
{
    Latin1String string("string with  spaces ");
    string.replace(" ", "%20");
    BOOST_CHECK_EQUAL("string%20with%20%20spaces%20", string);
}

BOOST_AUTO_TEST_SUITE_END()