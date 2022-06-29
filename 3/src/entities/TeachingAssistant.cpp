#include "TeachingAssistant.hpp"

#include "World.hpp"
#include "Student.hpp"

void TeachingAssistant::start(TeachingAssistant &teachingAssistant)
{
    teachingAssistant.world.getOutputStream().accessStream([&teachingAssistant](std::ostream &stream) {
        stream << "[Teaching Assistant Bootstrapper] Creating teaching assistant thread" << std::endl;
    });

    teachingAssistant.thread = std::make_unique<std::thread>(std::thread([&teachingAssistant] {
        teachingAssistant.runner();
    }));

    teachingAssistant.thread->detach();
}


TeachingAssistant::TeachingAssistant(World &world):
    world(world), randomEngine(std::random_device()())
{
}

void TeachingAssistant::wakeUpBy(Student &student)
{
    eventWakeUp.notify_all();
    world.getOutputStream().accessStream([this, &student](std::ostream &stream) {
        stream << "[Teaching Assistant] TA is waken up by " << student.getName() << std::endl;
    });
}

void TeachingAssistant::runner()
{
    for (;;)
    {
        if (!world.getQueue().empty() && world.getQueue().element() != nullptr)
        {
            helpStudent(*world.getQueue().element());
        }
        else
        {
            sleep();
        }
    }
}

void TeachingAssistant::sleep()
{
    world.getOutputStream().accessStream([this](std::ostream &stream) {
        stream << "[Teaching Assistant Thread] TA is now going to sleep" << std::endl;
    });
    std::unique_lock<std::mutex> lock(mutexWakeUp);
    eventWakeUp.wait(lock);
}

void TeachingAssistant::helpStudent(Student &student)
{
    std::uniform_int_distribution<> distribution(10, 30);
    auto                            time = distribution(randomEngine);

    world.getOutputStream().accessStream([this, &student, time](std::ostream &stream) {
        stream << "[Teaching Assistant Thread] TA is helping " << student.getName() << " for " << time << " seconds" << std::endl;
    });

    std::this_thread::sleep_for(std::chrono::seconds(time));
    student.helpBy(*this);
}

