#include "TestDESimulator.h"

#include "DESimulator.h"
#include "ModuleTimer.h"
#include "MovingParticle.h"
#include "Random.h"

#include "catch2/catch.hpp"

#include <iostream>

TEST_CASE("A Discrete Event Simulation can be defined and run", "[DESimulator]")
{
    DESimulator::SimulationGraph mySimGraph;

    //*
    std::cout << "-----------------------------------------------------" << std::endl
              << "---------------------  Network 1 --------------------" << std::endl
              << "-----------------------------------------------------" << std::endl;
    MyGen* g = new MyGen("The Greater Generator");
    mySimGraph.add(g, g->id());
    MySink* s = new MySink("The Greater Sinkator");
    mySimGraph.add(s, s->id());
    MyQueue* q = new MyQueue("The Greater Server");
    mySimGraph.add(q, q->id());

    // Generator to Queue, and ...
    mySimGraph.add(g, q);
    // ... Queue to Sink
    mySimGraph.add(q, s);

    std::cout << "==============================================" << std::endl
              << "Initializing simulator." << std::endl;
    DESimulator::theSimulator()->initiateSimulator(&mySimGraph);

    std::cout << "==============================================" << std::endl
              << "Setting simulator Pattern." << std::endl;
    DESimulator::theSimulator()->setSimulationPattern(DESimulator::BasedOnModulesBehaviours);

    std::cout << "==============================================" << std::endl
              << "Simulating." << std::endl;
    DESimulator::theSimulator()->simulate(200);

    std::cout << "==============================================" << std::endl
              << "Cleaning up." << std::endl;
    DESimulator::theSimulator()->cleanupSimulator();

    mySimGraph.remove(g);
    delete g;
    mySimGraph.remove(s);
    delete s;
    mySimGraph.remove(q);
    delete q;

    getchar();
    //*/

    std::cout << "-----------------------------------------------------" << std::endl
              << "---------------------  Network 2 --------------------" << std::endl
              << "-----------------------------------------------------" << std::endl;
    MyGen *g1, *g2;
    g1 = new MyGen("Gen1");
    g2 = new MyGen("Gen2");
    mySimGraph.add(g1, g1->id());
    mySimGraph.add(g2, g2->id());

    MyQueue *q1, *q2, *q3, *q4;
    q1 = new MyQueue("Queue1");
    q2 = new MyQueue("Queue2");
    q3 = new MyQueue("Queue3");
    q4 = new MyQueue("Queue4");
    mySimGraph.add(q1, q1->id());
    mySimGraph.add(q2, q2->id());
    mySimGraph.add(q3, q3->id());
    mySimGraph.add(q4, q4->id());

    MySink *s1, *s2;
    s1 = new MySink("Sink1");
    s2 = new MySink("Sink2");
    mySimGraph.add(s1, s1->id());
    mySimGraph.add(s2, s2->id());

    mySimGraph.add(g1, q1);
    mySimGraph.add(g2, q2);
    mySimGraph.add(q1, q3);
    mySimGraph.add(q1, q4);
    mySimGraph.add(q2, q3);
    mySimGraph.add(q2, q4);
    mySimGraph.add(q3, s1);
    mySimGraph.add(q4, s2);

    mySimGraph.save("network2.xml");

    std::cout << "==============================================" << std::endl
              << "Initializing simulator." << std::endl;
    DESimulator::theSimulator()->initiateSimulator(&mySimGraph);

    std::cout << "==============================================" << std::endl
              << "Setting simulator Pattern." << std::endl;
    DESimulator::theSimulator()->setSimulationPattern(DESimulator::BasedOnModulesBehaviours);

    std::cout << "==============================================" << std::endl
              << "Simulating." << std::endl;
    DESimulator::theSimulator()->simulate(200);

    std::cout << "==============================================" << std::endl
              << "Cleaning up." << std::endl;
    DESimulator::theSimulator()->cleanupSimulator();

    mySimGraph.remove(g1);
    delete g1;
    mySimGraph.remove(s1);
    delete s1;
    mySimGraph.remove(q1);
    delete q1;
    mySimGraph.remove(g2);
    delete g2;
    mySimGraph.remove(s2);
    delete s2;
    mySimGraph.remove(q2);
    delete q2;
    mySimGraph.remove(q3);
    delete q3;
    mySimGraph.remove(q4);
    delete q4;

    getchar();
}

////////////////////////////////////////////////////////////////////////////////////////
void MySink::getReady()
{
    nbReceivedParticles = 0;
}

void MySink::handleParticleArrival(MovingParticle* arrivingParticle)
{
    std::cout << DESimulator::simTime() << ": " << *this << " RECEIVED " << *arrivingParticle << std::endl
              << std::endl;

    ++nbReceivedParticles;
    releaseParticle(arrivingParticle);
    delete arrivingParticle;
}

