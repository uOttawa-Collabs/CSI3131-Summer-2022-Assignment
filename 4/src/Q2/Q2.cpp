#include "Q2.h"

#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

#include "Page.hpp"
#include "PageReferenceString.hpp"
#include "LRUAlgorithm.hpp"
#include "FIFOAlgorithm.hpp"

constexpr std::size_t PAGE_TABLE_SIZE = 10;
constexpr std::size_t PHYSICAL_MEMORY_SIZE = 5;

void entryQ2()
{
    std::vector<Page> pageTable(10);

    // Initialize pages
    {
        std::size_t pageID = 0;
        std::for_each(pageTable.begin(), pageTable.end(), [&pageID](Page &page) {
            page.setPageID(pageID++);
        });
    }

    PageReferenceString pageReferenceString(10);
    pageReferenceString.randomize(0, 9);

    std::unique_ptr<AbstractAlgorithm> algorithms[] = {
        std::make_unique<LRUAlgorithm>(pageTable, PHYSICAL_MEMORY_SIZE),
        std::make_unique<FIFOAlgorithm>(pageTable, PHYSICAL_MEMORY_SIZE)
    };

    std::cout << "For page reference string: " << pageReferenceString << "," << std::endl;
    std::cout << "the page fault count for each algorithms are:" << std::endl;
    for (std::unique_ptr<AbstractAlgorithm> &algorithm: algorithms)
    {
        std::cout << *algorithm << ": " << (*algorithm << pageReferenceString) << std::endl;
    }
}
