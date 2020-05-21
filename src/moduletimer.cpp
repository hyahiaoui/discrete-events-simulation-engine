#include "moduletimer.h"
#include "desimulator.h"
#include "simulationmodule.h"

#include <stdexcept>

cModuleTimer::cModuleTimer(const std::string name)
    : cSimulationEvent(cDESimulator::processedModule(), name)
    , m_ownerModuleId(cDESimulator::processedModule())
    , m_attachedData(NULL)
{
}

cModuleTimer::cModuleTimer(const cModuleTimer& other)
    : cSimulationEvent(cDESimulator::processedModule(), other.name())
    , m_ownerModuleId(cDESimulator::processedModule())
    , m_attachedData(NULL)
{
    operator=(other);
}

cModuleTimer::~cModuleTimer()
{
}

cModuleTimer& cModuleTimer::operator=(const cModuleTimer& other)
{
    if (this != &other) {
        cSimulationEvent::operator=(other);
        m_attachedData = other.m_attachedData;
        m_ownerModuleId = other.ownerModuleId();
    }
    return *this;
}

cSimulationTime cModuleTimer::triggerTime() const
{
    return cSimulationEvent::occurrenceTime();
}

tModuleId cModuleTimer::ownerModuleId() const
{
    return m_ownerModuleId;
}

void* cModuleTimer::attachedData() const
{
    return m_attachedData;
}

void cModuleTimer::setOwnerModuleId(const tModuleId newOwner)
{
    m_ownerModuleId = newOwner;
}

void cModuleTimer::setAttachedData(void* data)
{
    m_attachedData = data;
}

void cModuleTimer::scheduleAt(const cSimulationTime& occurenceTime)
{
    if (ownerModuleId() == invalidModuleId)
        throw std::runtime_error("Trying to schedule a timer not attached to a module.");

    cSimulationEvent::scheduleAt(occurenceTime);
}

void cModuleTimer::scheduleAt(const cSimulationTime& occurenceTime, const tModuleId newOwnerModuleId)
{
    setOwnerModuleId(newOwnerModuleId);
    scheduleAt(occurenceTime);
}

void cModuleTimer::scheduleAt(const cSimulationTime& occurenceTime, const cSimulationModule* newOwnerModule)
{
    if (!newOwnerModule)
        throw std::runtime_error("Trying to schedule a timer not attached to a module.");

    scheduleAt(occurenceTime, newOwnerModule->id());
}

void cModuleTimer::sim_handleTriggering()
{
    if (cDESimulator::simulationPattern() == cDESimulator::BasedOnModulesBehaviours)
        throw std::runtime_error("Invoking timer triggering while doing modules behaviours based simulation.");
    handleTriggering();
}

void cModuleTimer::handleTriggering()
{
    // Empty function. Must be overloaded to implement desired behaviour
}

const char* cModuleTimer::serialize() const
{
    std::ostringstream outStream;
    outStream << "cModuleTimer["
              << "name=\"" << name() << "\", "
              << "kind=" << kind() << ", "
              << "owner=" << ownerModuleId() << ", "
              << "scheduled=" << (isScheduled() ? "true" : "false") << ", "
              << "triggerAt=" << triggerTime() << "]";
    return outStream.str().c_str();
}
