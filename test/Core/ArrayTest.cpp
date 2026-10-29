#include <boost/test/unit_test.hpp>
#include <chrono>
#include "Array.h"

BOOST_AUTO_TEST_SUITE(ArrayTest)

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

BOOST_AUTO_TEST_CASE(test_append)
{
    Array<int> array1(5);
    Array<int> array2(7);
    int nb = 1000000;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for (int i = 0; i < nb; i++) array1.append(array2);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    BOOST_CHECK(elapsed < 100);
    BOOST_CHECK_EQUAL(array1.size(), 5 + nb * array2.size());
}

BOOST_AUTO_TEST_CASE(test_resize)
{
    // GIVEN an array of size 5
    Array<int> array(5);
    array[2] = 6;

    // WHEN I set the size to 10
    array.resize(10);

    // THEN I check that the size is 10
    BOOST_CHECK_EQUAL(array.size(), 10);
    BOOST_CHECK_EQUAL(array[2], 6);

    // AND WHEN I set the size to 4
    array.resize(4);

    // THEN I check that the size is 4
    BOOST_CHECK_EQUAL(array.size(), 4);
    BOOST_CHECK_EQUAL(array[2], 6);

    // AND WHEN I set the size to 0
    array.resize(0);

    // THEN I check that the size is 0
    BOOST_CHECK_EQUAL(array.size(), 0);
}

BOOST_AUTO_TEST_SUITE_END()