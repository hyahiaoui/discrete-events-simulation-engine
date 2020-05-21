/**
 * \file    simulationmodule.h
 * \brief   Declaration of cSimulationModule: base class for simulation components
 * \date    Jully, 26th, 2011
 * \author  Yahiaoui H.
 */

#ifndef SIMULATIONMODULE_H
#define SIMULATIONMODULE_H

#include <iostream>
#include <set>
#include <vector>

#include "baseobject.h"
#include "common.h"
#include "simulationtime.h"

class cMovingParticle;
class cModuleTimer;
class cDESimulator;

/**
  * \brief
  */
class cSimulationModule : public cBaseObject {
public:
    typedef std::set<cMovingParticle*> tMovingParticlesSet;
    typedef std::set<cModuleTimer*> tTimersSet;

    /**
      * \brief Constructor with module name and kind
      */
    cSimulationModule(int moduleKind, const std::string& name = std::string());

    /**
      * \brief  Destructor
      */
    virtual ~cSimulationModule();

    /**
      * \brief
      */
    tModuleId id() const
    {
        return m_moduleId;
    }

    /**
      * \brief      Called by the simulation engine when a simulation is about to start.
      * \warning    Must ONLY be called by simulation engine. Must NOT be overloaded.
      */
    virtual void sim_getReady();

    /**
      * \brief      Called by the simulation engine when a simulation is about to start.
      * \warning    Must ONLY be called by simulation engine. Must NOT be overloaded.
      */
    virtual void sim_terminate();

    /**
      * \brief      Called by the simulation engine when a particle enters the module.
      * \warning    Must ONLY be called by simulation engine. Must NOT be overloaded.
      */
    virtual void sim_handleParticleArrival(cMovingParticle* arrivingParticle);

    /**
      * \brief      Called by the simulation engine when a particle leaves the module.
      * \warning    Must ONLY be called by simulation engine. Must NOT be overloaded.
      */
    virtual void sim_handleParticleDeparture(cMovingParticle* departingParticle);

    /**
      * \brief      Called by the simulation engine when a timer of the module, fires.
      * \warning    Must ONLY be called by simulation engine. Must NOT be overloaded.
      */
    virtual void sim_handleTimerTriggering(cModuleTimer* triggeredTimer);

    /**
      * \brief      Called by the simulation engine when ..
      * \warning    Must ONLY be called by simulation engine. Must NOT be overloaded.
      */
    virtual void sim_setNeighbours(const std::set<tModuleId>& sources, const std::set<tModuleId>& dests);

    /**
      * \brief  Returns the number of modules linked to this module in the simulation, which can emit moving particles to the current module.
      */
    virtual unsigned neighbourSourceOfParticlesNb() const;
    /**
      * \brief  Returns the number of modules linked to this module in the simulation, which can receive moving particles sent from the current module.
      */
    virtual unsigned neighbourDestinationForParticlesNb() const;

    /**
      * \brief  Returns the Id of a module that can emit particles to the current module.
      * \param  index   position of the neighbour module in the array of neighbour modules that can emit particles.
      */
    virtual tModuleId neighbourSourceOfParticlesId(unsigned index) const;
    /**
      * \brief  Returns the Id of a module that can receive particles from the current module.
      * \param  index   position of the neighbour module in the array of neighbour modules that can receive particles.
      */
    virtual tModuleId neighbourDestinationForParticlesId(unsigned index) const;

    // Added by Yacine Ould Rouis: Give the possibility to access directly the properties of neighbour modules.
    /**
      * \brief  Returns the pointer to a module that can emit particles to the current module.
      * \param  index   position of the neighbour module in the array of neighbour modules that can emit particles.
      */
    virtual cSimulationModule* neighbourSourceOfParticlesPtr(unsigned index) const;
    /**
      * \brief  Returns the pointer to a module that can receive particles from the current module.
      * \param  index   position of the neighbour module in the array of neighbour modules that can receive particles.
      */
    virtual cSimulationModule* neighbourDestinationForParticlesPtr(unsigned index) const;

    virtual const char* serialize() const;

protected:
    /**
      * \brief
      * \param  arrivingParticle
      */
    virtual void captureParticle(cMovingParticle* arrivingParticle);

    /**
      * \brief
      * \param  departingParticle
      */
    virtual void releaseParticle(cMovingParticle* departingParticle);

    /**
      * \brief
      */
    virtual void getReady();

    /**
      * \brief
      * \param  arrivingParticle
      */
    virtual void handleParticleArrival(cMovingParticle* arrivingParticle);

    /**
      * \brief
      * \param  departingParticle
      */
    virtual void handleParticleDeparture(cMovingParticle* departingParticle);

    /**
      * \brief
      */
    virtual void handleTimerTriggering(cModuleTimer* triggeredTimer);

    /**
      * \brief
      */
    virtual void terminate();

private:
    typedef std::vector<tModuleId> NeighboursVector;

    tModuleId m_moduleId;
    tMovingParticlesSet m_particlesInModule;
    tTimersSet m_timersInModule;

    NeighboursVector m_neighboursSourcesOfParticles;
    NeighboursVector m_neighboursDestinationForParticles;
};

/**
  * \brief  Comparison operator used for modules sorting
  */
bool operator<(cSimulationModule const& mod1, cSimulationModule const& mod2);

/**
  * \brief  Comparison operator used for modules sorting.
  */
struct cSimulationModulePtrCmp {
    bool operator()(cSimulationModule* const& mod1, cSimulationModule* const& mod2) const;
};

#endif // SIMULATIONMODULE_H
