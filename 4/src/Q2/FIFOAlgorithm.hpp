#ifndef INC_4_FIFOALGORITHM_HPP
#define INC_4_FIFOALGORITHM_HPP

#include "AbstractAlgorithm.hpp"

class FIFOAlgorithm: public AbstractAlgorithm
{
public:
    FIFOAlgorithm(const std::vector<Page> &pageTable, std::size_t physicalMemorySize);

    std::size_t operator<<(const PageReferenceString &pageReferenceString) const override;
};


#endif //INC_4_FIFOALGORITHM_HPP
