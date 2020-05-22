#include "BaseObject.h"
#include "GenericGraph.h"
#include "Random.h"
#include "RandomVariable.h"
#include "SimulationTime.h"
#include "TestDESimulator.h"
#include "UniqueIDGenerator.h"
#include "common.h"

#include <climits>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <sstream>
#include <vector>

#define MYMAX 60
//#define DEBUG
//#define CHECK_BEFORE_INSERTION

void testSimulationTime()
{
    std::stringstream timeAsStr;
    SimulationTime st, oldst;

    std::cout.precision(24);
    for (int i = 0; i < 10; i++) {
        timeAsStr.str("");
        timeAsStr << (rand() % 2 == 0 ? "+" : "-")
                  << rand() % MYMAX << "h"
                  << rand() % MYMAX << "d"
                  << rand() % MYMAX << "m"
                  << rand() % MYMAX << "";

        std::cout << "=============================" << std::endl;
        std::cout << "Before conversion time = " << timeAsStr.str().c_str() << std::endl;
        try {
            oldst = st;
            st.fromStr(timeAsStr.str().c_str());
        } catch (char* strexcept) {
            std::cerr << "Launched exception '" << strexcept << "'. Stopping." << std::endl;
            return;
        }

        std::cout << "After conversion time = " << st << std::endl;
        std::cout << "'" << st << "' + '" << oldst << "' = '" << st + oldst << "'." << std::endl;
    }

    SimulationTime testtime;
    testtime.fromStr("6h6m6s");
    std::cout << "============================" << std::endl;
    std::cout << "time is " << testtime << std::endl
              << ", 1.5*time = " << testtime * 1.5 << std::endl
              << ", 2*time = " << testtime * 2 << std::endl
              << ", 0.1*time = " << testtime * 0.1 << std::endl
              << ", 10.5*time = " << testtime * 10.5 << std::endl
              << ", 1000*time = " << testtime * 1000 << std::endl;
}

void testBaseObject()
{
    BaseObject ob1, ob2("hi"), ob3("himynameiswalter");

    std::cout << "First object is '" << ob1.name() << "'." << std::endl;
    std::cout << "Second object is '" << ob2.name() << "'." << std::endl;
    std::cout << "Third object is '" << ob3.name() << "'." << std::endl;

    ob1 = ob2;
    std::cout << "First object is '" << ob1.name() << "'." << std::endl;
    std::cout << "First Object is " << (ob1 == ob3 ? "equal to" : "different from") << " Third Object." << std::endl;

    ob1.setName("");
    std::cout << "First object is '" << ob1.name() << "'." << std::endl;
    std::cout << "First Object is " << (ob1 == ob3 ? "equal to" : "different from") << " Third Object." << std::endl;

    ob1.setName(ob3.name());
    std::cout << "First object is '" << ob1.name() << "'." << std::endl;
    std::cout << "First Object is " << (ob1 == ob3 ? "equal to" : "different from") << " Third Object." << std::endl;
}

void testRandom()
{
    const int n = 10;
    long long tab[n];
    for (int i = 0; i < n; i++)
        tab[i] = 0;

    for (long long i = 0; i < 1000000; i++) {
        long double l = 10 * Random::Generate()->uniform(0, 1);
        if ((l < 0) || (l >= 10)) {
            std::cout << "l=" << l << std::endl;
            continue;
        }
        tab[(int)(l)]++;
    }

    unsigned long long sum = 0;
    for (int i = 0; i < n; i++) {
        std::cout << i << " : " << tab[i] << std::endl;
        sum += tab[i];
    }
    std::cout << "sum= " << sum << std::endl;
}

void testDistributionRandom()
{
    unsigned long nb1 = 0, nb0 = 0;
    for (long long i = 0; i < 10000000; i++) {
        if (Random::Generate()->bernoulli(0.66666666) == 0)
            ++nb0;
        else
            ++nb1;
    }
    std::cout << "Number of 0 = " << nb0 << std::endl;
    std::cout << "Number of 1 = " << nb1 << std::endl;
}

