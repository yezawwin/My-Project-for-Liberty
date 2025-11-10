/**
 * @brief Splits the original expression into tokens (variables and operators).
 * Example: "(A AND B) XOR NOT C" → ["(", "A", "AND", "B", ")", "XOR", "NOT", "C"]
 */

 /**
  * @brief Converts infix expression into postfix (Reverse Polish Notation)
  *        for easy evaluation using stack operations.
  * Example: ["A", "AND", "B", "XOR", "NOT", "C"] → ["A", "B", "AND", "C", "NOT", "XOR"]
  */

  /**
   * @brief Evaluates the postfix expression for given truth values.
   * @return pair of (steps, finalResult) where steps are intermediate calculations.
   */

#include "Boolean_Expression.h"

#include <iostream>

#include "AND_Operator.h"
#include "OR_Operator.h"
#include "NOT_Operator.h"
#include "NAND_Operator.h"
#include "NOR_Operator.h"
#include "XOR_Operator.h"
#include <map>

using namespace std;

// --------------------------- Precedence Table -------------------------------
// Highest number = higher precedence. NOT binds strongest, then AND/NAND,
// then OR/NOR/XOR. This table is consulted during infix→postfix conversion.
map<string, int> logic_priority = {
    {"NOT", 3},
    {"AND", 2}, {"NAND", 2},
    {"OR", 1}, {"NOR", 1}, {"XOR", 1},
};

// Constructor
Boolean_Expression::Boolean_Expression(const string& expr): original_expression(expr) {
  splitExpression();
  findOperators();
}

/**
 * @brief Split the original string into tokens.
 * Rules:
 *  - Variables are single letters: A, B, C
 *  - Operators are words: AND, OR, NOT, XOR, NAND, NOR
 *  - Parentheses are single-character tokens: '(' and ')'
 *  - Whitespace separates tokens but is otherwise ignored
 *
 * Example:
 *   "(A AND B) XOR NOT C"
 *   → ["(", "A", "AND", "B", ")", "XOR", "NOT", "C"]
 */
void Boolean_Expression::splitExpression() {

  expression_parts.clear();
  string part; 

  // Scan once across the raw expression
  for (int i = 0; i < original_expression.length(); ++i) {
    char ch = original_expression[i];

    if (isspace(ch)) {
      // Push any word we’ve collected so far
      if (!part.empty()) {
        expression_parts.push_back(part);
        part.clear();
      }
    }
    else if (ch == '(' || ch == ')') {
      // Push any pending token, then push the parenthesis as its own token
      if (!part.empty()) {
        expression_parts.push_back(part);
        part.clear();
      }
      expression_parts.emplace_back(1, ch); // Add bracket as a separate token
    }
    else {
      // Build up a word token (e.g., AND/OR/NOT or variable letter)
      part += ch;
    }
  }

  // Append the final token if the loop ended mid-word
  if (!part.empty()) {
    expression_parts.push_back(part);
  }
}

/**
 * @brief Identify which operator classes to list as “detected”.
 * This doesn’t affect evaluation; it’s for user-facing explanations only.
 */
void Boolean_Expression:: findOperators() {
  operators_found.clear();

  for(const string& piece : expression_parts) {
    if (piece == "AND") {
      operators_found.push_back(std::make_unique <AND_Operator>());
    }
    else if (piece == "OR") {
      operators_found.push_back(std::make_unique <OR_Operator>());
    }
    else if (piece == "NOT") {
      operators_found.push_back(std::make_unique <NOT_Operator>());
    }
    else if (piece == "NAND") {
      operators_found.push_back(std::make_unique <NAND_Operator>());
    }
    else if (piece == "NOR") {
      operators_found.push_back(std::make_unique <NOR_Operator>());
    }
    else if (piece == "XOR") {
      operators_found.push_back(std::make_unique <XOR_Operator>());
    }
  }
}

/**
 * @brief Convert infix tokens to postfix.
 *
 * Algorithm:
 *   - For each token:
 *       - If variable → output queue
 *       - If operator → pop higher/equal precedence operators to output, then push current
 *       - If "(" → push to stack
 *       - If ")" → pop until "("
 *   - After scanning → pop any remaining stack operators to output
 */

