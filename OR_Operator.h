/**
 * @class OR_Operator
 * @brief Implements logical OR operation.
 *
 * Returns true only if at least one input is true.
 */

#ifndef OR_OPERATOR_H
#define OR_OPERATOR_H

#include "Boolean_Operator.h"

class OR_Operator : public Boolean_Operator{
public:
    bool evaluate(bool a, bool b = false) const override;
    std::string getName() const override;
    std::string getExplanation() const override;
};

#endif //OR_OPERATOR_H