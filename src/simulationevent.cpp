#include "simulationevent.h"
#include "desimulator.h"

#include <stdexcept>

cSimulationEvent::cSimulationEvent(const tModuleId& creatorId, const std::string& name)
    : cBaseObject(name)
    , m_occurrenceTime()
    , m_scheduled(false)
{
    m_creationTime = cDESimulator::simTime();
    m_creationModule = creatorId;
}

cSimulationEvent::cSimulationEvent(const cSimulationEvent& other)
    : cBaseObject()
    , m_occurrenceTime()
    , m_scheduled(false)
{
    m_creationTime = cDESimulator::simTime();
    operator=(other);
}

cSimulationEvent::~cSimulationEvent() noexcept(false)
{
    // Added by Yacine Ould Rouis: Give the possibility of deleting scheduled events, when the simulation is finished.
    if (isScheduled() && cDESimulator::isCurrentlySimulating())
        throw std::runtime_error("Destroying still scheduled event.");
}

cSimulationEvent& cSimulationEvent::operator=(const cSimulationEvent& other)
{
    if (this != &other) {
        cBaseObject::operator=(other);
        if (other.isScheduled()) {
            scheduleAt(other.m_occurrenceTime);
        }
    }
    return *this;
}

bool cSimulationEvent::operator==(const cSimulationEvent& other)
{
    if (cBaseObject::operator==(other))
        return ((m_scheduled == other.m_scheduled)
            && (m_occurrenceTime == other.m_occurrenceTime));
    else
        return false;
}

const cSimulationTime& cSimulationEvent::occurrenceTime() const
{
    return m_occurrenceTime;
}

void cSimulationEvent::setOccurenceTime(const cSimulationTime& occurenceTime)
{
    m_occurrenceTime = occurenceTime;
}

void cSimulationEvent::scheduleAt(const cSimulationTime& occurenceTime)
{
    m_occurrenceTime = occurenceTime;
    cDESimulator::theSimulator()->scheduleFutureEvent(this);
    m_scheduled = true;
}

bool cSimulationEvent::isScheduled() const
{
    return m_scheduled;
}

void cSimulationEvent::cancelScheduling()
{
    cDESimulator::theSimulator()->cancelFutureEvent(this);
    m_scheduled = false;
}

const char* cSimulationEvent::serialize() const
{
    std::ostringstream outStream;
    outStream << "cSimulationEvent["
              << "name=\"" << name() << "\", "
              << "kind=" << kind() << ", "
              << "scheduled=" << (isScheduled() ? "true" : "false") << ", "
              << "scheduledAt=" << occurrenceTime() << "]";
    return outStream.str().c_str();
}

const cSimulationTime& cSimulationEvent::creationTime() const
{
    return m_creationTime;
}

const tModuleId& cSimulationEvent::creationModule() const
{
    return m_creationModule;
}
