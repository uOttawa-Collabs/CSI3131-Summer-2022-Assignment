#ifndef INC_3_SYNCHRONIZEDOUTPUTSTREAM_HPP
#define INC_3_SYNCHRONIZEDOUTPUTSTREAM_HPP

#include <ostream>
#include <mutex>
#include <functional>

class SynchronizedOutputStream
{
public:
    using StreamCallback = std::function<void(std::ostream &)>;

public:
    explicit SynchronizedOutputStream(std::ostream &outputStream);

    virtual ~SynchronizedOutputStream() = default;

    SynchronizedOutputStream(const SynchronizedOutputStream &outputMonitor) = delete;

    SynchronizedOutputStream(SynchronizedOutputStream &&outputMonitor) = delete;

    SynchronizedOutputStream &operator=(const SynchronizedOutputStream &outputMonitor) = delete;

    SynchronizedOutputStream &operator=(SynchronizedOutputStream &&outputMonitor) = delete;

    void accessStream(const SynchronizedOutputStream::StreamCallback &callback);

private:
    std::mutex   mutex;
    std::ostream &outputStream;
};

#endif //INC_3_SYNCHRONIZEDOUTPUTSTREAM_HPP