void MySink::terminate()
{
    std::cout << "Sink[" << name() << "] received " << nbReceivedParticles << " particles." << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////
void MyGen::getReady()
{
    nbSentParticles = 0;
    m_sendingMeanInterval = 8.1;
    m_sendingTimer = new ModuleTimer(std::string("GenTimer_") + std::to_string(id()));
    m_sendingTimer->scheduleAt(
        DESimulator::simTime() + Random::Generate()->exponential(1 / m_sendingMeanInterval.toDbl()));
}

void MyGen::handleTimerTriggering(ModuleTimer* triggeredTimer)
{
    if (triggeredTimer != m_sendingTimer) {
        std::ostringstream exceptionStream;
        exceptionStream << __PRETTY_FUNCTION__ << ": Module " << *this << " was asked to handle unknown timer " << *triggeredTimer;
        throw std::runtime_error(exceptionStream.str());
    }

    MovingParticle* newParticle = new MovingParticle(nbSentParticles);
    std::cout << DESimulator::simTime() << ": " << *this << " IS SENDING " << *newParticle << std::endl
              << std::endl;
    newParticle->send(neighbourDestinationForParticlesId(0), DESimulator::simTime()); // Make it arrive NOW!
    ++nbSentParticles;
    m_sendingTimer->scheduleAt(
        DESimulator::simTime() + Random::Generate()->exponential(1 / m_sendingMeanInterval.toDbl()));
}

void MyGen::terminate()
{
    m_sendingTimer->cancelScheduling();
    std::cout << "Generator[" << name() << "] has sent " << nbSentParticles << " particles." << std::endl;
}

MyGen::~MyGen()
{
    delete m_sendingTimer;
}

const char* MyGen::serialize() const
{
    std::ostringstream outStream;
    outStream << "MyGen["
              << "id=" << id() << ", "
              << "name=\"" << name() << "\", "
              << "kind=" << kind() << ", ";
    outStream << "in=(";
    for (unsigned i = 0; neighbourSourceOfParticlesId(i) != invalidModuleId; ++i)
        outStream << (i == 0 ? "" : " ") << neighbourSourceOfParticlesId(i);
    outStream << "), "
              << "out=(";
    for (unsigned i = 0; neighbourDestinationForParticlesId(i) != invalidModuleId; ++i)
        outStream << (i == 0 ? "" : " ") << neighbourDestinationForParticlesId(i) << " ";
    outStream << "), ";
    outStream << "sentParticles=" << nbSentParticles << ", "
              << "sendMeanTime=" << m_sendingMeanInterval << ","
              << "sendTimer='" << *m_sendingTimer << "' ";
    outStream << "]";
    return outStream.str().c_str();
}

////////////////////////////////////////////////////////////////////////////////////////
void MyQueue::getReady()
{
    nbTreatedParticles = 0;
    m_servingMeanInterval = 8;
    m_servingTimer = new ModuleTimer("Serving Timer");
}

void MyQueue::handleParticleArrival(MovingParticle* arrivingParticle)
{
    std::cout << DESimulator::simTime() << ": " << *this << " RECEIVED " << *arrivingParticle << std::endl
              << std::endl;

    m_waitingParticles.push(arrivingParticle);
    if (!m_servingTimer->isScheduled())
        m_servingTimer->scheduleAt(
            DESimulator::simTime() + Random::Generate()->exponential(1 / m_servingMeanInterval.toDbl()));
}

void MyQueue::handleTimerTriggering(ModuleTimer* triggeredTimer)
{
    if (triggeredTimer != m_servingTimer) {
        std::ostringstream exceptionStream;
        exceptionStream << __PRETTY_FUNCTION__ << ": Module " << *this << " was asked to handle unknown timer " << *triggeredTimer;
        throw std::runtime_error(exceptionStream.str());
    }

    // Get a particle from the queue
    MovingParticle* particleToSend = m_waitingParticles.front();
    m_waitingParticles.pop();

    // Send it to the sink
    std::cout << DESimulator::simTime() << ": " << *this << " SERVED AND IS SENDING " << *particleToSend << std::endl
              << std::endl;
    releaseParticle(particleToSend);

    // This module can have several outputs, choose randomly one of them to send the particle
    unsigned choosenDestIndex = Random::Generate()->intuniform(0, neighbourDestinationForParticlesNb() - 1);
    std::cout << "Choosen index == " << choosenDestIndex << std::endl;
    particleToSend->send(neighbourDestinationForParticlesId(choosenDestIndex), DESimulator::simTime());

    nbTreatedParticles++;

    // If there are still particles to serve, re-schedule the timer
    if (!m_waitingParticles.empty())
        m_servingTimer->scheduleAt(
            DESimulator::simTime() + Random::Generate()->exponential(1 / m_servingMeanInterval.toDbl()));
}

void MyQueue::terminate()
{
    m_servingTimer->cancelScheduling();
    std::cout << "Queue[" << name() << "] has received and re-sent " << nbTreatedParticles << " particles." << std::endl;
    std::cout << "Queue[" << name() << "] is still containing " << m_waitingParticles.size() << " particles." << std::endl;
}

MyQueue::~MyQueue()
{
    delete m_servingTimer;
}
