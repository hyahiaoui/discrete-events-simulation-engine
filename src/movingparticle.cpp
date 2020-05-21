/**
 * \file    MovingParticle.cpp
 * \brief   Implementation of base class for moving particles (clients, vehicles, ...) in discrete events simulators
 * \date    June, 13th, 2011
 * \author  Yahiaoui H.
 */

#include "MovingParticle.h"
#include "DESimulator.h"

#include <stdexcept>

MovingParticle::MovingParticle(const ParticleId newId, const char* name)
    : SimulationEvent(DESimulator::processedModule(), name)
    , m_id(newId)
    , m_previousModuleId(invalidModuleId)
    , m_nexModuleId(DESimulator::processedModule())
    , m_previousArrivalTime()
{
}

MovingParticle::MovingParticle(const MovingParticle& other)
    : SimulationEvent(DESimulator::processedModule())
    , m_id(invalidParticleId)
    , m_previousModuleId(invalidModuleId)
    , m_nexModuleId(DESimulator::processedModule())
    , m_previousArrivalTime()
{
    operator=(other);
}

MovingParticle MovingParticle::operator=(const MovingParticle& other)
{
    if (this != &other) {
        SimulationEvent::operator=(other);

        m_id = other.m_id;
        m_nexModuleId = other.m_nexModuleId;
        m_previousModuleId = other.m_previousModuleId;
        m_previousArrivalTime = other.m_previousArrivalTime;
    }
    return *this;
}

bool MovingParticle::operator==(const MovingParticle& other)
{
    if (!SimulationEvent::operator==(other))
        return false;
    return (m_id == other.m_id && m_nexModuleId == other.m_nexModuleId && m_previousModuleId == other.m_previousModuleId && m_previousArrivalTime == other.m_previousArrivalTime);
}

ParticleId MovingParticle::id() const
{
    return m_id;
}

ModuleId MovingParticle::nextModule() const
{
    return m_nexModuleId;
}

ModuleId MovingParticle::previousModule() const
{
    return m_previousModuleId;
}

SimulationTime MovingParticle::nextArrivalTime() const
{
    return SimulationEvent::occurrenceTime();
}

SimulationTime MovingParticle::previousArrivalTime() const
{
    return m_previousArrivalTime;
}

void MovingParticle::setId(const ParticleId& newId)
{
    m_id = newId;
}

void MovingParticle::send(const ModuleId destinationModuleId, const SimulationTime& arrivalTime)
{
    if (destinationModuleId == invalidModuleId)
        throw std::runtime_error("Sending a moving particle to an unspecified module.");

    // Added by Yacine Ould Rouis: Correct the sending behaviour by recording the previous module ID before sending.
    m_previousModuleId = m_nexModuleId;

    m_nexModuleId = destinationModuleId;
    scheduleAt(arrivalTime);
}

void MovingParticle::sim_handleArrivalAtModule()
{
    if (DESimulator::simulationPattern() == DESimulator::BasedOnModulesBehaviours)
        throw std::runtime_error("Invoking particle arrival at module while doing modules behaviours based simulation.");
    handleArrivalAtModule();
}

void MovingParticle::handleArrivalAtModule()
{
    // Empty function. Must be overloaded to implement desired behaviour
}

const char* MovingParticle::serialize() const
{
    std::ostringstream outStream;
    outStream << "MovingParticle["
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
