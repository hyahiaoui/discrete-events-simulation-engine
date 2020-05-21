/**
 * \file    genericgraph.h
 * \brief   Declaration and implementation of generic graph class
 * \date    June, 27th, 2011
 * \author  Yahiaoui H.
 */

#ifndef GENERICGRAPH_H
#define GENERICGRAPH_H

#include <cstdlib>
#include <map>
#include <set>
#include <stdexcept>
#include <vector>

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>

#include "uniqueidgenerator.h"

/**
  * \brief
  */
template <typename V, typename A, bool DirectedGraph = true, class CompareV = std::less<V>>
class cGenericGraph {
public: // Types and consts
    typedef unsigned long VertexID;
    typedef std::pair<VertexID, VertexID> ArcID;
    static const VertexID IllegalVertexID; // = ~(VertexID)(0);
    static const ArcID IllegalArcID; // = ArcID(IllegalVertexID, IllegalVertexID);

    typedef std::set<VertexID> VertexIDSet;
    typedef std::set<ArcID> ArcIDSet;

    typedef std::vector<VertexID> VertexIDPath;

public: // Methods
    /**
      * \brief  Default constructor
      * \param  graphName   the build graph's name
      */
    cGenericGraph(const char* graphName = 0);

    /**
      * \brief  Copy constructor
      */
    cGenericGraph(const cGenericGraph& other);

    /**
      * \brief  Destructor
      */
    virtual ~cGenericGraph();

    /**
      * \brief  Assign operator
      */
    cGenericGraph& operator=(const cGenericGraph& other);

    /**
      * \brief  Duplication operator
      */
    cGenericGraph* dup();

    /**
      * \brief
      */
    void clear();

    /**
      * \brief
      */
    const char* name() const;

    /**
      * \brief
      */
    void setName(const char* graphName = 0);

    // Insertion methods
    /**
      * \brief
      * \param
      * \return
      */
    virtual VertexID add(const V& newVertex, const VertexID newVertexID = IllegalVertexID);

    /**
      * \brief
      * \param
      * \return
      */
    virtual ArcID add(const V& vertex1, const V& vertex2, const A& newArc, bool addVertexIfMissing = false);

    /**
      * \brief
      * \param
      * \return
      */
    virtual ArcID add(const V& vertex1, const V& vertex2, bool addVertexIfMissing = false);

    /**
      * \brief
      * \param
      * \return
      */
    virtual ArcID add(const VertexID vertex1Id, const VertexID vertex2Id, const A& newArc, bool addVertexIfMissing = false);

    /**
      * \brief
      * \param
      * \return
      */
    virtual ArcID add(const VertexID vertex1Id, const VertexID vertex2Id, bool addVertexIfMissing = false);

    /**
      * \brief
      * \param
      * \return
      */
    virtual ArcID add(const ArcID& arcId, bool addVertexIfMissing = false);

    /**
      * \brief
      * \param
      * \return
      */
    virtual ArcID add(const ArcID& arcId, const A& newArc, bool addVertexIfMissing = false);

    // Getters methods
    /**
      * \brief
      * \param
      * \return
      */
    virtual VertexID vertex(const V& vertex) const;

    /**
      * \brief
      * \param
      * \return
      */
    virtual const V& vertex(const VertexID vertexId) const;

    /**
      * \brief
      * \param
      * \return
      */
    virtual ArcID arc(const V& vertex1, const V& vertex2) const;

    /**
      * \brief
      * \param
      * \return
      */
    virtual ArcID arc(const VertexID vertex1Id, const VertexID vertex2Id) const;

    /**
      * \brief
      * \param
      * \return
      */
    virtual A arc(const ArcID& arcId) const;

    /**
      * \brief
      * \param
      * \return
      */
    virtual VertexID arcTail(const ArcID& arcId) const;

    /**
      * \brief
      * \param
      * \return
      */
    virtual VertexID arcHead(const ArcID& arcId) const;

    /**
      * \brief
      * \param
      * \return
      */
    virtual VertexIDSet vertices() const;

    /**
      * \brief
      * \param
      * \return
      */
    virtual ArcIDSet arcs() const;

    /**
      * \brief
      * \param
      * \return
      */
    virtual ArcIDSet arcs(const VertexID vertexId) const;

    /**
      * \brief
      * \param
      * \return
      */
    virtual ArcIDSet arcs(const V& vertex) const;

    /**
      * \brief
      * \param
      * \return
      */
    virtual VertexIDSet successors(const VertexID vertexId) const;

    /**
      * \brief
      * \param
      * \return
      */
    virtual VertexIDSet successors(const V& vertex) const;

    /**
      * \brief param return
      */
    virtual VertexIDSet predecessors(const VertexID vertexId) const;

    /**
      * \brief
      * \param
      * \return
      */
    virtual VertexIDSet predecessors(const V& vertex) const;

