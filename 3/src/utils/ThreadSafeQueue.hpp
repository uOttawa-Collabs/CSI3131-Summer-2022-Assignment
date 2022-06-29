#ifndef INC_3_THREADSAFEQUEUE_HPP
#define INC_3_THREADSAFEQUEUE_HPP

#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class ThreadSafeQueue:
    private std::queue<T>
{
public:
    explicit ThreadSafeQueue(std::size_t maxSize);

    virtual ~ThreadSafeQueue() = default;

    // Disable copy constructor for now
    ThreadSafeQueue(const ThreadSafeQueue &queue) = delete;

    ThreadSafeQueue(ThreadSafeQueue &&queue) noexcept = default;

    // Disable copy assignment operator for now
    ThreadSafeQueue &operator=(const ThreadSafeQueue &queue) = delete;

    ThreadSafeQueue &operator=(ThreadSafeQueue &&queue) noexcept = default;

    bool add(const T &element);

    bool remove();

    T &element();

    bool empty();

    std::mutex &getMutexElementRemoved();

    std::condition_variable &getEventElementRemoved();

private:
    std::mutex              mutexReadWrite;
    std::mutex              mutexElementRemoved;
    std::condition_variable eventElementRemoved;
    std::size_t             maxSize;
};


#endif //INC_3_THREADSAFEQUEUE_HPP
