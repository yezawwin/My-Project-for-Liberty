/**
 * @file OR_Operator.cpp
 * @brief Defines the behavior of the OR logical operator.
 * Returns true only if at least one input is true.
 */

#include "OR_Operator.h"

bool OR_Operator :: evaluate( bool a, bool b) const {
    return a || b;
}

std::string OR_Operator :: getName() const { return "OR"; }

std::string OR_Operator :: getExplanation() const {
    return "True only if at least one input is true.";
}