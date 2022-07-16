#ifndef INC_4_ABSTRACTALGORITHM_HPP
#define INC_4_ABSTRACTALGORITHM_HPP

#include <vector>
#include <ostream>

#include "Page.hpp"
#include "PageReferenceString.hpp"

class AbstractAlgorithm
{
public:
    AbstractAlgorithm(std::vector<Page> pageTable, std::size_t physicalMemorySize, const char *algorithmName = "");

    virtual ~AbstractAlgorithm() = default;

    virtual std::size_t operator<<(const PageReferenceString &pageReferenceString) const = 0;

    [[nodiscard]] const std::vector<Page> &getPageTable() const;

    [[nodiscard]] std::size_t getPhysicalMemorySize() const;

    friend std::ostream &operator<<(std::ostream &ostream, const AbstractAlgorithm &algorithm);

private:
    const char *algorithmName;
    std::vector<Page> pageTable;
    std::size_t physicalMemorySize;
};


#endif //INC_4_ABSTRACTALGORITHM_HPP
