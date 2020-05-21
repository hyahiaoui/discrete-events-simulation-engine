#ifndef SIMULATIONEVENT_H
#define SIMULATIONEVENT_H

#include "BaseObject.h"
#include "SimulationTime.h"
#include "common.h"

/**
  * \brief
  */
class SimulationEvent : public BaseObject {
public:
    /**
      * \brief
      */
    SimulationEvent(const ModuleId& creatorId, const std::string& name = std::string());

    /**
      * \brief
      */
    SimulationEvent(const SimulationEvent& other);

    virtual ~SimulationEvent() noexcept(false);

    /**
      * \brief
      */
    virtual SimulationEvent& operator=(const SimulationEvent& other);

    /**
      * \brief
      */
    virtual bool operator==(const SimulationEvent& other);

    /**
      * \brief
      */
    virtual const SimulationTime& occurrenceTime() const;

    /**
      * \brief
      */
    virtual void setOccurenceTime(const SimulationTime& occurenceTime);

    /**
      * \brief
      */
    virtual void scheduleAt(const SimulationTime& occurenceTime);

    /**
      * \brief
      */
    virtual bool isScheduled() const;

    /**
      * \brief
      */
    virtual void cancelScheduling();

    virtual const SimulationTime& creationTime() const;

    virtual const ModuleId& creationModule() const;

    virtual const char* serialize() const;

protected:
private:
    SimulationTime m_occurrenceTime;
    bool m_scheduled;

    SimulationTime m_creationTime;
    ModuleId m_creationModule;
};

#endif // SIMULATIONEVENT_H
