/**
 * @file AND_Operator.cpp
 * @brief Defines the behavior of the AND logical operator.
 * Returns true only if both inputs are true.
 */

#include "AND_Operator.h"

bool AND_Operator :: evaluate( bool a, bool b) const {
  return a && b;
}

std::string AND_Operator :: getName() const { return "AND"; }

std::string AND_Operator :: getExplanation() const {
  return "True only if both inputs are true.";
}