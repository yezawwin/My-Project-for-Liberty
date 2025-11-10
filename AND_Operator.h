/**
 * @class AND_Operator
 * @brief Implements logical AND operation.
 *
 * Returns true only if both inputs are true.
 */

#ifndef AND_OPERATOR_H
#define AND_OPERATOR_H

#include "Boolean_Operator.h"

class AND_Operator : public Boolean_Operator{
    public:
      bool evaluate(bool a, bool b = false) const override;
      std::string getName() const override;
      std::string getExplanation() const override;
};

#endif //AND_OPERATOR_H
