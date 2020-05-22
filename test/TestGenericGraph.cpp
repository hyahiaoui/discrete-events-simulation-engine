#include "GenericGraph.h"
#include "Random.h"

#include "catch2/catch.hpp"

#include <iostream>

// //#define DEBUG
// //#define CHECK_BEFORE_INSERTION

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

TEST_CASE("Random GenericGraph can be created", "[GenericGraph]")
{
    int nbNodes = 25000;
    int meanArcsPerNode = 10;
    bool writeToXML = false;

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
}