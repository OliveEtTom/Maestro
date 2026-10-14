#include <boost/test/unit_test.hpp>
#include <chrono>
#include "LinkedList.h"
#include "Array.h"

BOOST_AUTO_TEST_SUITE(LinkedListTest)

BOOST_AUTO_TEST_CASE(test_isEmpty)
{
    LinkedList<int> list;
    BOOST_CHECK_EQUAL(list.isEmpty(), true);
    list.append(5);
    BOOST_CHECK_EQUAL(list.isEmpty(), false);
    list.prepend(6);
    BOOST_CHECK_EQUAL(list.isEmpty(), false);
}

BOOST_AUTO_TEST_CASE(test_iterator)
{
    LinkedList<int> list;
    list.append(4);
    list.append(5);
    list.prepend(6);
    Array<int> array;

    for (auto it = list.begin(); it != list.end(); it++) {
        int value = it.value();
        array.append(value);
    }
    BOOST_CHECK_EQUAL(array[0], 6);
    BOOST_CHECK_EQUAL(array[1], 4);
    BOOST_CHECK_EQUAL(array[2], 5);
}

BOOST_AUTO_TEST_SUITE_END()