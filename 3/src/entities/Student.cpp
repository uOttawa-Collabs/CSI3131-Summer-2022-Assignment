#include "Student.hpp"

#include "World.hpp"
#include "TeachingAssistant.hpp"

#include <chrono>
#include <utility>

void Student::start(Student &student)
{
    student.world.getOutputStream().accessStream([&student](std::ostream &stream) {
        stream << "[Student Bootstrapper] Creating student thread for " << student.name << std::endl;
    });

    student.thread = std::make_unique<std::thread>(std::thread([&student] {
        student.runner();
    }));

    student.thread->detach();
}

Student::Student(std::size_t studentID, std::string name, World &world):
    studentID(studentID), name(std::move(name)), world(world), randomEngine(std::random_device()())
{
}

void Student::helpBy(TeachingAssistant &teachingAssistant)
{
    world.getOutputStream().accessStream([this](std::ostream &stream) {
        stream << "[Student] " << name << " has been helped" << std::endl;
    });
    eventGetHelped.notify_all();
}

std::size_t Student::getStudentId() const
{
    return studentID;
}

const std::string &Student::getName() const
{
    return name;
}

void Student::runner()
{
    for (;;)
    {
        doProgramming();
        getHelp();
    }
}

void Student::doProgramming()
{
    // Delay for a random period of time (from 30 seconds to 60 seconds)
    std::uniform_int_distribution<> distribution(30, 60);
    auto                            time = distribution(randomEngine);

    world.getOutputStream().accessStream([this, time](std::ostream &stream) {
        stream << "[Student Thread] " << name << " is now programming for " << time << " seconds" << std::endl;
    });
    std::this_thread::sleep_for(std::chrono::seconds(time));
}

void Student::getHelp()
{
    world.getOutputStream().accessStream([this](std::ostream &stream) {
        stream << "[Student Thread] " << name << " is now need for help" << std::endl;
    });

    std::uniform_int_distribution<> distribution(10, 20);

    while (!world.getQueue().add(this))
    {
        auto time = distribution(randomEngine);
        world.getOutputStream().accessStream([this, time](std::ostream &stream) {
            stream << "[Student Thread] Queue is now full. " << name << " will check it out later" << std::endl;
            stream << "[Student Thread] " << name << " will now sleep for " << time << " seconds" << std::endl;
        });
        std::this_thread::sleep_for(std::chrono::seconds(time));
    }

    world.getOutputStream().accessStream([this](std::ostream &stream) {
        stream << "[Student Thread] " << name << " is now in queue" << std::endl;
    });

    while (world.getQueue().element() != this)
    {
        std::unique_lock<std::mutex> lock(world.getQueue().getMutexElementRemoved());
        world.getQueue().getEventElementRemoved().wait(lock);
    }

    world.getOutputStream().accessStream([this](std::ostream &stream) {
        stream << "[Student Thread] " << name << " is now waking up the TA" << std::endl;
    });
    world.getTeachingAssistant().wakeUpBy(*this);

    world.getOutputStream().accessStream([this](std::ostream &stream) {
        stream << "[Student Thread] " << name << " is now being helped" << std::endl;
    });

    std::unique_lock<std::mutex> lock(mutexGetHelped);
    eventGetHelped.wait(lock);

    world.getOutputStream().accessStream([this](std::ostream &stream) {
        stream << "[Student Thread] " << name << " got help" << std::endl;
    });
    world.getQueue().remove();
}

