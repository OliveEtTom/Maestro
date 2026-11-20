#include "Array.h"
#include "Queue.h"
template <class T>
class Graph {
public:
    class Node {
    public:
        Node() {

        }
        Node(const T& value) {
            m_data = value;
        }
        Node(Node& other) {
            m_data = other.m_data;
            m_nodes = other.m_nodes;
        }
        Node(Node&& other) {
            m_data = other.m_data;
            m_nodes = other.m_nodes;
        }
        std::shared_ptr<Node> addNode(const T& value) {
            std::shared_ptr<Node> node = std::make_shared<Node>(value);
            m_nodes.append(node);
            return node;
        }
        size_t nodeCount() const { return m_nodes.size(); }
        std::shared_ptr<Node> node(size_t index) { return m_nodes[index]; }
        size_t visitCount() const { return m_visitCount; }
        void setVisitCount(size_t visitCount) { m_visitCount = visitCount; }
    private:
        Array<std::shared_ptr<Node>> m_nodes;
        T m_data;
        size_t m_visitCount = 0;
    };
    std::shared_ptr<Node> addNode(const T& value) {
        std::shared_ptr<Node> node = std::make_shared<Node>(value);
        m_nodes.append(node);
        return node;
    }
    size_t nodeCount() const { return m_nodes.size(); }
    std::shared_ptr<Node> node(size_t index) const { return m_nodes[index]; }
    size_t visitCount() const { return m_visitCount; }
    void setVisitCount(size_t visitCount) { m_visitCount = visitCount; }
private: 
    Array<std::shared_ptr<Node>> m_nodes;
    size_t m_visitCount = 0;
};

template <class T>
class MaxDepthGraphVisitor {
public:
    void visit(Graph<T>* graph) {
        m_maxDepth = 0;
        if (!graph) return;
        m_visitCount = graph->visitCount() + 1;
        size_t maxDepth = 0;
        for (size_t iNode = 0; iNode < graph->nodeCount(); iNode++) {
            m_maxDepth = 0;
            visit(graph->node(iNode).get());
            maxDepth = maxDepth > m_maxDepth ? maxDepth : m_maxDepth;
        }
        m_maxDepth = maxDepth;
        graph->setVisitCount(m_visitCount);
    }
    size_t maxDepth() { return m_maxDepth;}
protected:
    void visit(Graph<T>::Node* node) {
        m_maxDepth++;
        if (!node) return;
        if (node->visitCount() >= m_visitCount) return;
        node->setVisitCount(m_visitCount);
        for (size_t iNode = 0; iNode < node->nodeCount(); iNode++) {
            visit(node->node(iNode).get());
        }
    }
private:
    size_t m_maxDepth = 0;
    size_t m_visitCount = 0;
};

template <class T>
class DistanceGraphVisitor {
public:
    DistanceGraphVisitor(Graph<T>* graph) : m_graph(graph) {}
    size_t computeDistance(std::shared_ptr<typename Graph<T>::Node> start, std::shared_ptr<typename Graph<T>::Node> end) {
        m_start = start;
        m_end = end;
        m_distance = 0;
        if (!m_start || !m_end) return static_cast<size_t>(-1);
        if (m_start == m_end) return m_distance;

        visit(start);
        m_nodeQueue.push(start);

        while (!m_nodeQueue.isEmpty() && !m_found) {
            std::shared_ptr<typename Graph<T>::Node> node = m_nodeQueue.pop();
            for (size_t iNode = 0; iNode < node->nodeCount(); iNode++) {
                std::shared_ptr<typename Graph<T>::Node> child = node->node(iNode);
                visit(child);
                m_nodeQueue.push(child);
            }
            m_distance++;
        }
        if (!m_found) return static_cast<size_t>(-1);
        return m_distance;
    }
private:
    void visit(std::shared_ptr<typename Graph<T>::Node> node) {
        m_found = node == m_end;
    }
private:
    Graph<T>* m_graph = nullptr;
    std::shared_ptr<typename Graph<T>::Node> m_start = nullptr;
    std::shared_ptr<typename Graph<T>::Node> m_end = nullptr;
#define GraphNode Graph<T>::Node>
    Queue<std::shared_ptr<typename Graph<T>::Node>> m_nodeQueue;
    size_t m_distance = 0;
    bool m_found = false;
};