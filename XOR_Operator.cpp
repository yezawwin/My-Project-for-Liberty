/**
 * @file XOR_Operator.cpp
 * @brief Defines the behavior of the XOR logical operator.
 * Returns if exactly one of the inputs is true.
 */

#include "XOR_Operator.h"

bool XOR_Operator :: evaluate( bool a, bool b) const {
    return a != b ;
}

std::string XOR_Operator :: getName() const { return "XOR"; }

std::string XOR_Operator :: getExplanation() const {
    return "True if exactly one of the inputs is true.";
}