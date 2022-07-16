#ifndef INC_4_PAGEREFERENCESTRING_HPP
#define INC_4_PAGEREFERENCESTRING_HPP

#include <cstdlib>
#include <cinttypes>
#include <ostream>
#include <random>

class PageReferenceString
{
public:
    using Iterator = std::size_t *;
    using ConstIterator = const std::size_t *;

    explicit PageReferenceString(std::size_t size);
    PageReferenceString(const std::size_t *pageReferenceNumbers, std::size_t size);

    virtual ~PageReferenceString();
    PageReferenceString(const PageReferenceString &pageReferenceString);
    PageReferenceString(PageReferenceString &&pageReferenceString) noexcept;

    PageReferenceString &operator=(const PageReferenceString &pageReferenceString);
    PageReferenceString &operator=(PageReferenceString &&pageReferenceString) noexcept;

    std::size_t operator[](std::size_t i) const;

    friend std::ostream &operator<<(std::ostream &ostream, const PageReferenceString &pageReferenceString);

    [[nodiscard]] Iterator begin();
    [[nodiscard]] Iterator end();

    [[nodiscard]] ConstIterator begin() const;
    [[nodiscard]] ConstIterator end() const;

    [[nodiscard]] std::size_t getArraySize() const;
    void randomize(std::size_t min, std::size_t max);

private:
    std::size_t *array;
    std::size_t arraySize;
    std::mt19937 randomEngine;
};


#endif //INC_4_PAGEREFERENCESTRING_HPP
