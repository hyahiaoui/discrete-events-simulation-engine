#include "simulationmodule.h"
#include "desimulator.h"

cSimulationModule::cSimulationModule(int moduleKind, const std::string& name)
    : cBaseObject(name)
{
    m_moduleId = cUniqueIDGenerator<tModuleId>::Generator()->newId();
    setKind(moduleKind);
}

cSimulationModule::~cSimulationModule()
{
    m_particlesInModule.clear();
    m_timersInModule.clear();
}

void cSimulationModule::sim_handleParticleArrival(cMovingParticle* arrivingParticle)
{
    if (cDESimulator::simulationPattern() == cDESimulator::BasedOnParticlesBehaviours)
        throw std::runtime_error("Invoking particle arrival handler at module while doing particles behaviours based simulation.");

    captureParticle(arrivingParticle);
    handleParticleArrival(arrivingParticle);
}

void cSimulationModule::sim_handleParticleDeparture(cMovingParticle* departingParticle)
{
    if (cDESimulator::simulationPattern() == cDESimulator::BasedOnParticlesBehaviours)
        throw std::runtime_error("Invoking particle departure handler at module while doing particles behaviours based simulation.");

    releaseParticle(departingParticle);
    handleParticleDeparture(departingParticle);
}

void cSimulationModule::sim_handleTimerTriggering(cModuleTimer* triggeredTimer)
{
    if (cDESimulator::simulationPattern() == cDESimulator::BasedOnParticlesBehaviours)
        throw std::runtime_error("Invoking timer triggering handler at module while doing particles behaviours based simulation.");

    handleTimerTriggering(triggeredTimer);
}

void cSimulationModule::captureParticle(cMovingParticle* arrivingParticle)
{
    m_particlesInModule.insert(arrivingParticle);
}

void cSimulationModule::releaseParticle(cMovingParticle* departingParticle)
{
    m_particlesInModule.erase(departingParticle);
}

void cSimulationModule::handleParticleArrival(cMovingParticle* arrivingParticle)
{
    throw std::runtime_error(std::string(__FUNCTION__) + std::string(": this method must only be called for objects of subclasses of cSimulationModule."));
}

void cSimulationModule::handleParticleDeparture(cMovingParticle* arrivingParticle)
{
    throw std::runtime_error(std::string(__FUNCTION__) + std::string(": this method must only be called for objects of subclasses of cSimulationModule."));
}

void cSimulationModule::handleTimerTriggering(cModuleTimer* triggeredTimer)
{
    // Empty method: Do nothing
}

void cSimulationModule::sim_getReady()
{
    if (cDESimulator::simulationStage() != cDESimulator::InitializationStage)
        throw std::runtime_error("Invoking module initialization method out of simulator initialization stage.");

    getReady();
}

void cSimulationModule::getReady()
{
    // Empty Method
}

void cSimulationModule::sim_terminate()
{
    if (cDESimulator::simulationStage() != cDESimulator::PostProcessingStage)
        throw std::runtime_error("Invoking module finalization method out of simulator finalization stage.");

    terminate();
}

void cSimulationModule::terminate()
{
    // Empty Method
}

bool operator<(cSimulationModule const& mod1, cSimulationModule const& mod2)
{
    return mod1.id() < mod2.id();
}

bool cSimulationModulePtrCmp::operator()(cSimulationModule* const& mod1, cSimulationModule* const& mod2) const
{
    if ((!mod1) || (!mod2))
        throw std::runtime_error(__PRETTY_FUNCTION__ + std::string(": Comparing NULL pointer referenced cSimulationModule."));

    return mod1->id() < mod2->id();
}

void cSimulationModule::sim_setNeighbours(const std::set<tModuleId>& sources, const std::set<tModuleId>& dests)
{
    int index;

    m_neighboursSourcesOfParticles.resize(sources.size());
    index = 0;
    for (std::set<tModuleId>::const_iterator it = sources.begin(); it != sources.end(); it++)
        m_neighboursSourcesOfParticles.at(index++) = *it;

    m_neighboursDestinationForParticles.resize(dests.size());
    index = 0;
    for (std::set<tModuleId>::const_iterator it = dests.begin(); it != dests.end(); it++)
        m_neighboursDestinationForParticles.at(index++) = *it;
}

tModuleId cSimulationModule::neighbourSourceOfParticlesId(unsigned index) const
{
    if (index >= m_neighboursSourcesOfParticles.size())
        return invalidModuleId;
    return m_neighboursSourcesOfParticles.at(index);
}

unsigned cSimulationModule::neighbourSourceOfParticlesNb() const
{
    return m_neighboursSourcesOfParticles.size();
}

tModuleId cSimulationModule::neighbourDestinationForParticlesId(unsigned index) const
{
    if (index >= m_neighboursDestinationForParticles.size())
        return invalidModuleId;
    return m_neighboursDestinationForParticles.at(index);
}

unsigned cSimulationModule::neighbourDestinationForParticlesNb() const
{
    return m_neighboursDestinationForParticles.size();
}

const char* cSimulationModule::serialize() const
{
    std::ostringstream outStream;
    outStream << "cSimulationModule["
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
    outStream << ")"
              << "]";
    return outStream.str().c_str();
}

cSimulationModule* cSimulationModule::neighbourSourceOfParticlesPtr(unsigned index) const
{
    if (index >= m_neighboursSourcesOfParticles.size())
        return NULL;
    return cDESimulator::theSimulator()->getSimulationGraph()->vertex(m_neighboursSourcesOfParticles.at(index));
}

cSimulationModule* cSimulationModule::neighbourDestinationForParticlesPtr(unsigned index) const
{
    if (index >= m_neighboursDestinationForParticles.size())
        return NULL;
    return cDESimulator::theSimulator()->getSimulationGraph()->vertex(m_neighboursDestinationForParticles.at(index));
}
