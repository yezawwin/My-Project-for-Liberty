/**
 * @class NAND_Operator
 * @brief Implements logical NAND operation.
 *
 * Returns true unless both inputs are true.
 */

#ifndef NAND_OPERATOR_H
#define NAND_OPERATOR_H

#include "Boolean_Operator.h"

class NAND_Operator : public Boolean_Operator{
public:
    bool evaluate(bool a, bool b = false) const override;
    std::string getName() const override;
    std::string getExplanation() const override;
};

#endif //NAND_OPERATOR_H