void testIDGenerator()
{
    for (long i = 0; i < 1000; i++)
        std::cout << i << " : "
                  << " module= " << UniqueIDGenerator<ModuleId>::Generator()->newId()
                  << " client= " << UniqueIDGenerator<ParticleId>::Generator()->newId()
                  << std::endl;
}

struct Node {
    char name[10];
    int otherProp;
};
bool operator<(const Node& node1, const Node& node2)
{
    if (node1.otherProp < node2.otherProp)
        return true;
    if (node1.otherProp > node2.otherProp)
        return false;
    return (strcmp(node1.name, node2.name) < 0);
}

std::ostream& operator<<(std::ostream& ost, const Node& node)
{
    ost << "['" << node.name << "', " << node.otherProp << "]";
    return ost;
}

struct Edge {
    int cost;
};

void testGenericGraph(const unsigned nbNodes, const unsigned meanArcsPerNode, bool writeToXML = false)
{
    GenericGraph<Node, Edge> myGraph;
    struct std::vector<Node> vectNode(nbNodes);
    int nbArcsInserted = 0;

    //  Testing vertices adding
    time_t t = time(NULL);
    for (unsigned i = 0; i < nbNodes; i++) {
        vectNode[i].name[0] = Random::Generate()->bernoulli(0.5) == 0 ? 'H' : 'h';
        vectNode[i].name[1] = Random::Generate()->bernoulli(0.5) == 0 ? 'I' : 'i';
        vectNode[i].name[2] = '\0';

        vectNode[i].otherProp = Random::Generate()->intuniform(1, vectNode.size());

#ifdef CHECK_BEFORE_INSERTION
        std::cout << "Attempt to insert " << vectNode[i] << ": ";
        if (myGraph.exists(vectNode[i])) {
            ++nbNodesAlreadyInserted;
            std::cout << "Already existing" << std::endl;
        } else {
            myGraph.add(vectNode[i]);
            std::cout << "Insertion success." << std::endl;
        }
#else
        myGraph.add(vectNode[i]);
#endif
    }
    std::cout << "Resume: Inserted " << myGraph.verticesNb() << " vertices in " << time(NULL) - t << " seconds" << std::endl;
#ifdef CHECK_BEFORE_INSERTION
    std::cout << "\t" << nbNodesAlreadyInserted << " nodes insertion conflicts " << std::endl
              << std::endl;
#endif

    //  Testing arcs adding
    double prob = (double)(meanArcsPerNode) / (double)(vectNode.size());
    GenericGraph<Node, Edge>::VertexIDSet nodesSet = myGraph.vertices();
    unsigned long long i = 0;
    t = time(NULL);
    for (GenericGraph<Node, Edge>::VertexIDSet::const_iterator it = nodesSet.begin();
         it != nodesSet.end(); it++) {
        for (GenericGraph<Node, Edge>::VertexIDSet::const_iterator itsec = nodesSet.begin();
             itsec != nodesSet.end(); itsec++) {
            ++i;
            if (i % (nbNodes * nbNodes / 100) == 0) {
                std::cout << ".";
                std::cout.flush();
            }

            if (*it == *itsec)
                continue;

            if (Random::Generate()->bernoulli(prob) == 1) {
#ifdef CHECK_BEFORE_INSERTION
                std::cout << "Attempt to insert " << myGraph.vertex(*it) << "-->" << myGraph.vertex(*itsec) << ": ";
                if (myGraph.exists(*it, *itsec)) {
                    ++nbArcAlreadyInserted;
                    std::cout << "Already existing" << std::endl;
                } else {
                    myGraph.add(*it, *itsec);
                    std::cout << "Insertion success." << std::endl;
                }
#else
                myGraph.add(*it, *itsec);
                ++nbArcsInserted;
#endif
            }
        }
    }
    std::cout << std::endl
              << "Resume: Inserted " << myGraph.arcsNb() << "(=" << nbArcsInserted << ") arcs in " << time(NULL) - t << " seconds." << std::endl;
#ifdef CHECK_BEFORE_INSERTION
    std::cout << "\t" << nbArcAlreadyInserted << " arcs insertion conflicts " << std::endl
              << std::endl;
#endif

#ifdef DEBUG
    for (GenericGraph<Node, Edge>::VertexIDSet::const_iterator it = nodesSet.begin();
         it != nodesSet.end(); it++) {
        std::cout << myGraph.vertex(*it) << " has " << myGraph.successorsNb(*it) << " successors and " << myGraph.predecessorsNb(*it) << " predecessors" << std::endl;

        GenericGraph<Node, Edge>::VertexIDSet set = myGraph.successors(*it);
        std::cout << "Successors of " << myGraph.vertex(*it) << " are : ";
        for (GenericGraph<Node, Edge>::VertexIDSet::iterator itsucc = set.begin(); itsucc != set.end(); itsucc++)
            std::cout << myGraph.vertex(*itsucc) << " ";
        std::cout << std::endl;

        set = myGraph.predecessors(*it);
        std::cout << "Predecessors of " << myGraph.vertex(*it) << " are : ";
        for (GenericGraph<Node, Edge>::VertexIDSet::iterator itpred = set.begin(); itpred != set.end(); itpred++)
            std::cout << myGraph.vertex(*itpred) << " ";
        std::cout << std::endl;
    }
#endif
    std::cout << "The graph contains " << myGraph.verticesNb() << " vertices, and " << myGraph.arcsNb() << " arcs." << std::endl;

    if (writeToXML) {
        char file[] = "Original.graphml";
        std::cout << "Writing Graph to file " << file << ": ..." << std::endl;
        myGraph.save(file);
        std::cout << "done !" << std::endl;
    }

    // Testing arcs removal
    i = 0;
    for (GenericGraph<Node, Edge>::VertexIDSet::const_iterator it = nodesSet.begin();
         it != nodesSet.end(); it++) {
        for (GenericGraph<Node, Edge>::VertexIDSet::const_iterator itsec = nodesSet.begin();
             itsec != nodesSet.end(); itsec++) {
            ++i;
            //if (i%10000==0) std::cout << "Step " << i << "." << std::endl;

            if (*it == *itsec)
                continue;

            if (Random::Generate()->bernoulli(prob) == 1) {
                if (myGraph.remove(*it, *itsec))
                    --nbArcsInserted;
            }
        }
    }
    std::cout << "Resume: remaining " << myGraph.arcsNb() << "(=" << nbArcsInserted << ") arcs in " << time(NULL) - t << " seconds." << std::endl;

    if (writeToXML) {
        char file[] = "AfterArcsRemoval.graphml";
        std::cout << "Writing Graph to file " << file << ": ..." << std::endl;
        myGraph.save(file);
        std::cout << "done !" << std::endl;
    }

    // Testing nodes removal
    i = myGraph.verticesNb();
    for (GenericGraph<Node, Edge>::VertexIDSet::const_iterator it = nodesSet.begin();
         it != nodesSet.end(); it++) {
        Node n = myGraph.vertex(*it);
        if (Random::Generate()->bernoulli(0.2) == 1) {
            if (myGraph.remove(n))
                --i;
            else {
                std::cerr << "Error: unable to remove a vertice tah must be in the graph." << std::endl;
                exit(1);
            }
        }
    }
    std::cout << "Resume: remaining " << myGraph.verticesNb() << "(=" << i << ") vertices in " << time(NULL) - t << " seconds." << std::endl;
    std::cout << "        remaining " << myGraph.arcsNb() << " arcs." << std::endl;

    if (writeToXML) {
        char file[] = "AfterVerticesRemoval.graphml";
        std::cout << "Writing Graph to file " << file << ": ..." << std::endl;
        myGraph.save(file);
        std::cout << "done !" << std::endl;
    }

    std::cout << "Making a dup" << std::endl;
    GenericGraph<Node, Edge>* myOtherGraph = myGraph.dup();
    std::cout << "done !" << std::endl;

    std::cout << "Changing the name of the dup" << std::endl;
    myOtherGraph->setName("ElDoublon");
    std::cout << "done !" << std::endl;

    std::cout << "Writing the dup" << std::endl;
    if (writeToXML) {
        char file[] = "ElDoublon.graphml";
        std::cout << "Writing Other Graph to file " << file << ": ..." << std::endl;
        myOtherGraph->save(file);
        std::cout << "done !" << std::endl;
    }
    std::cout << "done !" << std::endl;

    getchar();
}

