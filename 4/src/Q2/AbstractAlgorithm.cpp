#include "AbstractAlgorithm.hpp"

#include <utility>

AbstractAlgorithm::AbstractAlgorithm(std::vector<Page> pageTable, std::size_t physicalMemorySize, const char *algorithmName):
    pageTable(std::move(pageTable)), physicalMemorySize(physicalMemorySize), algorithmName(algorithmName)
{
}

const std::vector<Page> &AbstractAlgorithm::getPageTable() const
{
    return pageTable;
}

std::ostream &operator<<(std::ostream &ostream, const AbstractAlgorithm &algorithm)
{
    return ostream << algorithm.algorithmName;
}

std::size_t AbstractAlgorithm::getPhysicalMemorySize() const
{
    return physicalMemorySize;
}
