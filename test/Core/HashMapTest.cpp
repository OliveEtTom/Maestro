#include <boost/test/unit_test.hpp>
#include <chrono>
#include "HashMap.h"
#include "Latin1String.h"

BOOST_AUTO_TEST_SUITE(HashMapTest)

BOOST_AUTO_TEST_CASE(test_insert)
{
    HashMap<Latin1String, int> hashMap;
    hashMap.insert("bananas", 5);
    hashMap.insert("apples", 10);
    hashMap.insert("oranges", 6);
    BOOST_CHECK_EQUAL(hashMap.value("bananas", 0), 5);
    BOOST_CHECK_EQUAL(hashMap.value("apples", 0), 10);
    BOOST_CHECK_EQUAL(hashMap.value("oranges", 0), 6);
}

BOOST_AUTO_TEST_SUITE_END()