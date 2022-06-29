#include "World.hpp"

#include <chrono>
#include <thread>
#include <iostream>

World::World(std::size_t chairCount, std::size_t studentCount):
    chairCount(chairCount), studentCount(studentCount), teachingAssistant(*this), outputStream(std::cout), queue(chairCount)
{
    for (std::size_t i = 0; i < studentCount; ++i)
    {
        std::string studentName = std::string("Student ") + std::to_string(i);
        outputStream.accessStream([&studentName](std::ostream &stream) {
            stream << "[World] Creating student instance " << studentName << std::endl;
        });
        students.emplace_back(new Student(i, studentName, *this));
    }
}

int World::simulate()
{
    outputStream.accessStream([](std::ostream &stream) {
        stream << "[World] When the program is running, press Enter to stop the program" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
    });

    TeachingAssistant::start(teachingAssistant);
    for (std::shared_ptr<Student> &student: students)
    {
        Student::start(*student);
    }

    getchar();
    return 0;
}

std::size_t World::getChairCount() const
{
    return chairCount;
}

std::size_t World::getStudentCount() const
{
    return studentCount;
}

TeachingAssistant &World::getTeachingAssistant()
{
    return teachingAssistant;
}

std::vector<std::shared_ptr<Student>> &World::getStudents()
{
    return students;
}

ThreadSafeQueue<Student *> &World::getQueue()
{
    return queue;
}

SynchronizedOutputStream &World::getOutputStream()
{
    return outputStream;
}
