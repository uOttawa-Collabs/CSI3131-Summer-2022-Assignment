#include "PageReferenceString.hpp"

#include <exception>
#include <algorithm>
#include <utility>

PageReferenceString::PageReferenceString(std::size_t size):
    arraySize(size), randomEngine(std::random_device()())
{
    array = new std::size_t[size];
}

PageReferenceString::PageReferenceString(const std::size_t *pageReferenceNumbers, std::size_t size):
    PageReferenceString(size)
{
    std::copy(pageReferenceNumbers, pageReferenceNumbers + size, array);
}

PageReferenceString::~PageReferenceString()
{
    delete array;
}

PageReferenceString::PageReferenceString(const PageReferenceString &pageReferenceString):
    PageReferenceString(pageReferenceString.arraySize)
{
    std::copy(pageReferenceString.array, pageReferenceString.array + pageReferenceString.arraySize, array);
}

PageReferenceString::PageReferenceString(PageReferenceString &&pageReferenceString) noexcept:
    array(std::exchange(pageReferenceString.array, nullptr)),
    arraySize(std::exchange(pageReferenceString.arraySize, 0)),
    randomEngine(std::random_device()())
{
}

PageReferenceString &PageReferenceString::operator=(const PageReferenceString &pageReferenceString)
{
    if (this != &pageReferenceString)
    {
        return *this = PageReferenceString(pageReferenceString);
    }
    else
    {
        return *this;
    }
}

PageReferenceString &PageReferenceString::operator=(PageReferenceString &&pageReferenceString) noexcept
{
    std::swap(pageReferenceString.array, array);
    std::swap(pageReferenceString.arraySize, arraySize);
    return *this;
}

std::size_t PageReferenceString::operator[](std::size_t i) const
{
    if (array == nullptr)
    {
        throw std::runtime_error("Pointer array is nullptr");
    }

    if (i >= arraySize)
    {
        throw std::out_of_range("Index is out of range");
    }

    return array[i];
}

std::ostream &operator<<(std::ostream &ostream, const PageReferenceString &pageReferenceString)
{
    ostream << '(';
    if (pageReferenceString.arraySize != 0)
    {
        ostream << pageReferenceString[0];
        for (std::size_t i = 1; i < pageReferenceString.arraySize; ++i)
        {
            ostream << ", " << pageReferenceString[i];
        }
    }
    return ostream << ')';
}

PageReferenceString::Iterator PageReferenceString::begin()
{
    return array;
}

PageReferenceString::Iterator PageReferenceString::end()
{
    return array + arraySize;
}

PageReferenceString::ConstIterator PageReferenceString::begin() const
{
    return array;
}

PageReferenceString::ConstIterator PageReferenceString::end() const
{
    return array + arraySize;
}

std::size_t PageReferenceString::getArraySize() const
{
    return arraySize;
}

void PageReferenceString::randomize(std::size_t min, std::size_t max)
{
    std::uniform_int_distribution<std::size_t> distribution(min, max);
    std::size_t count = 0;
    std::for_each(array, array + arraySize, [this, &distribution, &count](std::size_t &item) {
        std::size_t random;
        do
        {
            random = distribution(randomEngine);
        }
        while (count && array[count - 1] == random);

        item = random;
        ++count;
    });
}
