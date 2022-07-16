#include <algorithm>
#include <iostream>
#include "LRUAlgorithm.hpp"

LRUAlgorithm::LRUAlgorithm(const std::vector<Page> &pageTable, std::size_t physicalMemorySize):
    AbstractAlgorithm(pageTable, physicalMemorySize, "LRU")
{
}

std::size_t LRUAlgorithm::operator<<(const PageReferenceString &pageReferenceString) const
{
    std::size_t       pageFaultCounter = 0;
    std::vector<Page> pageTable        = getPageTable();

    std::size_t time           = 0;
    std::size_t usedMemorySize = 0;

    std::for_each(pageReferenceString.begin(), pageReferenceString.end(), [this, &pageFaultCounter, &pageTable, &usedMemorySize, &time](std::size_t pageReference) {
        pageTable[pageReference].setLastReferencedTime(time);

        if (!pageTable[pageReference].isInMemory())
        {
            // The referenced page is not in memory, need to bring it in
            if (usedMemorySize >= getPhysicalMemorySize())
            {
                // No room left, need to swap off a page that has the oldest reference time
                std::size_t      minTime = time;
                std::size_t      targetPage;
                for (std::size_t i       = 0; i < pageTable.size(); ++i)
                {
                    if (pageTable[i].isInMemory() && pageTable[i].getLastReferencedTime() < minTime)
                    {
                        minTime    = pageTable[i].getLastReferencedTime();
                        targetPage = i;
                    }
                }
                // Swap off the page
                pageTable[targetPage].setInMemory(false);
                ++pageFaultCounter;
                --usedMemorySize;
                std::cerr
                    << "[" << *this << "] "
                    << "Page fault occurred when bringing in page "
                    << pageReference
                    << ", swapped off page "
                    << pageTable[targetPage].getPageID()
                    << std::endl;
            }

            // We have enough free pages, bring the page into memory
            pageTable[pageReference].setInMemory(true);
            ++usedMemorySize;
            std::cerr
                << "[" << *this << "] "
                << "Bringing in page "
                << pageTable[pageReference].getPageID()
                << std::endl;
        }
        else
        {
            std::cerr
                << "[" << *this << "] "
                << "Page "
                << pageTable[pageReference].getPageID()
                << " is already in memory"
                << std::endl;
        }

        ++time;
    });

    return pageFaultCounter;
}
