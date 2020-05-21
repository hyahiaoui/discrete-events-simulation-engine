/**
 * \file    test_desimulator.h
 * \brief   Test unit for Discret Events simulator framework.
 * \date    June, 10th, 2011
 * \author  Yahiaoui H.
 * \version 1.0
 */

#ifndef TEST_DESIMULATOR_H
#define TEST_DESIMULATOR_H

#include "desimulator.h"
#include <iostream>

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
class MyGen : public cSimulationModule {
public:
    /**
      * \brief  Default constructor
      * \param  name    Generator's name
      */
    MyGen(const std::string& name = std::string())
        : cSimulationModule(Generator, name)
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
    virtual void handleParticleArrival(cMovingParticle* arrivingParticle) { }

    /**
      * \brief  Overloaded method for handeling particles departure from module (Does nothing)
      */
    virtual void handleParticleDeparture(cMovingParticle* arrivingParticle) { }

    /**
      * \brief  Overloaded method for handeling timers firing
      */
    virtual void handleTimerTriggering(cModuleTimer* triggeredTimer);

    /**
      * \brief  Overloaded termination method
      */
    virtual void terminate();

private:
    unsigned nbSentParticles;
    cSimulationTime m_sendingMeanInterval;
    cModuleTimer* m_sendingTimer;
};

////////////////////////////////////////////////////////////////////////////////////////////
/**
  * \brief  Module receving particles, putting them in a waiting queue, and treating them in FIFO order.
  */
class MyQueue : public cSimulationModule {
public:
    /**
      * \brief  Default constructor.
      * \param  name    Queue's name.
      */
    MyQueue(const std::string& name = std::string())
        : cSimulationModule(ServerAndQueue, name)
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
    virtual void handleParticleArrival(cMovingParticle* arrivingParticle);

    /**
      * \brief  Overloaded method for handeling particles departure from module (Does nothing)
      */
    virtual void handleParticleDeparture(cMovingParticle* arrivingParticle) { }

    /**
      * \brief  Overloaded method for handeling timers firing
      */
    virtual void handleTimerTriggering(cModuleTimer* triggeredTimer);

    /**
      * \brief  Overloaded termination method
      */
    virtual void terminate();

private:
    unsigned nbTreatedParticles;
    cSimulationTime m_servingMeanInterval;
    cModuleTimer* m_servingTimer;
    std::queue<cMovingParticle*> m_waitingParticles;
};

////////////////////////////////////////////////////////////////////////////////////////////
/**
  * \brief  Final destination of every particles generated in the test unit: a bottomless pit.
  */
class MySink : public cSimulationModule {
public:
    /**
      * \brief  Default constructor
      * \param  name    The sink's name.
      */
    MySink(const std::string& name = std::string())
        : cSimulationModule(Sink, name)
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
    virtual void handleParticleArrival(cMovingParticle* arrivingParticle);

    /**
      * \brief  Overloaded method for handeling particles departure from module (Does nothing)
      */
    virtual void handleParticleDeparture(cMovingParticle* arrivingParticle) { }

    /**
      * \brief  Overloaded method for handeling timers firing
      */
    virtual void handleTimerTriggering(cModuleTimer* triggeredTimer) { }

    /**
      * \brief  Overloaded termination method
      */
    virtual void terminate();

private:
    unsigned nbReceivedParticles;
};

////////////////////////////////////////////////////////////////////////////////////////////
/**
  * \brief  Test unit funtion: creates a simulation, creates and links simulation modules, then launches athe simulation before cleaning up the mess.
  */
void testSimulationEngine();

#endif // TEST_DESIMULATOR_H
