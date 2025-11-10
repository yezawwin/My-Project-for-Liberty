/**
 * @class NOT_Operator
 * @brief Implements logical NOT operation.
 *
 * Returns inverted input..
 */

#ifndef NOT_OPERATOR_H
#define NOT_OPERATOR_H

#include "Boolean_Operator.h"

class NOT_Operator : public Boolean_Operator{
public:
    bool evaluate(bool a, bool b = false) const override;
    std::string getName() const override;
    std::string getExplanation() const override;
};

#endif //NOT_OPERATOR_H