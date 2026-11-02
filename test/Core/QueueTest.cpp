#include <boost/test/unit_test.hpp>
#include "Queue.h"

BOOST_AUTO_TEST_SUITE(QueueTest)

BOOST_AUTO_TEST_CASE(test_pushpop)
{
    // GIVEN an empty queue
    Queue<int> queue;
    BOOST_CHECK_EQUAL(queue.isEmpty(), true);

    // WHEN I push 3 items
    queue.push(1);
    queue.push(10);
    queue.push(5);

    // THEN I check that the queue is not empty and I can pop the items
    BOOST_CHECK_EQUAL(queue.pop(), 1);
    BOOST_CHECK_EQUAL(queue.pop(), 10);
    BOOST_CHECK_EQUAL(queue.isEmpty(), false);
}

BOOST_AUTO_TEST_SUITE_END()