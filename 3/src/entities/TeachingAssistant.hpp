#ifndef INC_3_TEACHINGASSISTANT_HPP
#define INC_3_TEACHINGASSISTANT_HPP

#include "../utils/ThreadSafeQueue.hpp"

#include <thread>
#include <random>

class World;

class Student;

class TeachingAssistant
{
public:
    static void start(TeachingAssistant &teachingAssistant);

public:
    explicit TeachingAssistant(World &world);

    virtual ~TeachingAssistant() = default;

    TeachingAssistant(const TeachingAssistant &TeachingAssistant) = delete;

    TeachingAssistant(TeachingAssistant &&TeachingAssistant) = delete;

    TeachingAssistant &operator=(const TeachingAssistant &TeachingAssistant) = delete;

    TeachingAssistant &operator=(TeachingAssistant &&TeachingAssistant) = delete;

    void wakeUpBy(Student &student);

private:
    void runner();

    void sleep();

    void helpStudent(Student &student);

    World &world;
    std::mt19937                 randomEngine;

    std::unique_ptr<std::thread> thread;
    std::mutex                   mutexWakeUp;
    std::condition_variable      eventWakeUp;
};


#endif //INC_3_TEACHINGASSISTANT_HPP
