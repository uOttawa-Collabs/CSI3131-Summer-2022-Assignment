#include "SynchronizedOutputStream.hpp"

#include <exception>

SynchronizedOutputStream::SynchronizedOutputStream(std::ostream &outputStream):
    outputStream(outputStream)
{
}

void SynchronizedOutputStream::accessStream(const SynchronizedOutputStream::StreamCallback &callback)
{
    std::lock_guard<std::mutex> lock(mutex);
    callback(outputStream);
}
