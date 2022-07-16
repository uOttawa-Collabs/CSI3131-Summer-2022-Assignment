#include "Page.hpp"

std::size_t Page::getPageID() const
{
    return pageID;
}

void Page::setPageID(std::size_t pageID)
{
    Page::pageID = pageID;
}

std::size_t Page::getLastReferencedTime() const
{
    return lastReferencedTime;
}

void Page::setLastReferencedTime(std::size_t lastReferencedTime)
{
    Page::lastReferencedTime = lastReferencedTime;
}

std::size_t Page::getQueueEnteringTime() const
{
    return queueEnteringTime;
}

void Page::setQueueEnteringTime(std::size_t queueEnteringTime)
{
    Page::queueEnteringTime = queueEnteringTime;
}

bool Page::isInMemory() const
{
    return inMemory;
}

void Page::setInMemory(bool inMemory)
{
    Page::inMemory = inMemory;
}

std::ostream &operator<<(std::ostream &ostream, const Page &page)
{
    return ostream << page.getPageID();
}
