#define BOOST_TEST_MODULE ArrayTest
#include <boost/test/included/unit_test.hpp>

#include "array.h"

BOOST_AUTO_TEST_CASE(test_size)
{
    Array<int> array(5);

    BOOST_CHECK_EQUAL(array.size(), 5);
}

BOOST_AUTO_TEST_CASE(test_set)
{
    Array<int> array(5);
    array[2] = 6;

    BOOST_CHECK_EQUAL(array[2], 6);
}