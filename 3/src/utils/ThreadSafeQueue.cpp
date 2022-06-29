#include "ThreadSafeQueue.hpp"

template<typename T>
ThreadSafeQueue<T>::ThreadSafeQueue(std::size_t maxSize): maxSize(maxSize)
{}

template<typename T>
bool ThreadSafeQueue<T>::add(const T &element)
{
    std::lock_guard<std::mutex> lockGuard(mutexReadWrite);

    if (std::queue<T>::size() == maxSize)
    {
        return false;
    }
    else
    {
        std::queue<T>::push(element);
        return true;
    }
}

template<typename T>
bool ThreadSafeQueue<T>::remove()
{
    std::lock_guard<std::mutex> lockGuard(mutexReadWrite);

    if (!std::queue<T>::size())
    {
        return false;
    }
    else
    {
        std::queue<T>::pop();
        eventElementRemoved.notify_all();
        return true;
    }
}

template<typename T>
T &ThreadSafeQueue<T>::element()
{
    std::lock_guard<std::mutex> lockGuard(mutexReadWrite);
    return std::queue<T>::front();
}

template<typename T>
bool ThreadSafeQueue<T>::empty()
{
    std::lock_guard<std::mutex> lockGuard(mutexReadWrite);
    return std::queue<T>::empty();
}

template<typename T>
std::mutex &ThreadSafeQueue<T>::getMutexElementRemoved()
{
    return mutexElementRemoved;
}

template<typename T>
std::condition_variable &ThreadSafeQueue<T>::getEventElementRemoved()
{
    return eventElementRemoved;
}

// Explicit template instantiation
#include <memory>
#include "../entities/Student.hpp"
template class ThreadSafeQueue<Student *>;
