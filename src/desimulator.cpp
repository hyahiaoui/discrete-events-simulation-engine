#include "desimulator.h"
#include "common.h"
#include "moduletimer.h"
#include "movingparticle.h"

cDESimulator* cDESimulator::m_simulator = NULL;

cDESimulator::cDESimulator()
    : m_simulationPattern(BasedOnModulesBehaviours)
    , m_simulationCurrentTime()
    , m_simulationCurrentProcessedModule(invalidModuleId)
    , m_simulationEventsQueue()
    , m_simulationGraph(NULL)
    , m_currentSimulationStage(OutOfSimulationStage)
{
}

cDESimulator::~cDESimulator()
{
    cleanupSimulator();
}

cDESimulator* cDESimulator::theSimulator()
{
    if (m_simulator == NULL)
        m_simulator = new cDESimulator();

    return m_simulator;
}

cSimulationTime cDESimulator::simTime()
{
    return theSimulator()->m_simulationCurrentTime;
}

tModuleId cDESimulator::processedModule()
{
    return theSimulator()->m_simulationCurrentProcessedModule;
}

void cDESimulator::simulate(const cSimulationTime& maxSimTime, unsigned simulationsNumber)
{
    if (!m_simulationGraph)
        throw std::runtime_error("Launching simulation before assigning simulation graph.");

    m_simulationCurrentProcessedModule = invalidModuleId;
    m_currentSimulationStage = OutOfSimulationStage;
    for (unsigned i = 0; i < simulationsNumber; i++) {
        m_simulationCurrentTime = 0.;

        m_simulationCurrentProcessedModule = invalidModuleId;
        m_currentSimulationStage = InitializationStage;
        prepareSimulation(i);

        m_simulationCurrentProcessedModule = invalidModuleId;
        m_currentSimulationStage = EventsSimulationStage;
        makeSimulation(maxSimTime, i);

        m_simulationCurrentProcessedModule = invalidModuleId;
        m_currentSimulationStage = PostProcessingStage;
        postProcessSimulation(i);

        m_simulationCurrentProcessedModule = invalidModuleId;
        m_currentSimulationStage = OutOfSimulationStage;
    }
}

void cDESimulator::prepareSimulation(unsigned currentSimulationId)
{
    m_simulationCurrentProcessedModule = invalidModuleId;

    // Call initialization methods of all the modules of this simulation
    if (!m_simulationGraph) {
        std::ostringstream exceptionStream;
        exceptionStream << __PRETTY_FUNCTION__ << ": Launching simulation initialization process before assigning simulation graph.";
        throw std::runtime_error(exceptionStream.str());
    }

    if (m_currentSimulationStage != InitializationStage) {
        std::ostringstream exceptionStream;
        exceptionStream << __PRETTY_FUNCTION__ << ": Launching simulation initialization out of initialization stage.";
        throw std::runtime_error(exceptionStream.str());
    }

    for (tModuleId initializedModule : m_simulationGraph->vertices()) {
        m_simulationCurrentProcessedModule = m_simulationGraph->vertex(initializedModule)->id();
        m_simulationGraph->vertex(initializedModule)->sim_getReady();
    }
}

void cDESimulator::postProcessSimulation(unsigned currentSimulationId)
{
    // Call post-processing methods of all the modules of this simulation
    if (!m_simulationGraph) {
        std::ostringstream exceptionStream;
        exceptionStream << __PRETTY_FUNCTION__ << ": Launching simulation finalization process before assigning simulation graph.";
        throw std::runtime_error(exceptionStream.str());
    }

    if (m_currentSimulationStage != PostProcessingStage) {
        std::ostringstream exceptionStream;
        exceptionStream << __PRETTY_FUNCTION__ << ": Launching simulation finalization out of post-processing stage.";
        throw std::runtime_error(exceptionStream.str());
    }

    for (tModuleId module : m_simulationGraph->vertices()) {
        m_simulationCurrentProcessedModule = m_simulationGraph->vertex(module)->id();
        m_simulationGraph->vertex(module)->sim_terminate();
    }
}