vector<string> Boolean_Expression:: convertToPostfix() {
  
  vector<string> postfix_output; 
  vector<string> logic_stack; // operator stack

  for (const string& symbol : expression_parts) {
    // Case 1: variable (operands go straight to output)
    if (symbol == "A" || symbol == "B" || symbol == "C") {
      postfix_output.push_back(symbol);
    }
    // Case 2: known operator (consult precedence table)
    else if (logic_priority.find(symbol) != logic_priority.end()) {
        // Pop stronger or equal-precedence operators before pushing current
      while(!logic_stack.empty() && logic_stack.back() != "(" &&
             logic_priority[symbol] <= logic_priority[logic_stack.back()]) {
        postfix_output.push_back(logic_stack.back());
        logic_stack.pop_back();
      }
      logic_stack.push_back(symbol); // Push current operator
    }
    // Case 3: open parenthesis → push
    else if (symbol == "("){
      logic_stack.push_back(symbol);
    }
    // Case 4: close parenthesis → drain until matching "("
    else if (symbol == ")"){
      while(!logic_stack.empty() && logic_stack.back() != "("){
        postfix_output.push_back(logic_stack.back());
        logic_stack.pop_back();
      }
      if(!logic_stack.empty()){
        logic_stack.pop_back(); // Remove "("
      }
    }
    // Case 5: anything else is unexpected (typo or unknown token)
    else
    {
      std::cout << "Undefined operator " << symbol << std::endl;
    }
  }

  // After the loop, move remaining operators to output
  while (!logic_stack.empty()){
    postfix_output.push_back(logic_stack.back());
    logic_stack.pop_back();
  }

  return postfix_output;
}

/**
 * @brief Evaluate a postfix sequence for a given assignment of A/B/C
 *        while capturing readable step labels for the truth table.
 *
 * Stacks:
 *   - eval_stack   : holds boolean values during evaluation
 *   - label_stack  : mirrors eval_stack with human-readable labels
 *                    (e.g., "NOT C", "(A AND B)")
 *
 * Return:
 *   - pair of ( vector of (label, value) for each intermediate step, final result )
 *   - The steps drive the truth-table “explanation” columns.
 */
pair<vector<pair<string, bool>>, bool>
Boolean_Expression::evaluateWithSteps(const vector<string>& postfix, const map<char, bool>& input_values) {
  vector<bool> eval_stack; // boolean values (operands & results)
  vector<string> label_stack; // matching labels for pretty output
  vector<pair<string, bool>> steps; // ordered (label, result)

  // Example:
  // postfix: ["A", "B", "C", "NOT", "XOR", "AND"]
  // inputs : {A:1, B:0, C:1}
  for (const string& piece : postfix) {
    // Operand → push its boolean value + its label ("A"/"B"/"C")
    if (piece == "A" || piece == "B" || piece == "C") {
      eval_stack.push_back(input_values.at(piece[0])); // piece[0] is 'A'/'B'/'C'
      label_stack.push_back(piece);
    }
    // Unary operator: NOT
    else if (piece == "NOT") {
      // Pop one value, compute, push result; keep label in sync
      bool a = eval_stack.back(); eval_stack.pop_back();
      string aLabel = label_stack.back(); label_stack.pop_back();

      bool result = !a;
      string label = "NOT " + aLabel;
      steps.emplace_back(label, result);

      eval_stack.push_back(result);
      label_stack.push_back(label);
    }
    // Binary operators: AND/OR/XOR/NAND/NOR
    else {
      // Pop right then left (stack order), compute, label as "(left op right)"
      bool b = eval_stack.back(); eval_stack.pop_back();
      bool a = eval_stack.back(); eval_stack.pop_back();

      string bLabel = label_stack.back(); label_stack.pop_back();
      string aLabel = label_stack.back(); label_stack.pop_back();

      string label = "(" + aLabel + " " + piece + " " + bLabel + ")";
      bool result = false;

      if (piece == "AND") result = a && b;
      else if (piece == "OR") result = a || b;
      else if (piece == "XOR") result = a != b;
      else if (piece == "NAND") result = !(a && b);
      else if (piece == "NOR") result = !(a || b);

      steps.emplace_back(label, result);
      eval_stack.push_back(result);
      label_stack.push_back(label);
    }
  }

  // The remaining stack top is the final result for this input assignment
  return { steps, eval_stack.back() };
}

/**
 * @brief Expose the detected operators (for UI explanation).
 * Returns a const reference so ownership stays within the expression object.
 */
const std::vector<std::unique_ptr<Boolean_Operator>>&
Boolean_Expression::getOperators() const {
    return operators_found;
}

/**
 * @brief Original, unmodified user expression (for display/backreference)
 */
string Boolean_Expression:: getOriginalExpression() const{
  return original_expression;
}
