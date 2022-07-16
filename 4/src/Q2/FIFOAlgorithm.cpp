#include "FIFOAlgorithm.hpp"
#include <algorithm>
#include <queue>

FIFOAlgorithm::FIFOAlgorithm(const std::vector<Page> &pageTable, std::size_t physicalMemorySize):
    AbstractAlgorithm(pageTable, physicalMemorySize, "FIFO")
{
}

std::size_t FIFOAlgorithm::operator<<(const PageReferenceString &pageReferenceString) const
{
    std::size_t        pageFaultCounter = 0;
    std::vector<Page>  pageTable        = getPageTable();
    std::queue<Page *> queue;

    std::size_t time           = 0;
    std::size_t usedMemorySize = 0;

    std::for_each(pageReferenceString.begin(), pageReferenceString.end(), [this, &pageFaultCounter, &pageTable, &queue, &usedMemorySize, &time](std::size_t pageReference) {
        if (!pageTable[pageReference].isInMemory())
        {
            // The referenced page is not in memory, need to bring it in
            if (usedMemorySize >= getPhysicalMemorySize())
            {
                // No room left, need to pop out a page
                std::size_t targetPage = queue.front()->getPageID();
                queue.front()->setInMemory(false);
                queue.pop();
                ++pageFaultCounter;
                --usedMemorySize;
                std::cerr
                    << "["
                    << *this
                    << "] "
                    << "Page fault occurred when bringing in page "
                    << pageReference
                    << ", swapped off page "
                    << pageTable[targetPage].getPageID()
                    << std::endl;
            }

            // We have enough free pages, bring the page into memory
            queue.push(&pageTable[pageReference]);
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
