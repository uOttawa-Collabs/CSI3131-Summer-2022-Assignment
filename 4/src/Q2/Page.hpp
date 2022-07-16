#ifndef INC_4_PAGE_HPP
#define INC_4_PAGE_HPP

#include <iostream>
#include <cstdlib>
#include <cinttypes>

class Page
{
public:
    [[nodiscard]] std::size_t getPageID() const;

    void setPageID(std::size_t pageID);

    [[nodiscard]] std::size_t getLastReferencedTime() const;

    void setLastReferencedTime(std::size_t lastReferencedTime);

    [[nodiscard]] std::size_t getQueueEnteringTime() const;

    void setQueueEnteringTime(std::size_t queueEnteringTime);

    [[nodiscard]] bool isInMemory() const;

    void setInMemory(bool inMemory);

    friend std::ostream &operator<<(std::ostream &ostream, const Page &page);

private:
    std::size_t pageID;
    // This is for LRU
    std::size_t    lastReferencedTime;
    // This is for FIFO
    std::size_t    queueEnteringTime;
    bool        inMemory;
};

#endif //INC_4_PAGE_HPP
