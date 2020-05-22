#include "SimulationModule.h"
#include "DESimulator.h"

SimulationModule::SimulationModule(int moduleKind, const std::string& name)
    : BaseObject(name)
{
    m_moduleId = UniqueIDGenerator<ModuleId>::Generator()->newId();
    setKind(moduleKind);
}

SimulationModule::~SimulationModule()
{
    m_particlesInModule.clear();
    m_timersInModule.clear();
}

void SimulationModule::sim_handleParticleArrival(MovingParticle* arrivingParticle)
{
    if (DESimulator::simulationPattern() == DESimulator::BasedOnParticlesBehaviours)
        throw std::runtime_error("Invoking particle arrival handler at module while doing particles behaviours based simulation.");

    captureParticle(arrivingParticle);
    handleParticleArrival(arrivingParticle);
}

void SimulationModule::sim_handleParticleDeparture(MovingParticle* departingParticle)
{
    if (DESimulator::simulationPattern() == DESimulator::BasedOnParticlesBehaviours)
        throw std::runtime_error("Invoking particle departure handler at module while doing particles behaviours based simulation.");

    releaseParticle(departingParticle);
    handleParticleDeparture(departingParticle);
}

void SimulationModule::sim_handleTimerTriggering(ModuleTimer* triggeredTimer)
{
    if (DESimulator::simulationPattern() == DESimulator::BasedOnParticlesBehaviours)
        throw std::runtime_error("Invoking timer triggering handler at module while doing particles behaviours based simulation.");

    handleTimerTriggering(triggeredTimer);
}

void SimulationModule::captureParticle(MovingParticle* arrivingParticle)
{
    m_particlesInModule.insert(arrivingParticle);
}

void SimulationModule::releaseParticle(MovingParticle* departingParticle)
{
    m_particlesInModule.erase(departingParticle);
}

void SimulationModule::handleParticleArrival(MovingParticle* arrivingParticle)
{
    throw std::runtime_error(std::string(__FUNCTION__) + std::string(": this method must only be called for objects of subclasses of SimulationModule."));
}

void SimulationModule::handleParticleDeparture(MovingParticle* arrivingParticle)
{
    throw std::runtime_error(std::string(__FUNCTION__) + std::string(": this method must only be called for objects of subclasses of SimulationModule."));
}

void SimulationModule::handleTimerTriggering(ModuleTimer* triggeredTimer)
{
    // Empty method: Do nothing
}

void SimulationModule::sim_getReady()
{
    if (DESimulator::simulationStage() != DESimulator::InitializationStage)
        throw std::runtime_error("Invoking module initialization method out of simulator initialization stage.");

    getReady();
}

void SimulationModule::getReady()
{
    // Empty Method
}

void SimulationModule::sim_terminate()
{
    if (DESimulator::simulationStage() != DESimulator::PostProcessingStage)
        throw std::runtime_error("Invoking module finalization method out of simulator finalization stage.");

    terminate();
}

void SimulationModule::terminate()
{
    // Empty Method
}

bool operator<(SimulationModule const& mod1, SimulationModule const& mod2)
{
    return mod1.id() < mod2.id();
}

bool SimulationModulePtrCmp::operator()(SimulationModule* const& mod1, SimulationModule* const& mod2) const
{
    if ((!mod1) || (!mod2))
        throw std::runtime_error(__PRETTY_FUNCTION__ + std::string(": Comparing NULL pointer referenced SimulationModule."));

    return mod1->id() < mod2->id();
}

void SimulationModule::sim_setNeighbours(const std::set<ModuleId>& sources, const std::set<ModuleId>& dests)
{
    int index;

    m_neighboursSourcesOfParticles.resize(sources.size());
    index = 0;
    for (std::set<ModuleId>::const_iterator it = sources.begin(); it != sources.end(); it++)
        m_neighboursSourcesOfParticles.at(index++) = *it;

    m_neighboursDestinationForParticles.resize(dests.size());
    index = 0;
    for (std::set<ModuleId>::const_iterator it = dests.begin(); it != dests.end(); it++)
        m_neighboursDestinationForParticles.at(index++) = *it;
}

ModuleId SimulationModule::neighbourSourceOfParticlesId(unsigned index) const
{
    if (index >= m_neighboursSourcesOfParticles.size())
        return invalidModuleId;
    return m_neighboursSourcesOfParticles.at(index);
}

unsigned SimulationModule::neighbourSourceOfParticlesNb() const
{
    return m_neighboursSourcesOfParticles.size();
}

ModuleId SimulationModule::neighbourDestinationForParticlesId(unsigned index) const
{
    if (index >= m_neighboursDestinationForParticles.size())
        return invalidModuleId;
    return m_neighboursDestinationForParticles.at(index);
}

unsigned SimulationModule::neighbourDestinationForParticlesNb() const
{
    return m_neighboursDestinationForParticles.size();
}

const char* SimulationModule::serialize() const
{
    std::ostringstream outStream;
    outStream << "SimulationModule["
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

SimulationModule* SimulationModule::neighbourSourceOfParticlesPtr(unsigned index) const
{
    if (index >= m_neighboursSourcesOfParticles.size())
        return NULL;
    return DESimulator::theSimulator()->getSimulationGraph()->vertex(m_neighboursSourcesOfParticles.at(index));
}

SimulationModule* SimulationModule::neighbourDestinationForParticlesPtr(unsigned index) const
{
    if (index >= m_neighboursDestinationForParticles.size())
        return NULL;
    return DESimulator::theSimulator()->getSimulationGraph()->vertex(m_neighboursDestinationForParticles.at(index));
}
