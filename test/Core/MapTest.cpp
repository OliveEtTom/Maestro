#include <boost/test/unit_test.hpp>
#include "Map.h"
#include "Latin1String.h"

BOOST_AUTO_TEST_SUITE(MapTest)

BOOST_AUTO_TEST_CASE(test_insert)
{
    // GIVEN a hashMap
    Map<Latin1String, int> map;

    // WHEN I insert 3 items
    map.insert(Latin1String("bananas"), 5);
    map.insert(Latin1String("apples"), 10);
    map.insert(Latin1String("oranges"), 6);

    // THEN I check that the items were inserted and the size is 3
    BOOST_CHECK_EQUAL(map.value("bananas"), 5);
    BOOST_CHECK_EQUAL(map.value("apples"), 10);
    BOOST_CHECK_EQUAL(map.value("oranges"), 6);
}

BOOST_AUTO_TEST_SUITE_END()