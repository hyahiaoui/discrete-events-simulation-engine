#ifndef MODULETIMER_H
#define MODULETIMER_H

#include "common.h"
#include "simulationevent.h"
#include <string>

class cSimulationModule;

class cModuleTimer : public cSimulationEvent {
public:
    cModuleTimer(const std::string name = std::string());
    cModuleTimer(const cModuleTimer& other);

    virtual ~cModuleTimer();

    virtual cModuleTimer& operator=(const cModuleTimer& other);

    // Getters
    virtual tModuleId ownerModuleId() const;
    virtual cSimulationTime triggerTime() const;
    virtual void* attachedData() const;

    // Setters
    virtual void setOwnerModuleId(const tModuleId newOwner);
    virtual void setAttachedData(void* data);

    // Overloaded methods
    /**
      * \brief
      */
    virtual void scheduleAt(const cSimulationTime& occurenceTime);

    /**
      * \brief
      */
    virtual void scheduleAt(const cSimulationTime& occurenceTime, const tModuleId newOwnerModuleId);

    /**
      * \brief
      */
    virtual void scheduleAt(const cSimulationTime& occurenceTime, const cSimulationModule* newOwnerModule);

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
    tModuleId m_ownerModuleId;
    void* m_attachedData;
};

//std::ostream & operator<<(std::ostream & ost, const cModuleTimer & obj);

#endif // MODULETIMER_H
