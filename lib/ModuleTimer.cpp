#include "ModuleTimer.h"
#include "DESimulator.h"
#include "SimulationModule.h"

#include <stdexcept>

ModuleTimer::ModuleTimer(const std::string name)
    : SimulationEvent(DESimulator::processedModule(), name)
    , m_ownerModuleId(DESimulator::processedModule())
    , m_attachedData(NULL)
{
}

ModuleTimer::ModuleTimer(const ModuleTimer& other)
    : SimulationEvent(DESimulator::processedModule(), other.name())
    , m_ownerModuleId(DESimulator::processedModule())
    , m_attachedData(NULL)
{
    operator=(other);
}

ModuleTimer::~ModuleTimer()
{
}

ModuleTimer& ModuleTimer::operator=(const ModuleTimer& other)
{
    if (this != &other) {
        SimulationEvent::operator=(other);
        m_attachedData = other.m_attachedData;
        m_ownerModuleId = other.ownerModuleId();
    }
    return *this;
}

SimulationTime ModuleTimer::triggerTime() const
{
    return SimulationEvent::occurrenceTime();
}

ModuleId ModuleTimer::ownerModuleId() const
{
    return m_ownerModuleId;
}

void* ModuleTimer::attachedData() const
{
    return m_attachedData;
}

void ModuleTimer::setOwnerModuleId(const ModuleId newOwner)
{
    m_ownerModuleId = newOwner;
}

void ModuleTimer::setAttachedData(void* data)
{
    m_attachedData = data;
}

void ModuleTimer::scheduleAt(const SimulationTime& occurenceTime)
{
    if (ownerModuleId() == invalidModuleId)
        throw std::runtime_error("Trying to schedule a timer not attached to a module.");

    SimulationEvent::scheduleAt(occurenceTime);
}

void ModuleTimer::scheduleAt(const SimulationTime& occurenceTime, const ModuleId newOwnerModuleId)
{
    setOwnerModuleId(newOwnerModuleId);
    scheduleAt(occurenceTime);
}

void ModuleTimer::scheduleAt(const SimulationTime& occurenceTime, const SimulationModule* newOwnerModule)
{
    if (!newOwnerModule)
        throw std::runtime_error("Trying to schedule a timer not attached to a module.");

    scheduleAt(occurenceTime, newOwnerModule->id());
}

void ModuleTimer::sim_handleTriggering()
{
    if (DESimulator::simulationPattern() == DESimulator::BasedOnModulesBehaviours)
        throw std::runtime_error("Invoking timer triggering while doing modules behaviours based simulation.");
    handleTriggering();
}

void ModuleTimer::handleTriggering()
{
    // Empty function. Must be overloaded to implement desired behaviour
}

const char* ModuleTimer::serialize() const
{
    std::ostringstream outStream;
    outStream << "ModuleTimer["
              << "name=\"" << name() << "\", "
              << "kind=" << kind() << ", "
              << "owner=" << ownerModuleId() << ", "
              << "scheduled=" << (isScheduled() ? "true" : "false") << ", "
              << "triggerAt=" << triggerTime() << "]";
    return outStream.str().c_str();
}
