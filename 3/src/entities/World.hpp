#ifndef INC_3_WORLD_HPP
#define INC_3_WORLD_HPP

#include <cinttypes>
#include <memory>

#include "Student.hpp"
#include "TeachingAssistant.hpp"

#include "../utils/ThreadSafeQueue.hpp"
#include "../utils/SynchronizedOutputStream.hpp"

class World
{
public:
    World(std::size_t chairCount, std::size_t studentCount);

    virtual ~World() = default;

    int simulate();

    [[nodiscard]] std::size_t getChairCount() const;

    [[nodiscard]] std::size_t getStudentCount() const;

    [[nodiscard]] TeachingAssistant &getTeachingAssistant();

    [[nodiscard]] std::vector<std::shared_ptr<Student>> &getStudents();

    [[nodiscard]] ThreadSafeQueue<Student *> &getQueue();

    [[nodiscard]] SynchronizedOutputStream &getOutputStream();

private:
    std::size_t                           chairCount, studentCount;
    TeachingAssistant                     teachingAssistant;
    std::vector<std::shared_ptr<Student>> students;
    ThreadSafeQueue<Student *>            queue;
    SynchronizedOutputStream              outputStream;
};


#endif //INC_3_WORLD_HPP
