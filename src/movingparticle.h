/**
 * \file    movingparticle.cpp
 * \brief   Declaration of base class for moving particles (clients, vehicles, ...) in discrete events simulators
 * \date    June, 13th, 2011
 * \author  Yahiaoui H.
 */

#ifndef MOVINGPARTICLE_H
#define MOVINGPARTICLE_H

#include "common.h"
#include "simulationevent.h"

class cMovingParticle : public cSimulationEvent {
public:
    // Constructors
    /**
      * \brief  Default constructor
      * \param  newId   Identifier of the created particle
      * \param  name    Name of the created particle
      */
    cMovingParticle(const tParticleId newId = invalidParticleId, const char* name = 0);

    /**
      * \brief Copy Constructor
      */
    cMovingParticle(const cMovingParticle& other);

    // Operators
    /**
      * \brief  Assignment operator
      */
    virtual cMovingParticle operator=(const cMovingParticle& other);

    /**
      * \brief  Comparison operator
      */
    virtual bool operator==(const cMovingParticle& other);

    /**
      * \brief  Returns the particle's identifier
      */
    virtual tParticleId id() const;

    /**
      * \brief  Returns the module to be visited next
      */
    virtual tModuleId nextModule() const;

    /**
      * \brief  Returns the previously visited module
      */
    virtual tModuleId previousModule() const;

    /**
      * \brief  Returns the arrival time at the next module
      */
    virtual cSimulationTime nextArrivalTime() const;

    /**
      * \brief  Returns the arrival time at the previously visited module
      */
    virtual cSimulationTime previousArrivalTime() const;

    /**
      * \brief  Sets the specified parameter as the particle's identifier
      */
    virtual void setId(const tParticleId& newId);

    /**
      * \brief
      * \param
      * \param
      */
    virtual void send(const tModuleId destinationModuleId, const cSimulationTime& arrivalTime);

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
      * This should be overloaded to specify the particle's actions when it arrives at the module 'm_nextModuleId'.
      */
    virtual void handleArrivalAtModule();

private:
    tParticleId m_id;
    tModuleId m_previousModuleId, m_nextModuleId;
    cSimulationTime m_previousArrivalTime;
};

//std::ostream & operator<<(std::ostream & ost, const cMovingParticle & obj);

#endif // MOVINGPARTICLE_H