    /**
      * \brief
      * \param
      * \return
      */
    virtual unsigned long verticesNb() const;

    /**
      * \brief
      * \param
      * \return
      */
    virtual unsigned long arcsNb() const;

    /**
      * \brief
      * \param
      * \return
      */
    virtual unsigned long arcsNb(const VertexID vertexId) const;

    /**
      * \brief
      * \param
      * \return
      */
    virtual unsigned long arcsNb(const V& vertex) const;

    /**
      * \brief
      * \param
      * \return
      */
    virtual unsigned long successorsNb(const VertexID vertexId) const;
    /**
      * \brief
      * \param
      * \return
      */
    virtual unsigned long successorsNb(const V& vertex) const;
    /**
      * \brief
      * \param
      * \return
      */
    virtual unsigned long predecessorsNb(const VertexID vertexId) const;
    /**
      * \brief
      * \param
      * \return
      */
    virtual unsigned long predecessorsNb(const V& vertex) const;

    // Setters methods
    /**
      * \brief
      * \param
      * \return
      */
    virtual void setVertex(const VertexID vertexId, const V& vertexData);
    /**
      * \brief
      * \param
      * \return
      */
    virtual void setArc(const ArcID& arcId, const A& arcData);

    // General information retrieval methods
    /**
      * \brief
      * \param
      * \return
      */
    virtual bool isEmpty() const;

    /**
      * \brief
      * \param
      * \return
      */
    virtual bool exists(const V& vertex) const;

    /**
      * \brief
      * \param
      * \return
      */
    virtual bool exists(const VertexID vertexId) const;

    /**
      * \brief
      * \param
      * \return
      */
    virtual bool exists(const V& vertex1, const V& vertex2) const;

    /**
      * \brief
      * \param
      * \return
      */
    virtual bool exists(const VertexID vertex1Id, const VertexID vertex2Id) const;

    /**
      * \brief
      * \param
      * \return
      */
    virtual bool exists(const ArcID& arcId) const;

    // Removal methods
    /**
      * \brief
      * \param
      * \return
      */
    virtual bool remove(const V& vertex);
    /**
      * \brief
      * \param
      * \return
      */
    virtual bool remove(const VertexID vertexId);

    /**
      * \brief
      * \param
      * \return
      */
    virtual bool remove(const ArcID& arcId);

    /**
      * \brief
      * \param
      * \return
      */
    virtual bool remove(const VertexID vertex1Id, const VertexID vertex2Id);

    /**
      * \brief
      * \param
      * \return
      */
    virtual bool remove(const V& vertex1, const V& vertex2);

    // Path related methods
    /**
      * \brief
      * \param
      * \return
      */
    // virtual VertexIDPath  shortestPath(const VertexID sourceVertexId, const VertexID destVertexId);

    /**
      * \brief
      * \param
      * \return
      */
    //virtual VertexIDPath  shortestPath(const V & sourceVertex, const V & destVertex);

    // Load/save related methods
    /**
      * \brief
      * \param
      * \return true if saving process did not encounter errors, false else.
      */
    virtual bool save(std::ostream& ost) const;

    /**
      * \brief
      * \param
      * \return true if saving process did not encounter errors, false else.
      */
    virtual bool save(const char* writeFileName) const;

    /**
      * \brief
      * \param
      * \return true if loading process did not encounter errors, false else.
      */
    //virtual bool  load(std::istream & ist);

    /**
      * \brief
      * \param
      * \return true if loading process did not encounter errors, false else.
      */
    //virtual bool  load(const char * readFileName);

private:
    // Types definitions
    typedef std::map<V, VertexID, CompareV> Vertex2VertexID;
    typedef std::map<VertexID, A> SuccessorsSet;
    struct VertexData {
        typename Vertex2VertexID::iterator vertexRef;
        SuccessorsSet vertexSuccessors;
        VertexIDSet vertexPredecessors;
    };
    typedef std::map<VertexID, VertexData> VerticeDataSet;

    // Attributs declarations
    bool m_directed;
    unsigned long m_arcsNumber;
    Vertex2VertexID m_verticesData;
    VerticeDataSet m_verticesArcs;
    char* m_graphName;
};

// Assignation of static attributs values
template <typename V, typename A, bool DirectedGraph, class CompareV>
const typename cGenericGraph<V, A, DirectedGraph, CompareV>::VertexID cGenericGraph<V, A, DirectedGraph, CompareV>::IllegalVertexID = ~(VertexID)(0);

template <typename V, typename A, bool DirectedGraph, class CompareV>
const typename cGenericGraph<V, A, DirectedGraph, CompareV>::ArcID cGenericGraph<V, A, DirectedGraph, CompareV>::IllegalArcID = cGenericGraph<V, A, DirectedGraph, CompareV>::ArcID(IllegalVertexID, IllegalVertexID);

