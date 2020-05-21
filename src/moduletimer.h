#ifndef MODULETIMER_H
#define MODULETIMER_H

#include "SimulationEvent.h"
#include "common.h"

#include <string>

class SimulationModule;

class ModuleTimer : public SimulationEvent {
public:
    ModuleTimer(const std::string name = std::string());
    ModuleTimer(const ModuleTimer& other);

    virtual ~ModuleTimer();

    virtual ModuleTimer& operator=(const ModuleTimer& other);

    // Getters
    virtual ModuleId ownerModuleId() const;
    virtual SimulationTime triggerTime() const;
    virtual void* attachedData() const;

    // Setters
    virtual void setOwnerModuleId(const ModuleId newOwner);
    virtual void setAttachedData(void* data);

    // Overloaded methods
    /**
      * \brief
      */
    virtual void scheduleAt(const SimulationTime& occurenceTime);

    /**
      * \brief
      */
    virtual void scheduleAt(const SimulationTime& occurenceTime, const ModuleId newOwnerModuleId);

    /**
      * \brief
      */
    virtual void scheduleAt(const SimulationTime& occurenceTime, const SimulationModule* newOwnerModule);

    /**
      * \brief
      * \warning    Must ONLY be called by simulation engine. Must NOT be overloaded.
      */
    virtual void sim_handleTriggering();

    virtual const char* serialize() const;

protected:
    /**
      * \brief  This method invoked by simulation engine, when the timer fires, in simulation based on particles behaviours.
      *
      * This should be overloaded to specify the timer actions when it fires.
      */
    virtual void handleTriggering();

private:
    ModuleId m_ownerModuleId;
    void* m_attachedData;
};

//std::ostream & operator<<(std::ostream & ost, const ModuleTimer & obj);

#endif // MODULETIMER_H
