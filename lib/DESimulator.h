#ifndef DESIMULATOR_H
#define DESIMULATOR_H

#include "GenericGraph.h"
#include "SimulationEvent.h"
#include "SimulationModule.h"
#include "SimulationTime.h"

#include <queue>

/**
 *  \brief  Special struct housing the particles comparison operator
 *
 *  This struct houses an operator(), that compares two particles, and return true if the first particle has a next
 *  arrival time greater than the second particle.
 *  This operator is used in the simulator's  queue of  future events. Using this operator, the queue of particles is always
 *  sorted: the Particle with the smaller next arrival time is the first, ..., and the Particle with the greatest next arrival
 *  time is the last in the queue. Even when adding new Particles to the queue, this property is kept.
 */
struct SimulationEventCmp {
    inline bool operator()(const SimulationEvent* pr1, const SimulationEvent* pr2) const
    {
        return pr1->occurrenceTime() > pr2->occurrenceTime();
    }
};

/**
  * \brief
  *
  *
  */
class DESimulator {
public:
    /**
      * \brief
      */
    enum SimulationPattern {
        BasedOnModulesBehaviours,
        BasedOnParticlesBehaviours
    };

    /**
      * \brief
      */
    enum SimulationStage {
        OutOfSimulationStage,
        InitializationStage,
        EventsSimulationStage,
        PostProcessingStage
    };

    /**
     *  \brief  Queue of future events occurence in discrete events simulators.
     */
    typedef std::priority_queue<SimulationEvent*, std::deque<SimulationEvent*>, SimulationEventCmp> tSimulationEventQueue;

    /**
      * \brief
      */
    typedef GenericGraph<SimulationModule*, int, true, SimulationModulePtrCmp> SimulationGraph;

    /**
      *
      */
    static DESimulator* theSimulator();

    /**
      *
      */
    static SimulationTime simTime();

    /**
      *
      */
    static ModuleId processedModule();

    /**
      *
      */
    void initiateSimulator(SimulationGraph* const simulationGraph);

    /**
      *
      */
    void cleanupSimulator();

    /**
      * \param  maxSimTime  maximum simulation time for a single simulation (if equal to 0, then the simulations are done until no more events have to be simulated)
      */
    void simulate(const SimulationTime& maxSimTime, unsigned simulationsNumber = 1);

    /**
      * \brief
      */
    static SimulationPattern simulationPattern();

    /**
      * \brief
      */
    static void setSimulationPattern(const SimulationPattern newPattern);

    /**
      *
      */
    static SimulationStage simulationStage();

    /**
      *
      */
    static bool isCurrentlySimulating();

    /**
      *
      */
    ~DESimulator();

    /**
      * \brief
      **/
    void scheduleFutureEvent(SimulationEvent* futureEvent);

    /**
      * \brief
      **/
    void cancelFutureEvent(SimulationEvent* futureEventToCancel);

    const SimulationGraph* getSimulationGraph() const
    {
        return m_simulationGraph;
    }

protected:
    /**
      * \brief
      * \param
      */
    void prepareSimulation(unsigned currentSimulationId);

    /**
      * \brief
      * \param  maxSimTime  maximum simulation time for a single simulation (if equal to 0, then the simulations are done until no more events have to be simulated)
      */
    void makeSimulation(const SimulationTime& maxSimTime, unsigned currentSimulationId);

    /**
      * \brief
      * \param
      */
    void postProcessSimulation(unsigned currentSimulationId);

private:
    DESimulator();

    static DESimulator* m_simulator;

    //  Real simulator data
    SimulationPattern m_simulationPattern;
    SimulationTime m_simulationCurrentTime;
    ModuleId m_simulationCurrentProcessedModule;
    tSimulationEventQueue m_simulationEventsQueue;
    SimulationGraph* m_simulationGraph;

    SimulationStage m_currentSimulationStage;
};

#endif // DESIMULATOR_H
