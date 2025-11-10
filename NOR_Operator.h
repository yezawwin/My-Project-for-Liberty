/**
 * @class NOR_Operator
 * @brief Implements logical NOR operation.
 *
 * Returns true only if both inputs are false.
 */

#ifndef NOR_OPERATOR_H
#define NOR_OPERATOR_H

#include "Boolean_Operator.h"

class NOR_Operator : public Boolean_Operator{
public:
    bool evaluate(bool a, bool b = false) const override;
    std::string getName() const override;
    std::string getExplanation() const override;
};

#endif //NOR_OPERATOR_H