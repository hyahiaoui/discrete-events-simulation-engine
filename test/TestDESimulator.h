/**
 * \file    TestDESimulator.h
 * \brief   Test unit for Discret Events simulator framework.
 * \date    June, 10th, 2011
 * \author  Yahiaoui H.
 * \version 1.0
 */

#ifndef TEST_DESIMULATOR_H
#define TEST_DESIMULATOR_H

#include "SimulationModule.h"

#include <iostream>
#include <queue>

/**
  * \brief  Kinds of modules used in Discret Events simulator framework.
  */
enum MyModulesKinds {
    Generator,
    ServerAndQueue,
    Sink
};

////////////////////////////////////////////////////////////////////////////////////////////
/**
  * \brief  Generator of moving particles for the Test Unit.
  */
class MyGen : public SimulationModule {
public:
    /**
      * \brief  Default constructor
      * \param  name    Generator's name
      */
    MyGen(const std::string& name = std::string())
        : SimulationModule(Generator, name)
        , nbSentParticles(0)
        , m_sendingMeanInterval()
        , m_sendingTimer(NULL)
    {
    }

    /**
      * \brief  Destructor
      */
    virtual ~MyGen();

    virtual const char* serialize() const;

protected:
    /**
      * \brief  Overloaded initialization method
      */
    virtual void getReady();

    /**
      * \brief  Overloaded method for handeling particles arrival to module (Does nothing)
      */
    virtual void handleParticleArrival(MovingParticle* arrivingParticle) { }

    /**
      * \brief  Overloaded method for handeling particles departure from module (Does nothing)
      */
    virtual void handleParticleDeparture(MovingParticle* arrivingParticle) { }

    /**
      * \brief  Overloaded method for handeling timers firing
      */
    virtual void handleTimerTriggering(ModuleTimer* triggeredTimer);

    /**
      * \brief  Overloaded termination method
      */
    virtual void terminate();

private:
    unsigned nbSentParticles;
    SimulationTime m_sendingMeanInterval;
    ModuleTimer* m_sendingTimer;
};

////////////////////////////////////////////////////////////////////////////////////////////
/**
  * \brief  Module receving particles, putting them in a waiting queue, and treating them in FIFO order.
  */
class MyQueue : public SimulationModule {
public:
    /**
      * \brief  Default constructor.
      * \param  name    Queue's name.
      */
    MyQueue(const std::string& name = std::string())
        : SimulationModule(ServerAndQueue, name)
        , nbTreatedParticles(0)
        , m_servingMeanInterval()
        , m_servingTimer(NULL)
        , m_waitingParticles()
    {
    }

    /**
      * \brief  Destructor
      */
    virtual ~MyQueue();

protected:
    /**
      * \brief  Overloaded initialization method
      */
    virtual void getReady();

    /**
      * \brief  Overloaded method for handeling particles arrival to module (Does nothing)
      */
    virtual void handleParticleArrival(MovingParticle* arrivingParticle);

    /**
      * \brief  Overloaded method for handeling particles departure from module (Does nothing)
      */
    virtual void handleParticleDeparture(MovingParticle* arrivingParticle) { }

    /**
      * \brief  Overloaded method for handeling timers firing
      */
    virtual void handleTimerTriggering(ModuleTimer* triggeredTimer);

    /**
      * \brief  Overloaded termination method
      */
    virtual void terminate();

private:
    unsigned nbTreatedParticles;
    SimulationTime m_servingMeanInterval;
    ModuleTimer* m_servingTimer;
    std::queue<MovingParticle*> m_waitingParticles;
};

////////////////////////////////////////////////////////////////////////////////////////////
/**
  * \brief  Final destination of every particles generated in the test unit: a bottomless pit.
  */
class MySink : public SimulationModule {
public:
    /**
      * \brief  Default constructor
      * \param  name    The sink's name.
      */
    MySink(const std::string& name = std::string())
        : SimulationModule(Sink, name)
        , nbReceivedParticles(0)
    {
    }

protected:
    /**
      * \brief  Overloaded initialization method
      */
    virtual void getReady();

    /**
      * \brief  Overloaded method for handeling particles arrival to module (Does nothing)
      */
    virtual void handleParticleArrival(MovingParticle* arrivingParticle);

    /**
      * \brief  Overloaded method for handeling particles departure from module (Does nothing)
      */
    virtual void handleParticleDeparture(MovingParticle* arrivingParticle) { }

    /**
      * \brief  Overloaded method for handeling timers firing
      */
    virtual void handleTimerTriggering(ModuleTimer* triggeredTimer) { }

    /**
      * \brief  Overloaded termination method
      */
    virtual void terminate();

private:
    unsigned nbReceivedParticles;
};

#endif // TEST_DESIMULATOR_H
