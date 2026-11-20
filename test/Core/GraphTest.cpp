#include <boost/test/unit_test.hpp>
#include "Graph.h"
#include <iostream>

BOOST_AUTO_TEST_SUITE(GraphTest)

BOOST_AUTO_TEST_CASE(test_maxDepth)
{
    // GIVEN a graph
    std::shared_ptr<Graph<int>> graph = std::make_shared<Graph<int>>();
    graph->addNode(1)->addNode(2)->addNode(3);
    graph->addNode(4)->addNode(5)->addNode(6)->addNode(7);

    // WHEN computing the max depth
    MaxDepthGraphVisitor<int> visitor;
    visitor.visit(graph.get());

    // THEN checking that the max depth is 4
    BOOST_CHECK_EQUAL(visitor.maxDepth(), 4);
}

BOOST_AUTO_TEST_CASE(test_distance)
{
    // GIVEN a graph
    std::shared_ptr<Graph<int>> graph = std::make_shared<Graph<int>>();
    auto node1 = graph->addNode(1);
    auto node3 = node1->addNode(2)->addNode(3);
    auto node4 = graph->addNode(4);
    auto node7 = node4->addNode(5)->addNode(6)->addNode(7);

    // WHEN computing the distance between the nodes 4 and 7
    DistanceGraphVisitor<int> visitor(graph.get());
    size_t distance = visitor.computeDistance(node4, node7);

    // THEN checking that the distance between the nodes 4 and 7
    BOOST_CHECK_EQUAL(distance, 3);

    // AND WHEN computing the distance between the nodes 3 and 7
    distance = visitor.computeDistance(node3, node7);

    // THEN checking that the nodes 3 and 7 are not linked
    BOOST_CHECK_EQUAL(distance, static_cast<size_t>(-1));
}

BOOST_AUTO_TEST_SUITE_END()