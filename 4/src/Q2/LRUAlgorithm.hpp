#ifndef INC_4_LRUALGORITHM_HPP
#define INC_4_LRUALGORITHM_HPP

#include "Page.hpp"
#include "PageReferenceString.hpp"
#include "AbstractAlgorithm.hpp"

class LRUAlgorithm: public AbstractAlgorithm
{
public:
    LRUAlgorithm(const std::vector<Page> &pageTable, std::size_t physicalMemorySize);

    std::size_t operator<<(const PageReferenceString &pageReferenceString) const override;
};


#endif //INC_4_LRUALGORITHM_HPP
