/**
 * @class XOR_Operator
 * @brief Implements logical XOR operation.
 *
 * Returns true if exactly one of the inputs is true.
 */

#ifndef XOR_OPERATOR_H
#define XOR_OPERATOR_H

#include "Boolean_Operator.h"

class XOR_Operator : public Boolean_Operator{
public:
    bool evaluate(bool a, bool b = false) const override;
    std::string getName() const override;
    std::string getExplanation() const override;
};

#endif //XOR_OPERATOR_H