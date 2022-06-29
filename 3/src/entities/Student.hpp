#ifndef INC_3_STUDENT_HPP
#define INC_3_STUDENT_HPP

#include <string>
#include <thread>
#include <random>
#include <mutex>
#include <condition_variable>

#include "../utils/ThreadSafeQueue.hpp"

class World;

class TeachingAssistant;

class Student
{
public:
    static void start(Student &student);

public:
    Student(std::size_t studentID, std::string name, World &world);

    virtual ~Student() = default;

    Student(const Student &student) = delete;

    Student(Student &&student) = delete;

    Student &operator=(const Student &student) = delete;

    Student &operator=(Student &&student) = delete;

    void helpBy(TeachingAssistant &teachingAssistant);

    std::size_t getStudentId() const;

    const std::string &getName() const;

private:
    void runner();

    void doProgramming();

    void getHelp();

    std::size_t studentID;

    std::string name;
    World       &world;

    std::mt19937                 randomEngine;
    std::unique_ptr<std::thread> thread;

    std::mutex              mutexGetHelped;
    std::condition_variable eventGetHelped;
};


#endif //INC_3_ST{}UDENT_HPP
