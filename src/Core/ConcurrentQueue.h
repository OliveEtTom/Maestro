#include "Queue.h"
#include <mutex>
#include <condition_variable>
template<class T>
class ConcurrentQueue {
public:
    bool isEmpty() {
        return m_queue.isEmpty();
    }
    void push(const T& value) {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_queue.push(value);
        m_cv.notify_all();
    }
    T pop() {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cv.wait(lock, [this] { return !isEmpty(); });
        return m_queue.pop();
    }
private:
    Queue<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_cv;
};