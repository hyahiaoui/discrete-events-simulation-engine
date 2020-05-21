/**
 * \file    SimulationModule.h
 * \brief   Declaration of SimulationModule: base class for simulation components
 * \date    Jully, 26th, 2011
 * \author  Yahiaoui H.
 */

#ifndef SIMULATIONMODULE_H
#define SIMULATIONMODULE_H

#include "BaseObject.h"
#include "SimulationTime.h"
#include "common.h"

#include <iostream>
#include <set>
#include <vector>

class MovingParticle;
class ModuleTimer;
class DESimulator;

/**
  * \brief
  */
class SimulationModule : public BaseObject {
public:
    typedef std::set<MovingParticle*> tMovingParticlesSet;
    typedef std::set<ModuleTimer*> tTimersSet;

    /**
      * \brief Constructor with module name and kind
      */
    SimulationModule(int moduleKind, const std::string& name = std::string());

    /**
      * \brief  Destructor
      */
    virtual ~SimulationModule();

    /**
      * \brief
      */
    ModuleId id() const
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
    virtual void sim_handleParticleArrival(MovingParticle* arrivingParticle);

    /**
      * \brief      Called by the simulation engine when a particle leaves the module.
      * \warning    Must ONLY be called by simulation engine. Must NOT be overloaded.
      */
    virtual void sim_handleParticleDeparture(MovingParticle* departingParticle);

    /**
      * \brief      Called by the simulation engine when a timer of the module, fires.
      * \warning    Must ONLY be called by simulation engine. Must NOT be overloaded.
      */
    virtual void sim_handleTimerTriggering(ModuleTimer* triggeredTimer);

    /**
      * \brief      Called by the simulation engine when ..
      * \warning    Must ONLY be called by simulation engine. Must NOT be overloaded.
      */
    virtual void sim_setNeighbours(const std::set<ModuleId>& sources, const std::set<ModuleId>& dests);

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
    virtual ModuleId neighbourSourceOfParticlesId(unsigned index) const;
    /**
      * \brief  Returns the Id of a module that can receive particles from the current module.
      * \param  index   position of the neighbour module in the array of neighbour modules that can receive particles.
      */
    virtual ModuleId neighbourDestinationForParticlesId(unsigned index) const;

    // Added by Yacine Ould Rouis: Give the possibility to access directly the properties of neighbour modules.
    /**
      * \brief  Returns the pointer to a module that can emit particles to the current module.
      * \param  index   position of the neighbour module in the array of neighbour modules that can emit particles.
      */
    virtual SimulationModule* neighbourSourceOfParticlesPtr(unsigned index) const;
    /**
      * \brief  Returns the pointer to a module that can receive particles from the current module.
      * \param  index   position of the neighbour module in the array of neighbour modules that can receive particles.
      */
    virtual SimulationModule* neighbourDestinationForParticlesPtr(unsigned index) const;

    virtual const char* serialize() const;

protected:
    /**
      * \brief
      * \param  arrivingParticle
      */
    virtual void captureParticle(MovingParticle* arrivingParticle);

    /**
      * \brief
      * \param  departingParticle
      */
    virtual void releaseParticle(MovingParticle* departingParticle);

    /**
      * \brief
      */
    virtual void getReady();

    /**
      * \brief
      * \param  arrivingParticle
      */
    virtual void handleParticleArrival(MovingParticle* arrivingParticle);

    /**
      * \brief
      * \param  departingParticle
      */
    virtual void handleParticleDeparture(MovingParticle* departingParticle);

    /**
      * \brief
      */
    virtual void handleTimerTriggering(ModuleTimer* triggeredTimer);

    /**
      * \brief
      */
    virtual void terminate();

private:
    typedef std::vector<ModuleId> NeighboursVector;

    ModuleId m_moduleId;
    tMovingParticlesSet m_particlesInModule;
    tTimersSet m_timersInModule;

    NeighboursVector m_neighboursSourcesOfParticles;
    NeighboursVector m_neighboursDestinationForParticles;
};

/**
  * \brief  Comparison operator used for modules sorting
  */
bool operator<(SimulationModule const& mod1, SimulationModule const& mod2);

/**
  * \brief  Comparison operator used for modules sorting.
  */
struct SimulationModulePtrCmp {
    bool operator()(SimulationModule* const& mod1, SimulationModule* const& mod2) const;
};

#endif // SIMULATIONMODULE_H
