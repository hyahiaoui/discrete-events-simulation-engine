#ifndef SIMULATIONEVENT_H
#define SIMULATIONEVENT_H

#include "baseobject.h"
#include "common.h"
#include "simulationtime.h"

/**
  * \brief
  */
class cSimulationEvent : public cBaseObject {
public:
    /**
      * \brief
      */
    cSimulationEvent(const tModuleId& creatorId, const std::string& name = std::string());

    /**
      * \brief
      */
    cSimulationEvent(const cSimulationEvent& other);

    virtual ~cSimulationEvent() noexcept(false);

    /**
      * \brief
      */
    virtual cSimulationEvent& operator=(const cSimulationEvent& other);

    /**
      * \brief
      */
    virtual bool operator==(const cSimulationEvent& other);

    /**
      * \brief
      */
    virtual const cSimulationTime& occurrenceTime() const;

    /**
      * \brief
      */
    virtual void setOccurenceTime(const cSimulationTime& occurenceTime);

    /**
      * \brief
      */
    virtual void scheduleAt(const cSimulationTime& occurenceTime);

    /**
      * \brief
      */
    virtual bool isScheduled() const;

    /**
      * \brief
      */
    virtual void cancelScheduling();

    virtual const cSimulationTime& creationTime() const;

    virtual const tModuleId& creationModule() const;

    virtual const char* serialize() const;

protected:
private:
    cSimulationTime m_occurrenceTime;
    bool m_scheduled;

    cSimulationTime m_creationTime;
    tModuleId m_creationModule;
};

#endif // SIMULATIONEVENT_H
