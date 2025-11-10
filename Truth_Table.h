/**
 * @class Truth_Table
 * @brief Generates and displays a truth table for a given Boolean_Expression.
 *
 * Automatically:
 *  - Detects which variables (A, B, C) appear in the expression
 *  - Generates all possible True/False combinations (2^n)
 *  - Evaluates each combination and prints the results in tabular form
 */

#ifndef TRUTH_TABLE_H
#define TRUTH_TABLE_H

#include "Boolean_Expression.h"
#include <string>
#include <vector>
#include <map>
using namespace std;


class Truth_Table {
  private:
    Boolean_Expression& expression;
    vector<char> used_variables;
    vector<map<char, bool>> input_combinations;

    void detectVariables();
    void generateCombinations();

  public:
    explicit Truth_Table(Boolean_Expression& expression);

    void displayTable(); // Display the truth table
};

#endif //TRUTH_TABLE_H
