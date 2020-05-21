#include "SimulationEvent.h"
#include "DESimulator.h"

#include <stdexcept>

SimulationEvent::SimulationEvent(const ModuleId& creatorId, const std::string& name)
    : BaseObject(name)
    , m_occurrenceTime()
    , m_scheduled(false)
{
    m_creationTime = DESimulator::simTime();
    m_creationModule = creatorId;
}

SimulationEvent::SimulationEvent(const SimulationEvent& other)
    : BaseObject()
    , m_occurrenceTime()
    , m_scheduled(false)
{
    m_creationTime = DESimulator::simTime();
    operator=(other);
}

SimulationEvent::~SimulationEvent() noexcept(false)
{
    // Added by Yacine Ould Rouis: Give the possibility of deleting scheduled events, when the simulation is finished.
    if (isScheduled() && DESimulator::isCurrentlySimulating())
        throw std::runtime_error("Destroying still scheduled event.");
}

SimulationEvent& SimulationEvent::operator=(const SimulationEvent& other)
{
    if (this != &other) {
        BaseObject::operator=(other);
        if (other.isScheduled()) {
            scheduleAt(other.m_occurrenceTime);
        }
    }
    return *this;
}

bool SimulationEvent::operator==(const SimulationEvent& other)
{
    if (BaseObject::operator==(other))
        return ((m_scheduled == other.m_scheduled)
            && (m_occurrenceTime == other.m_occurrenceTime));
    else
        return false;
}

const SimulationTime& SimulationEvent::occurrenceTime() const
{
    return m_occurrenceTime;
}

void SimulationEvent::setOccurenceTime(const SimulationTime& occurenceTime)
{
    m_occurrenceTime = occurenceTime;
}

void SimulationEvent::scheduleAt(const SimulationTime& occurenceTime)
{
    m_occurrenceTime = occurenceTime;
    DESimulator::theSimulator()->scheduleFutureEvent(this);
    m_scheduled = true;
}

bool SimulationEvent::isScheduled() const
{
    return m_scheduled;
}

void SimulationEvent::cancelScheduling()
{
    DESimulator::theSimulator()->cancelFutureEvent(this);
    m_scheduled = false;
}

const char* SimulationEvent::serialize() const
{
    std::ostringstream outStream;
    outStream << "SimulationEvent["
              << "name=\"" << name() << "\", "
              << "kind=" << kind() << ", "
              << "scheduled=" << (isScheduled() ? "true" : "false") << ", "
              << "scheduledAt=" << occurrenceTime() << "]";
    return outStream.str().c_str();
}

const SimulationTime& SimulationEvent::creationTime() const
{
    return m_creationTime;
}

const ModuleId& SimulationEvent::creationModule() const
{
    return m_creationModule;
}
