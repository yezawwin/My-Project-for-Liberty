/**
 * @file NAND_Operator.cpp
 * @brief Defines the behavior of the NAND logical operator.
 * Returns true unless both inputs are true.
 */

#include "NAND_Operator.h"

bool NAND_Operator :: evaluate( bool a, bool b) const {
    return !(a && b);
}

std::string NAND_Operator :: getName() const { return "NAND"; }

std::string NAND_Operator :: getExplanation() const {
    return "True unless both inputs are true.";
}