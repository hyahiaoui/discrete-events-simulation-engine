/**
 * \file    movingparticle.cpp
 * \brief   Implementation of base class for moving particles (clients, vehicles, ...) in discrete events simulators
 * \date    June, 13th, 2011
 * \author  Yahiaoui H.
 */

#include "movingparticle.h"
#include "desimulator.h"

#include <stdexcept>

cMovingParticle::cMovingParticle(const tParticleId newId, const char* name)
    : cSimulationEvent(cDESimulator::processedModule(), name)
    , m_id(newId)
    , m_previousModuleId(invalidModuleId)
    , m_nextModuleId(cDESimulator::processedModule())
    , m_previousArrivalTime()
{
}

cMovingParticle::cMovingParticle(const cMovingParticle& other)
    : cSimulationEvent(cDESimulator::processedModule())
    , m_id(invalidParticleId)
    , m_previousModuleId(invalidModuleId)
    , m_nextModuleId(cDESimulator::processedModule())
    , m_previousArrivalTime()
{
    operator=(other);
}

cMovingParticle cMovingParticle::operator=(const cMovingParticle& other)
{
    if (this != &other) {
        cSimulationEvent::operator=(other);

        m_id = other.m_id;
        m_nextModuleId = other.m_nextModuleId;
        m_previousModuleId = other.m_previousModuleId;
        m_previousArrivalTime = other.m_previousArrivalTime;
    }
    return *this;
}

bool cMovingParticle::operator==(const cMovingParticle& other)
{
    if (!cSimulationEvent::operator==(other))
        return false;
    return (m_id == other.m_id && m_nextModuleId == other.m_nextModuleId && m_previousModuleId == other.m_previousModuleId && m_previousArrivalTime == other.m_previousArrivalTime);
}

tParticleId cMovingParticle::id() const
{
    return m_id;
}

tModuleId cMovingParticle::nextModule() const
{
    return m_nextModuleId;
}

tModuleId cMovingParticle::previousModule() const
{
    return m_previousModuleId;
}

cSimulationTime cMovingParticle::nextArrivalTime() const
{
    return cSimulationEvent::occurrenceTime();
}

cSimulationTime cMovingParticle::previousArrivalTime() const
{
    return m_previousArrivalTime;
}

void cMovingParticle::setId(const tParticleId& newId)
{
    m_id = newId;
}

void cMovingParticle::send(const tModuleId destinationModuleId, const cSimulationTime& arrivalTime)
{
    if (destinationModuleId == invalidModuleId)
        throw std::runtime_error("Sending a moving particle to an unspecified module.");

    // Added by Yacine Ould Rouis: Correct the sending behaviour by recording the previous module ID before sending.
    m_previousModuleId = m_nextModuleId;

    m_nextModuleId = destinationModuleId;
    scheduleAt(arrivalTime);
}

void cMovingParticle::sim_handleArrivalAtModule()
{
    if (cDESimulator::simulationPattern() == cDESimulator::BasedOnModulesBehaviours)
        throw std::runtime_error("Invoking particle arrival at module while doing modules behaviours based simulation.");
    handleArrivalAtModule();
}

void cMovingParticle::handleArrivalAtModule()
{
    // Empty function. Must be overloaded to implement desired behaviour
}

const char* cMovingParticle::serialize() const
{
    std::ostringstream outStream;
    outStream << "cMovingParticle["
              << "id=" << id() << ", "
              << "name=\"" << name() << "\", "
              << "kind=" << kind() << ", "
              << "creator=" << creationModule() << ", "
              << "goingFrom=" << (previousModule() == invalidModuleId ? -1 : previousModule()) << ", "
              << "goingTo=" << (nextModule() == invalidModuleId ? -1 : nextModule()) << ", "
              << "arrivingAt=" << nextArrivalTime()
              << "]";
    return outStream.str().c_str();
}