void cDESimulator::makeSimulation(const cSimulationTime& maxSimTime, unsigned currentSimulationId)
{
    while (1) {
        if (m_simulationEventsQueue.empty())
            // No more events to simulate => simulation ends
            break;

        if ((maxSimTime != 0) && (m_simulationEventsQueue.top()->occurrenceTime() > maxSimTime))
            // The next coming event has an occurrence time greater than the limit => end simulation before processing it
            break;

        // 1 -  Get an event (with the smallest simulation time) from the simulation queue,
        //      and remove that event from the queue of future events
        cSimulationEvent* currentEvent = m_simulationEventsQueue.top();
        m_simulationEventsQueue.pop();

        // 2 -  Check simulator's sanity
        if (!currentEvent->isScheduled()) {
            std::ostringstream exceptionStream;
            exceptionStream << __PRETTY_FUNCTION__ << ": Retrieved an event from future events queue which was not scheduled.";
            throw std::runtime_error(exceptionStream.str());
        }
        currentEvent->cancelScheduling();

        if (m_simulationCurrentTime > currentEvent->occurrenceTime()) // Meaning this event should have been executed in the past
        {
            std::ostringstream exceptionStream;
            exceptionStream << __PRETTY_FUNCTION__ << ": Retrieved an event whose execution time has already passed.";
            throw std::runtime_error(exceptionStream.str());
        }

        // Ok, everything is fine ... we can proceed

        // 3 -  Make the time jump to this event execution time
        m_simulationCurrentTime = currentEvent->occurrenceTime();

        // 4 -  Check if this event is a timer ...
        cModuleTimer* currentTimer = dynamic_cast<cModuleTimer*>(currentEvent);
        if (currentTimer) {
            m_simulationCurrentProcessedModule = currentTimer->ownerModuleId();
            switch (m_simulationPattern) {
            case BasedOnModulesBehaviours:
                // call the module's right method with currentTimer as argument
                m_simulationGraph->vertex(currentTimer->ownerModuleId())->sim_handleTimerTriggering(currentTimer);
                break;
            case BasedOnParticlesBehaviours:
                currentTimer->sim_handleTriggering();
                break;
            default: {
                std::ostringstream exceptionStream;
                exceptionStream << __PRETTY_FUNCTION__ << ": Simulating with unknown simulation pattern (" << m_simulationPattern << ").";
                throw std::runtime_error(exceptionStream.str());
            } break;
            }

            m_simulationCurrentProcessedModule = invalidModuleId;
            continue;
        }

        // 5-   ... or a moving particle arriving at some module
        cMovingParticle* currentParticle = dynamic_cast<cMovingParticle*>(currentEvent);
        if (currentParticle) {
            m_simulationCurrentProcessedModule = currentParticle->nextModule();
            switch (m_simulationPattern) {
            case BasedOnModulesBehaviours:
                // call the module's right method with currentParticle as argument
                m_simulationGraph->vertex(currentParticle->nextModule())->sim_handleParticleArrival(currentParticle);
                break;
            case BasedOnParticlesBehaviours:
                currentParticle->sim_handleArrivalAtModule();
                break;
            default: {
                std::ostringstream exceptionStream;
                exceptionStream << __PRETTY_FUNCTION__ << ": Simulating with unknown simulation pattern (" << m_simulationPattern << ").";
                throw std::runtime_error(exceptionStream.str());
            } break;
            }

            m_simulationCurrentProcessedModule = invalidModuleId;
            continue;
        }

        // If it is neither a timer nor a particle, then it's an error!
        std::ostringstream exceptionStream;
        exceptionStream << __PRETTY_FUNCTION__ << ": Encountred unknown event type while simulating.";
        throw std::runtime_error(exceptionStream.str());
    }
}

cDESimulator::SimulationPattern cDESimulator::simulationPattern()
{
    return theSimulator()->m_simulationPattern;
}

void cDESimulator::setSimulationPattern(const cDESimulator::SimulationPattern newPattern)
{
    switch (newPattern) {
    case BasedOnModulesBehaviours:
    case BasedOnParticlesBehaviours:
        theSimulator()->m_simulationPattern = newPattern;
        break;
    default: {
        std::ostringstream exceptionStream;
        exceptionStream << __PRETTY_FUNCTION__ << ": Setting unknown simulation pattern (" << newPattern << ").";
        throw std::runtime_error(exceptionStream.str());
    } break;
    }
}

cDESimulator::SimulationStage cDESimulator::simulationStage()
{
    return theSimulator()->m_currentSimulationStage;
}

bool cDESimulator::isCurrentlySimulating()
{
    return (theSimulator()->m_currentSimulationStage != OutOfSimulationStage);
}

void cDESimulator::initiateSimulator(cDESimulator::SimulationGraph* const simulationGraph)
{
    cleanupSimulator();

    if (simulationGraph) {
        m_simulationGraph = simulationGraph;
        for (tModuleId moduleId : m_simulationGraph->vertices()) {
            m_simulationGraph->vertex(moduleId)->sim_setNeighbours(
                m_simulationGraph->predecessors(moduleId),
                m_simulationGraph->successors(moduleId));
        }
    }

    m_currentSimulationStage = OutOfSimulationStage;
    m_simulationCurrentTime = 0;
}

void cDESimulator::cleanupSimulator()
{
    if (isCurrentlySimulating()) {
        std::ostringstream exceptionStream;
        exceptionStream << __PRETTY_FUNCTION__ << ": Clean up simulation while still simulating.";
        throw std::runtime_error(exceptionStream.str());
    }

    while (!m_simulationEventsQueue.empty()) {
        cSimulationEvent* event = m_simulationEventsQueue.top();
        m_simulationEventsQueue.pop();
        delete event;
    }
    if (m_simulationGraph) {
        delete m_simulationGraph;
        m_simulationGraph = NULL;
    }
    m_simulationCurrentTime = 0;
}

void cDESimulator::scheduleFutureEvent(cSimulationEvent* futureEvent)
{
    if (!isCurrentlySimulating()) {
        std::ostringstream exceptionStream;
        exceptionStream << __PRETTY_FUNCTION__ << ": Insert future event in queue while simulation is deactivated.";
        throw std::runtime_error(exceptionStream.str());
    }

    m_simulationEventsQueue.push(futureEvent);
}

void cDESimulator::cancelFutureEvent(cSimulationEvent* futureEventToCancel)
{
    if (!isCurrentlySimulating()) {
        std::ostringstream exceptionStream;
        exceptionStream << __PRETTY_FUNCTION__ << ": Canceling future event from queue while simulation is deactivated.";
        throw std::runtime_error(exceptionStream.str());
    }

    if (!futureEventToCancel->isScheduled())
        return;

    cSimulationEvent* tmpEvent;
    cDESimulator::tSimulationEventQueue tmpQueue;
    while (1) {
        if (m_simulationEventsQueue.empty())
            break;

        tmpEvent = m_simulationEventsQueue.top();
        m_simulationEventsQueue.pop();

        if (tmpEvent == futureEventToCancel)
            break; // DO not insert in tmpQueue, and stop searching
        tmpQueue.push(tmpEvent);
    }

    while (!tmpQueue.empty()) {
        m_simulationEventsQueue.push(tmpQueue.top());
        tmpQueue.pop();
    }
}
