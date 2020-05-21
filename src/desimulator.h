#ifndef DESIMULATOR_H
#define DESIMULATOR_H

#include "genericgraph.h"
#include "simulationevent.h"
#include "simulationmodule.h"
#include "simulationtime.h"

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
struct cSimulationEvent_Cmp {
    inline bool operator()(const cSimulationEvent* pr1, const cSimulationEvent* pr2) const
    {
        return pr1->occurrenceTime() > pr2->occurrenceTime();
    }
};

/**
  * \brief
  *
  *
  */
class cDESimulator {
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
    typedef std::priority_queue<cSimulationEvent*, std::deque<cSimulationEvent*>, cSimulationEvent_Cmp> tSimulationEventQueue;

    /**
      * \brief
      */
    typedef cGenericGraph<cSimulationModule*, int, true, cSimulationModulePtrCmp> SimulationGraph;

    /**
      *
      */
    static cDESimulator* theSimulator();

    /**
      *
      */
    static cSimulationTime simTime();

    /**
      *
      */
    static tModuleId processedModule();

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
    void simulate(const cSimulationTime& maxSimTime, unsigned simulationsNumber = 1);

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
    ~cDESimulator();

    /**
      * \brief
      **/
    void scheduleFutureEvent(cSimulationEvent* futureEvent);

    /**
      * \brief
      **/
    void cancelFutureEvent(cSimulationEvent* futureEventToCancel);

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
    void makeSimulation(const cSimulationTime& maxSimTime, unsigned currentSimulationId);

    /**
      * \brief
      * \param
      */
    void postProcessSimulation(unsigned currentSimulationId);

private:
    cDESimulator();

    static cDESimulator* m_simulator;

    //  Real simulator data
    SimulationPattern m_simulationPattern;
    cSimulationTime m_simulationCurrentTime;
    tModuleId m_simulationCurrentProcessedModule;
    tSimulationEventQueue m_simulationEventsQueue;
    SimulationGraph* m_simulationGraph;

    SimulationStage m_currentSimulationStage;
};

#endif // DESIMULATOR_H
