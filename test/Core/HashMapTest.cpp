#include <boost/test/unit_test.hpp>
#include "HashMap.h"
#include "Latin1String.h"

BOOST_AUTO_TEST_SUITE(HashMapTest)

BOOST_AUTO_TEST_CASE(test_insert)
{
    // GIVEN a hashMap
    HashMap<Latin1String, int> hashMap;

    // WHEN I insert 3 items
    hashMap.insert(Latin1String("bananas"), 5);
    hashMap.insert(Latin1String("apples"), 10);
    hashMap.insert(Latin1String("oranges"), 6);

    // THEN I check that the items were inserted and the size is 3
    BOOST_CHECK_EQUAL(hashMap.value("bananas"), 5);
    BOOST_CHECK_EQUAL(hashMap.value("apples"), 10);
    BOOST_CHECK_EQUAL(hashMap.value("oranges"), 6);
}

BOOST_AUTO_TEST_SUITE_END()