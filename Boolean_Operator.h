/**
 * @class Boolean_Operator
 * @brief Abstract base class defining the interface for all Boolean logic operators.
 *
 * Each operator must define:
 *  - evaluate(a,b): how it computes its logical result
 *  - getName(): the operator’s display name
 *  - getExplanation(): short description for user help
 */

#ifndef BOOLEAN_OPERATOR_H
#define BOOLEAN_OPERATOR_H

#include <string>

class Boolean_Operator{

  public:

    // Evaluate logic with one or two inputs
    // Default value b = false allows this to work for both binary (AND, Or, etc.)
    // and unary (NOT) operators using the same function signature
    virtual bool evaluate(bool a, bool b = false) const = 0;

    // Get the name of the operator (e.g., AND, OR, etc.)
    virtual std::string getName() const = 0;

    // Get a short explanantion of the operator
    virtual std::string getExplanation() const = 0;

};


#endif //BOOLEAN_OPERATOR_H