// Constructor
template <typename V, typename A, bool DirectedGraph, class CompareV>
cGenericGraph<V, A, DirectedGraph, CompareV>::cGenericGraph(const char* graphName)
    : m_directed(DirectedGraph)
    , m_arcsNumber(0)
    , m_verticesData()
    , m_verticesArcs()
    , m_graphName(0)
{
    setName(graphName);
}

// Copy Constructor
template <typename V, typename A, bool DirectedGraph, class CompareV>
cGenericGraph<V, A, DirectedGraph, CompareV>::cGenericGraph(const cGenericGraph<V, A, DirectedGraph, CompareV>& other)
    : m_directed(DirectedGraph)
    , m_arcsNumber(0)
    , m_verticesData()
    , m_verticesArcs()
    , m_graphName(0)
{
    operator=(other);
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
const char* cGenericGraph<V, A, DirectedGraph, CompareV>::name() const
{
    return m_graphName;
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
void cGenericGraph<V, A, DirectedGraph, CompareV>::setName(const char* graphName)
{
    if (m_graphName) {
        delete[] m_graphName;
        m_graphName = 0;
    }
    if (graphName != 0) {
        m_graphName = new char[strlen(graphName) + 1];
        strcpy(m_graphName, graphName);
    }
}

// Assign operator
template <typename V, typename A, bool DirectedGraph, class CompareV>
cGenericGraph<V, A, DirectedGraph, CompareV>& cGenericGraph<V, A, DirectedGraph, CompareV>::operator=(const cGenericGraph<V, A, DirectedGraph, CompareV>& other)
{
    if (this != &other) {
        clear();
        typename cGenericGraph<V, A, DirectedGraph, CompareV>::ArcIDSet arcsSet = other.arcs();
        for (typename cGenericGraph<V, A, DirectedGraph, CompareV>::ArcIDSet::const_iterator arcIt = arcsSet.begin(); arcIt != arcsSet.end(); arcIt++)
            add(*arcIt, other.arc(*arcIt), true);

        typename cGenericGraph<V, A, DirectedGraph, CompareV>::VertexIDSet verticesSet = other.vertices();
        for (typename cGenericGraph<V, A, DirectedGraph, CompareV>::VertexIDSet::const_iterator vertexIt = verticesSet.begin(); vertexIt != verticesSet.end(); vertexIt++)
            setVertex(*vertexIt, other.vertex(*vertexIt));
    }
    return *this;
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
cGenericGraph<V, A, DirectedGraph, CompareV>* cGenericGraph<V, A, DirectedGraph, CompareV>::dup()
{
    return (new cGenericGraph<V, A, DirectedGraph, CompareV>(*this));
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
void cGenericGraph<V, A, DirectedGraph, CompareV>::clear()
{
    m_verticesData.clear();
    for (typename VerticeDataSet::iterator it = m_verticesArcs.begin(); it != m_verticesArcs.end();) // Parse all vertices data ...
    {
        it->second.vertexSuccessors.clear();
        it->second.vertexPredecessors.clear();
        m_verticesArcs.erase(it++);
    }
    m_verticesArcs.clear();
    m_arcsNumber = 0;
}

// Destructor
template <typename V, typename A, bool DirectedGraph, class CompareV>
cGenericGraph<V, A, DirectedGraph, CompareV>::~cGenericGraph()
{
    clear();
    if (m_graphName)
        delete[] m_graphName;
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
typename cGenericGraph<V, A, DirectedGraph, CompareV>::VertexID cGenericGraph<V, A, DirectedGraph, CompareV>::add(const V& newVertex, const VertexID newVertexId)
{
    if (newVertexId == IllegalVertexID) // invalid vertex id
    {
        typename Vertex2VertexID::iterator vertexIt = m_verticesData.find(newVertex);
        // if the vertex does not exist, insert it with an id generated automatically
        if (vertexIt == m_verticesData.end()) // If the vertex does not exist , ...
        {
            VertexID insertId = cUniqueIDGenerator<VertexID>::Generator()->newId();
            VertexData newVertexData;
            newVertexData.vertexSuccessors.clear();
            newVertexData.vertexPredecessors.clear();
            // Insert the new vertex with a new Id, and set the returned iterator in the vertexRef attribute
            newVertexData.vertexRef = m_verticesData.insert(std::pair<V, VertexID>(newVertex, insertId)).first;
            m_verticesArcs.insert(std::pair<VertexID, VertexData>(insertId, newVertexData));
            return insertId;
        } else // it is already there, return it's ID
            return vertexIt->second;

    } else // valid vertex id
    {
        // check the existance of the vertex id
        if (m_verticesArcs.find(newVertexId) != m_verticesArcs.end()) {
            // if it exists, set the vertex data for this vertex id
            setVertex(newVertexId, newVertex);
            return newVertexId;
        } else {
            // if it does not exist: insert with the given information
            VertexData newVertexData;
            newVertexData.vertexSuccessors.clear();
            newVertexData.vertexPredecessors.clear();
            // Insert the new vertex with the given id Id, and set the returned iterator in the vertexRef attribute
            newVertexData.vertexRef = m_verticesData.insert(std::pair<V, VertexID>(newVertex, newVertexId)).first;
            m_verticesArcs.insert(std::pair<VertexID, VertexData>(newVertexId, newVertexData));
            return newVertexId;
        }
    }
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
typename cGenericGraph<V, A, DirectedGraph, CompareV>::ArcID cGenericGraph<V, A, DirectedGraph, CompareV>::add(const V& vertex1, const V& vertex2, bool addVertexIfMissing)
{
    A defaultArc;
    return add(vertex1, vertex2, defaultArc, addVertexIfMissing);
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
typename cGenericGraph<V, A, DirectedGraph, CompareV>::ArcID cGenericGraph<V, A, DirectedGraph, CompareV>::add(const V& vertex1, const V& vertex2, const A& newArc, bool addVertexIfMissing)
{
    VertexID vertex1Id, vertex2Id;
    typename Vertex2VertexID::iterator vertex1DataIt = m_verticesData.find(vertex1);
    if (vertex1DataIt == m_verticesData.end()) {
        if (addVertexIfMissing)
            vertex1Id = add(vertex1);
        else
            return IllegalArcID;
    } else
        vertex1Id = vertex1DataIt->second;

    typename Vertex2VertexID::iterator vertex2DataIt = m_verticesData.find(vertex2);
    if (vertex2DataIt == m_verticesData.end()) {
        if (addVertexIfMissing)
            vertex2Id = add(vertex2);
        else
            return IllegalArcID;
    } else
        vertex2Id = vertex2DataIt->second;

    return add(vertex1Id, vertex2Id, newArc);
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
typename cGenericGraph<V, A, DirectedGraph, CompareV>::ArcID cGenericGraph<V, A, DirectedGraph, CompareV>::add(const VertexID vertex1Id, const VertexID vertex2Id, bool addVertexIfMissing)
{
    A defaultArc;
    return add(vertex1Id, vertex2Id, defaultArc, addVertexIfMissing);
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
typename cGenericGraph<V, A, DirectedGraph, CompareV>::ArcID cGenericGraph<V, A, DirectedGraph, CompareV>::add(const VertexID vertex1Id, const VertexID vertex2Id, const A& newArc, bool addVertexIfMissing)
{
    typename VerticeDataSet::iterator vertex1It = m_verticesArcs.find(vertex1Id);
    if (vertex1It == m_verticesArcs.end()) {
        if (addVertexIfMissing) {
            V defaultVertex;
            add(defaultVertex, vertex1Id);
            vertex1It = m_verticesArcs.find(vertex1Id);
        } else
            return IllegalArcID;
    }
    typename VerticeDataSet::iterator vertex2It = m_verticesArcs.find(vertex2Id);
    if (vertex2It == m_verticesArcs.end()) {
        if (addVertexIfMissing) {
            V defaultVertex;
            add(defaultVertex, vertex2Id);
            vertex2It = m_verticesArcs.find(vertex2Id);
        } else
            return IllegalArcID;
    }

    // Every thing is right (vertices are inserted) proceed with the insertion of the arc
    vertex1It->second.vertexSuccessors.insert(std::pair<VertexID, A>(vertex2Id, newArc));
    vertex2It->second.vertexPredecessors.insert(vertex1Id);

    m_arcsNumber++;

    // Finally, return the inserted arc references
    return ArcID(vertex1Id, vertex2Id);
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
typename cGenericGraph<V, A, DirectedGraph, CompareV>::ArcID cGenericGraph<V, A, DirectedGraph, CompareV>::add(const ArcID& arcId, bool addVertexIfMissing)
{
    A defaultArc;
    return add(arcId.first, arcId.second, defaultArc, addVertexIfMissing);
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
typename cGenericGraph<V, A, DirectedGraph, CompareV>::ArcID cGenericGraph<V, A, DirectedGraph, CompareV>::add(const ArcID& arcId, const A& newArc, bool addVertexIfMissing)
{
    return add(arcId.first, arcId.second, newArc, addVertexIfMissing);
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
typename cGenericGraph<V, A, DirectedGraph, CompareV>::VertexID cGenericGraph<V, A, DirectedGraph, CompareV>::vertex(const V& vertex) const
{
    typename Vertex2VertexID::const_iterator vertexDataIt = m_verticesData.find(vertex);
    if (vertexDataIt == m_verticesData.end())
        return IllegalVertexID;

    return vertexDataIt->second;
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
const V& cGenericGraph<V, A, DirectedGraph, CompareV>::vertex(const VertexID vertexId) const
{
    typename VerticeDataSet::const_iterator vertexIt = m_verticesArcs.find(vertexId);
    if (vertexIt == m_verticesArcs.end()) {
        std::ostringstream exceptionStream;
        exceptionStream << __PRETTY_FUNCTION__ << ": Unable to find vertex with vertex Id " << vertexId;
        throw std::invalid_argument(exceptionStream.str());
    }

    return vertexIt->second.vertexRef->first;
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
typename cGenericGraph<V, A, DirectedGraph, CompareV>::ArcID cGenericGraph<V, A, DirectedGraph, CompareV>::arc(const V& vertex1, const V& vertex2) const
{
    typename Vertex2VertexID::const_iterator vertex1DataIt = m_verticesData.find(vertex1);
    if (vertex1DataIt == m_verticesData.end())
        return IllegalArcID;

    typename Vertex2VertexID::const_iterator vertex2DataIt = m_verticesData.find(vertex2);
    if (vertex2DataIt == m_verticesData.end())
        return IllegalArcID;

    return arc(vertex1DataIt->second, vertex2DataIt->second);
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
typename cGenericGraph<V, A, DirectedGraph, CompareV>::ArcID cGenericGraph<V, A, DirectedGraph, CompareV>::arc(const VertexID vertex1Id, const VertexID vertex2Id) const
{
    typename VerticeDataSet::const_iterator vertex1It = m_verticesArcs.find(vertex1Id);
    if (vertex1It == m_verticesArcs.end())
        return IllegalArcID;

    typename VerticeDataSet::const_iterator vertex2It = m_verticesArcs.find(vertex2Id);
    if (vertex2It == m_verticesArcs.end())
        return IllegalArcID;

    if (vertex1It->second.vertexSuccessors.find(vertex2Id) == vertex1It->second.vertexSuccessors.end())
        // this arc does not exist
        return IllegalArcID;
    else
        return ArcID(vertex1Id, vertex2Id);
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
A cGenericGraph<V, A, DirectedGraph, CompareV>::arc(const ArcID& arcId) const
{
    typename VerticeDataSet::const_iterator firstVertexIt = m_verticesArcs.find(arcId.first);
    if (firstVertexIt == m_verticesArcs.end()) {
        std::ostringstream exceptionStream;
        exceptionStream << __PRETTY_FUNCTION__ << ": Unable to find arc tail vertex in the graph (" << arcId.first << ")";
        throw std::invalid_argument(exceptionStream.str());
    }

    typename VerticeDataSet::const_iterator secondVertexIt = m_verticesArcs.find(arcId.second);
    if (secondVertexIt == m_verticesArcs.end()) {
        std::ostringstream exceptionStream;
        exceptionStream << __PRETTY_FUNCTION__ << ": Unable to find arc head vertex in the graph (" << arcId.second << ")";
        throw std::invalid_argument(exceptionStream.str());
    }

    if (firstVertexIt->second.vertexSuccessors.find(arcId.second)
        == firstVertexIt->second.vertexSuccessors.end()) // this arc does not exist
    {
        std::ostringstream exceptionStream;
        exceptionStream << __PRETTY_FUNCTION__ << ": Unable to find arc vertex in the graph (" << arcId.first << "->" << arcId.second << ")";
        throw std::invalid_argument(exceptionStream.str());
    }

    return firstVertexIt->second.vertexSuccessors.find(arcId.second)->second;
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
typename cGenericGraph<V, A, DirectedGraph, CompareV>::VertexID cGenericGraph<V, A, DirectedGraph, CompareV>::arcTail(const ArcID& arcId) const
{
    return arcId.first;
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
typename cGenericGraph<V, A, DirectedGraph, CompareV>::VertexID cGenericGraph<V, A, DirectedGraph, CompareV>::arcHead(const ArcID& arcId) const
{
    return arcId.second;
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
typename cGenericGraph<V, A, DirectedGraph, CompareV>::VertexIDSet cGenericGraph<V, A, DirectedGraph, CompareV>::vertices() const
{
    VertexIDSet verticesSet;
    for (typename VerticeDataSet::const_iterator it = m_verticesArcs.begin(); it != m_verticesArcs.end(); it++)
        verticesSet.insert(it->first);
    return verticesSet;
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
typename cGenericGraph<V, A, DirectedGraph, CompareV>::ArcIDSet cGenericGraph<V, A, DirectedGraph, CompareV>::arcs() const
{
    ArcIDSet arcsSet;
    for (typename VerticeDataSet::const_iterator it = m_verticesArcs.begin(); it != m_verticesArcs.end(); it++) // Parse all vertices ...
        for (typename SuccessorsSet::const_iterator succit = it->second.vertexSuccessors.begin(); succit != it->second.vertexSuccessors.end(); succit++) // parse all successors of each vertex
            arcsSet.insert(ArcID(it->first, succit->first)); // add the obtained arc to the set.
    return arcsSet;
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
typename cGenericGraph<V, A, DirectedGraph, CompareV>::ArcIDSet cGenericGraph<V, A, DirectedGraph, CompareV>::arcs(const VertexID vertexId) const
{
    ArcIDSet arcsSet;
    typename VerticeDataSet::const_iterator vertexIt = m_verticesArcs.find(vertexId);
    if (vertexIt != m_verticesArcs.end())
        for (typename SuccessorsSet::const_iterator succit = vertexIt->second.vertexSuccessors.begin(); succit != vertexIt->second.vertexSuccessors.end(); succit++) // parse all successors of each vertex
            arcsSet.insert(ArcID(vertexId, succit->first)); // add the obtained arc to the set.
    return arcsSet;
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
typename cGenericGraph<V, A, DirectedGraph, CompareV>::ArcIDSet cGenericGraph<V, A, DirectedGraph, CompareV>::arcs(const V& vertex) const
{
    if (m_verticesData.find(vertex) != m_verticesData.end())
        return arcs(m_verticesData.find(vertex)->second);
    else
        return ArcIDSet();
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
typename cGenericGraph<V, A, DirectedGraph, CompareV>::VertexIDSet cGenericGraph<V, A, DirectedGraph, CompareV>::successors(const VertexID vertexId) const
{
    VertexIDSet verticesSet;
    typename VerticeDataSet::const_iterator vertexIt = m_verticesArcs.find(vertexId);
    if (vertexIt != m_verticesArcs.end())
        for (typename SuccessorsSet::const_iterator succit = vertexIt->second.vertexSuccessors.begin(); succit != vertexIt->second.vertexSuccessors.end(); succit++) // parse all successors of each vertex
            verticesSet.insert(succit->first); // add the obtained arc to the set.
    return verticesSet;
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
typename cGenericGraph<V, A, DirectedGraph, CompareV>::VertexIDSet cGenericGraph<V, A, DirectedGraph, CompareV>::successors(const V& vertex) const
{
    if (m_verticesData.find(vertex) != m_verticesData.end())
        return successors(m_verticesData.find(vertex)->second);
    else
        return VertexIDSet();
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
typename cGenericGraph<V, A, DirectedGraph, CompareV>::VertexIDSet cGenericGraph<V, A, DirectedGraph, CompareV>::predecessors(const VertexID vertexId) const
{
    typename VerticeDataSet::const_iterator vertexIt = m_verticesArcs.find(vertexId);
    if (vertexIt != m_verticesArcs.end())
        return vertexIt->second.vertexPredecessors;
    else
        return VertexIDSet();
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
typename cGenericGraph<V, A, DirectedGraph, CompareV>::VertexIDSet cGenericGraph<V, A, DirectedGraph, CompareV>::predecessors(const V& vertex) const
{
    if (m_verticesData.find(vertex) != m_verticesData.end())
        return predecessors(m_verticesData.find(vertex)->second);
    else
        return VertexIDSet();
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
unsigned long cGenericGraph<V, A, DirectedGraph, CompareV>::verticesNb() const
{
    return m_verticesData.size();
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
unsigned long cGenericGraph<V, A, DirectedGraph, CompareV>::arcsNb() const
{
    return m_arcsNumber;
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
unsigned long cGenericGraph<V, A, DirectedGraph, CompareV>::arcsNb(const VertexID vertexId) const
{
    return arcs(vertexId).size();
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
unsigned long cGenericGraph<V, A, DirectedGraph, CompareV>::arcsNb(const V& vertex) const
{
    return arcs(vertex).size();
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
unsigned long cGenericGraph<V, A, DirectedGraph, CompareV>::successorsNb(const VertexID vertexId) const
{
    return successors(vertexId).size();
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
unsigned long cGenericGraph<V, A, DirectedGraph, CompareV>::successorsNb(const V& vertex) const
{
    return successors(vertex).size();
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
unsigned long cGenericGraph<V, A, DirectedGraph, CompareV>::predecessorsNb(const VertexID vertexId) const
{
    return predecessors(vertexId).size();
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
unsigned long cGenericGraph<V, A, DirectedGraph, CompareV>::predecessorsNb(const V& vertex) const
{
    return predecessors(vertex).size();
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
void cGenericGraph<V, A, DirectedGraph, CompareV>::setVertex(const VertexID vertexId, const V& vertexData)
{
    typename VerticeDataSet::iterator vertexIt = m_verticesArcs.find(vertexId);
    if (vertexIt == m_verticesArcs.end())
        return; // nothing to do, as the Id is not valid

    // Remove the association between old vertex data and vertex id
    m_verticesData.erase(vertexIt->second.vertexRef);

    // Set another association between new vertex data and vertex id
    vertexIt->second.vertexRef = m_verticesData.insert(std::pair<V, VertexID>(vertexData, vertexId)).first;
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
void cGenericGraph<V, A, DirectedGraph, CompareV>::setArc(const ArcID& arcId, const A& arcData)
{
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
bool cGenericGraph<V, A, DirectedGraph, CompareV>::isEmpty() const
{
    return m_verticesArcs.empty();
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
bool cGenericGraph<V, A, DirectedGraph, CompareV>::exists(const V& vertex) const
{
    return (m_verticesData.find(vertex) != m_verticesData.end());
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
bool cGenericGraph<V, A, DirectedGraph, CompareV>::exists(const VertexID vertexId) const
{
    return (m_verticesArcs.find(vertexId) != m_verticesArcs.end());
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
bool cGenericGraph<V, A, DirectedGraph, CompareV>::exists(const V& vertex1, const V& vertex2) const
{
    return (arc(vertex1, vertex2) != IllegalArcID);
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
bool cGenericGraph<V, A, DirectedGraph, CompareV>::exists(const VertexID vertex1Id, const VertexID vertex2Id) const
{
    return (arc(vertex1Id, vertex2Id) != IllegalArcID);
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
bool cGenericGraph<V, A, DirectedGraph, CompareV>::exists(const ArcID& arcId) const
{
    typename VerticeDataSet::const_iterator firstVertexIt = m_verticesArcs.find(arcId.first);
    if (firstVertexIt == m_verticesArcs.end())
        return false;

    typename VerticeDataSet::const_iterator secondVertexIt = m_verticesArcs.find(arcId.second);
    if (secondVertexIt == m_verticesArcs.end())
        return false;

    return (firstVertexIt->second.vertexSuccessors.find(arcId.second) != firstVertexIt->second.vertexSuccessors.end());
}

// Removal methods
template <typename V, typename A, bool DirectedGraph, class CompareV>
bool cGenericGraph<V, A, DirectedGraph, CompareV>::remove(const V& vertex)
{
    typename Vertex2VertexID::iterator vertexDataIt = m_verticesData.find(vertex);
    if (vertexDataIt == m_verticesData.end())
        return false;

    return remove(vertexDataIt->second);
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
bool cGenericGraph<V, A, DirectedGraph, CompareV>::remove(const VertexID vertexId)
{
    typename VerticeDataSet::iterator vertexIt = m_verticesArcs.find(vertexId);
    if (vertexIt == m_verticesArcs.end())
        return false;

    // Remove this vertex of successors lists of all his predecessors
    for (typename VertexIDSet::const_iterator predit = vertexIt->second.vertexPredecessors.begin();
         predit != vertexIt->second.vertexPredecessors.end(); predit++)
        m_verticesArcs.find(*predit)->second.vertexSuccessors.erase(vertexId);
    // Update arcs number before remove the arcs
    m_arcsNumber -= vertexIt->second.vertexPredecessors.size();
    vertexIt->second.vertexPredecessors.clear();

    // Remove this vertex of predecessors lists of all his successors
    for (typename SuccessorsSet::const_iterator succit = vertexIt->second.vertexSuccessors.begin();
         succit != vertexIt->second.vertexSuccessors.end(); succit++)
        m_verticesArcs.find(succit->first)->second.vertexPredecessors.erase(vertexId);
    // Update arcs number before remove the arcs
    m_arcsNumber -= vertexIt->second.vertexSuccessors.size();
    vertexIt->second.vertexSuccessors.clear();

    // Remove the vertex from both data structures
    m_verticesData.erase(vertexIt->second.vertexRef);
    m_verticesArcs.erase(vertexIt);

    return true;
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
bool cGenericGraph<V, A, DirectedGraph, CompareV>::remove(const ArcID& arcId)
{
    typename VerticeDataSet::const_iterator firstVertexIt = m_verticesArcs.find(arcId.first);
    if (firstVertexIt == m_verticesArcs.end())
        return false;

    typename VerticeDataSet::const_iterator secondVertexIt = m_verticesArcs.find(arcId.second);
    if (secondVertexIt == m_verticesArcs.end())
        return false;

    return remove(firstVertexIt->first, secondVertexIt->first);
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
bool cGenericGraph<V, A, DirectedGraph, CompareV>::remove(const V& vertex1, const V& vertex2)
{
    typename Vertex2VertexID::iterator vertex1DataIt = m_verticesData.find(vertex1);
    if (vertex1DataIt == m_verticesData.end())
        return false;

    typename Vertex2VertexID::iterator vertex2DataIt = m_verticesData.find(vertex2);
    if (vertex2DataIt == m_verticesData.end())
        return false;

    return remove(vertex1DataIt->first, vertex2DataIt->first);
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
bool cGenericGraph<V, A, DirectedGraph, CompareV>::remove(const VertexID vertex1Id, const VertexID vertex2Id)
{
    typename VerticeDataSet::iterator vertex1It = m_verticesArcs.find(vertex1Id);
    if (vertex1It == m_verticesArcs.end())
        return false;

    typename VerticeDataSet::iterator vertex2It = m_verticesArcs.find(vertex2Id);
    if (vertex2It == m_verticesArcs.end())
        return false;

    typename SuccessorsSet::iterator arcIt = vertex1It->second.vertexSuccessors.find(vertex2Id);
    if (arcIt == vertex1It->second.vertexSuccessors.end()) // There no such arc
        return false;

    // Remove vertex2Id from successors of vertex1Id, and ...
    vertex1It->second.vertexSuccessors.erase(arcIt);
    // ... vertex1Id from predecessors of vertex2Id, and ...
    vertex2It->second.vertexPredecessors.erase(vertex1Id);
    // ... update arcs number, and ...
    --m_arcsNumber;
    // ... tell that we suppressed the arc
    return true;
}

/*
template <typename V, typename A, bool DirectedGraph, class CompareV>
typename cGenericGraph<V, A, DirectedGraph, CompareV>::VertexIDPath  cGenericGraph<V, A, DirectedGraph, CompareV>::shortestPath(const VertexID sourceVertexId, const VertexID destVertexId)
{
    // TODO
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
typename cGenericGraph<V, A, DirectedGraph, CompareV>::VertexIDPath  cGenericGraph<V, A, DirectedGraph, CompareV>::shortestPath(const V & sourceVertex, const V & destVertex)
{
    // TODO
}
//*/

template <typename V, typename A, bool DirectedGraph, class CompareV>
bool cGenericGraph<V, A, DirectedGraph, CompareV>::save(const char* writeFileName) const
{
    std::fstream outFile;
    outFile.open(writeFileName, std::ios_base::out | std::ios_base::trunc);

    if (!outFile.is_open())
        return false;
    bool success = save(outFile);
    outFile.close();

    return success;
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
bool cGenericGraph<V, A, DirectedGraph, CompareV>::save(std::ostream& ost) const
{
    std::string indentStr[5] = {
        "",
        "\t",
        "\t\t",
        "\t\t\t",
        "\t\t\t\t",
    };
    unsigned int indentLevel = 0;

    // XML file Header [Begin of GraphML file]
    ost << indentStr[indentLevel]
        << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
    ost << indentStr[indentLevel]
        << "<graphml    xmlns=\"http://graphml.graphdrawing.org/xmlns\"" << std::endl;
    ost << indentStr[indentLevel]
        << "            xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"" << std::endl;
    ost << indentStr[indentLevel]
        << "            xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd\">" << std::endl;
    ++indentLevel;

    // Graph definition begin
    ost << indentStr[indentLevel]
        << "<graph id=\"" << (m_graphName == 0 ? "_NONAME_" : m_graphName) << "\" edgedefault=\"directed\">" << std::endl;
    ++indentLevel;

    // Parse each vertex, and write its data
    for (typename VerticeDataSet::const_iterator it = m_verticesArcs.begin(); it != m_verticesArcs.end(); it++)
        ost << indentStr[indentLevel]
            << "<node id=\"" << it->first << "\"/>" << std::endl;

    // Parse each successor of each vertex, and write the data of this arc
    for (typename VerticeDataSet::const_iterator it = m_verticesArcs.begin(); it != m_verticesArcs.end(); it++)
        for (typename SuccessorsSet::const_iterator succit = it->second.vertexSuccessors.begin(); succit != it->second.vertexSuccessors.end(); succit++)
            ost << indentStr[indentLevel]
                << "<edge source=\"" << it->first
                << "\" target=\"" << succit->first << "\"/>" << std::endl;

    // Graph definition end
    --indentLevel;
    ost << indentStr[indentLevel] << "</graph>" << std::endl;

    // End of GraphML file
    --indentLevel;
    ost << indentStr[indentLevel] << "</graphml>" << std::endl;

    return true;
}

/*
template <typename V, typename A, bool DirectedGraph, class CompareV>
bool  cGenericGraph<V, A, DirectedGraph, CompareV>::load(const char *readFileName)
{
    // \todo Implement graph loading from xml file method
}

template <typename V, typename A, bool DirectedGraph, class CompareV>
bool  cGenericGraph<V, A, DirectedGraph, CompareV>::load(std::ostream &ost)
{
    // \todo Implement graph loading from xml file method
}
//*/

#endif // GENERICGRAPH_H
