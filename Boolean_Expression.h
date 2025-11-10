/**
 * @class Boolean_Expression
 * @brief Handles parsing and evaluation of Boolean logic expressions.
 *
 * Responsible for:
 *  - Splitting user input into tokens (variables and operators)
 *  - Converting infix expressions to postfix form (for safe evaluation)
 *  - Evaluating postfix expressions with step-by-step tracking
 */

#ifndef BOOLEAN_EXPRESSION_H
#define BOOLEAN_EXPRESSION_H

#include <string>
#include <map>
#include <vector>
#include <memory>
#include "Boolean_Operator.h"

using namespace std;

class Boolean_Expression {
private:
  string original_expression;           // Variable to store original user input
  vector<string> expression_parts;      // Variable to store splited parts of expression (symbols)
  std::vector<std::unique_ptr<Boolean_Operator>> operators_found; // Variable to store detected operators

public:
  // Constructor
  explicit Boolean_Expression(const string& expr);

  // Break expression into words
  void splitExpression();

  // Identify all boolean Operators used
  void findOperators();

  // Convert infix into postfix
  vector<string> convertToPostfix();

  // Evaluate postfix with steps
  pair<std::vector<std::pair<std::string, bool>>, bool>
  evaluateWithSteps(const std::vector<std::string>& postfix, const std::map<char, bool>& input_values);

  // Return list of operators
  const std::vector<std::unique_ptr<Boolean_Operator>>& getOperators() const;


  // Get the original expression string
  string getOriginalExpression() const;
};

#endif //BOOLEAN_EXPRESSION_H
