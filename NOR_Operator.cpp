/**
 * @file NOR_Operator.cpp
 * @brief Defines the behavior of the NOR logical operator.
 * Returns true only if both inputs are false.
 */

#include "NOR_Operator.h"

bool NOR_Operator :: evaluate( bool a, bool b) const {
    return !(a || b) ;
}

std::string NOR_Operator :: getName() const { return "NOR"; }

std::string NOR_Operator :: getExplanation() const {
    return "True only if both inputs are false.";
}