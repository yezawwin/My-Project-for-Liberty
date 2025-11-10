/**
 * @file NOT_Operator.cpp
 * @brief Defines the behavior of the NOT logical operator.
 * Returns inverted the input.
 */

#include "NOT_Operator.h"

// Second argument 'b' is ignored but requirred by interface.
// Decfault value b = false allows this case to match the same interface.
bool NOT_Operator :: evaluate( bool a, bool b) const {
    return !a ;
}

std::string NOT_Operator :: getName() const { return "NOT"; }

std::string NOT_Operator :: getExplanation() const {
    return "Invert the input.";
}                   