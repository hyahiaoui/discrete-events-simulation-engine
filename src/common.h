/**
 * \file    common.h
 * \brief   Declaration of commonly used types, variables and functions
 * \date    June, 10th, 2011
 * \author  Yahiaoui H.
 */

#ifndef COMMON_H
#define COMMON_H

//  Common types definitions
/**
  * \brief  Type of identifiers of modules and static elements in map edition and simulation.
  */
typedef unsigned long tModuleId;
/**
  * \brief  Type of identifiers of particles dynamic elements in map edition and simulation.
  */
typedef unsigned long long tParticleId;

// Common consts definitions
/**
  * \brief  Special module identifier to specify invalidity.
  */
const tModuleId invalidModuleId = ~((tModuleId)0); // All bits to 1
/**
  * \brief  Special particle identifier to specify invalidity.
  */
const tParticleId invalidParticleId = ~((tParticleId)0); // All bits to 1

#endif // COMMON_H