void testRandomVariables(int nbSamples = 15)
{
    RandomVariable X;
    double mean, sample;

    std::cout << "Generating " << nbSamples << " of random variable X, of type '" << X.typeString() << "'" << std::endl;
    mean = 0;
    for (int i = 0; i < nbSamples; ++i) {
        sample = X.generateSample();
        mean += sample;
        std::cout << sample << " ";
    }
    std::cout << std::endl
              << "(Mean = " << mean / nbSamples << " )" << std::endl;

    X.setBernoulli(0.3);
    std::cout << "Generating " << nbSamples << " of random variable X, of type '" << X.typeString() << "'" << std::endl;
    mean = 0;
    for (int i = 0; i < nbSamples; ++i) {
        sample = X.generateSample();
        mean += sample;
        std::cout << sample << " ";
    }
    std::cout << std::endl
              << "(Mean = " << mean / nbSamples << " )" << std::endl;

    X.setUniform(0, 1);
    std::cout << "Generating " << nbSamples << " of random variable X, of type '" << X.typeString() << "'" << std::endl;
    mean = 0;
    for (int i = 0; i < nbSamples; ++i) {
        sample = X.generateSample();
        mean += sample;
        std::cout << sample << " ";
    }
    std::cout << std::endl
              << "(Mean = " << mean / nbSamples << " )" << std::endl;

    X.setIntUniform(0, 10);
    std::cout << "Generating " << nbSamples << " of random variable X, of type '" << X.typeString() << "'" << std::endl;
    mean = 0;
    for (int i = 0; i < nbSamples; ++i) {
        sample = X.generateSample();
        mean += sample;
        std::cout << sample << " ";
    }
    std::cout << std::endl
              << "(Mean = " << mean / nbSamples << " )" << std::endl;

    X.setBinomial(10, 0.3);
    std::cout << "Generating " << nbSamples << " of random variable X, of type '" << X.typeString() << "'" << std::endl;
    mean = 0;
    for (int i = 0; i < nbSamples; ++i) {
        sample = X.generateSample();
        mean += sample;
        std::cout << sample << " ";
    }
    std::cout << std::endl
              << "(Mean = " << mean / nbSamples << " )" << std::endl;

    X.setNormal(0, 1);
    std::cout << "Generating " << nbSamples << " of random variable X, of type '" << X.typeString() << "'" << std::endl;
    mean = 0;
    for (int i = 0; i < nbSamples; ++i) {
        sample = X.generateSample();
        mean += sample;
        std::cout << sample << " ";
    }
    std::cout << std::endl
              << "(Mean = " << mean / nbSamples << " )" << std::endl;

    X.setPoisson(5);
    std::cout << "Generating " << nbSamples << " of random variable X, of type '" << X.typeString() << "'" << std::endl;
    mean = 0;
    for (int i = 0; i < nbSamples; ++i) {
        sample = X.generateSample();
        mean += sample;
        std::cout << sample << " ";
    }
    std::cout << std::endl
              << "(Mean = " << mean / nbSamples << " )" << std::endl;

    X.setExponential(5);
    std::cout << "Generating " << nbSamples << " of random variable X, of type '" << X.typeString() << "'" << std::endl;
    mean = 0;
    for (int i = 0; i < nbSamples; ++i) {
        sample = X.generateSample();
        mean += sample;
        std::cout << sample << " ";
    }
    std::cout << std::endl
              << "(Mean = " << mean / nbSamples << " )" << std::endl;

    getchar();
}

int main()
{
    srand(time(NULL));

    /*
    std::cout << "Hi. We will work with times of " << SimulationTime::getBitsLength()
              << " bits with a right side of " << SimulationTime::getPrecisionLength() << " bits." << std::endl;
    //*/

    //testSimulationTime();

    //testBaseObject();

    //testRandom();

    //testDistributionRandom();

    //testIDGenerator();

    //testGenericGraph(25000, 10, true);

    //testRandomVariables(100);

    testSimulationEngine();

    std::cout << "That's all folks!" << std::endl;

    return 0;
}
