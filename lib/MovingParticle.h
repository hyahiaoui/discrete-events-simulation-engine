/**
 * \file    MovingParticle.cpp
 * \brief   Declaration of base class for moving particles (clients, vehicles, ...) in discrete events simulators
 * \date    June, 13th, 2011
 * \author  Yahiaoui H.
 */

#ifndef MOVINGPARTICLE_H
#define MOVINGPARTICLE_H

#include "SimulationEvent.h"
#include "common.h"

class MovingParticle : public SimulationEvent {
public:
    // Constructors
    /**
      * \brief  Default constructor
      * \param  newId   Identifier of the created particle
      * \param  name    Name of the created particle
      */
    MovingParticle(const ParticleId newId = invalidParticleId, const char* name = 0);

    /**
      * \brief Copy Constructor
      */
    MovingParticle(const MovingParticle& other);

    // Operators
    /**
      * \brief  Assignment operator
      */
    virtual MovingParticle operator=(const MovingParticle& other);

    /**
      * \brief  Comparison operator
      */
    virtual bool operator==(const MovingParticle& other);

    /**
      * \brief  Returns the particle's identifier
      */
    virtual ParticleId id() const;

    /**
      * \brief  Returns the module to be visited next
      */
    virtual ModuleId nextModule() const;

    /**
      * \brief  Returns the previously visited module
      */
    virtual ModuleId previousModule() const;

    /**
      * \brief  Returns the arrival time at the next module
      */
    virtual SimulationTime nextArrivalTime() const;

    /**
      * \brief  Returns the arrival time at the previously visited module
      */
    virtual SimulationTime previousArrivalTime() const;

    /**
      * \brief  Sets the specified parameter as the particle's identifier
      */
    virtual void setId(const ParticleId& newId);

    /**
      * \brief
      * \param
      * \param
      */
    virtual void send(const ModuleId destinationModuleId, const SimulationTime& arrivalTime);

    /**
      * \brief
      * \warning    Must ONLY be called by simulation engine. Must NOT be overloaded.
      */
    virtual void sim_handleArrivalAtModule();

    virtual const char* serialize() const;

protected:
    /**
      * \brief  This method invoked by simulation engine, when the particle arrives at its destination module, in simulation based on particles behaviours.
      *
      * This should be overloaded to specify the particle's actions when it arrives at the module 'm_nexModuleId'.
      */
    virtual void handleArrivalAtModule();

private:
    ParticleId m_id;
    ModuleId m_previousModuleId, m_nexModuleId;
    SimulationTime m_previousArrivalTime;
};

//std::ostream & operator<<(std::ostream & ost, const MovingParticle & obj);

#endif // MOVINGPARTICLE_H
