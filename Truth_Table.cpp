
#include "Truth_Table.h"

/**
 * @file Truth_Table.cpp
 * @brief Builds and prints the truth table for a Boolean_Expression.
 * Flow:
 *   1) detectVariables(): find which of A/B/C actually appear
 *   2) generateCombinations(): create all 2^n input rows
 *   3) displayTable(): evaluate each row and print a formatted table
 */

#include <iostream>
#include <cmath>
#include <algorithm>
#include <set>
#include <iomanip>   // required for std::setw


using namespace std;

// Constructor : stores the expression and prepares the table
Truth_Table::Truth_Table(Boolean_Expression& expr): expression(expr) {
  detectVariables();
  generateCombinations();
}

/**
 * @brief Step 1 — Detect which variables (A, B, C) appear in the expression.
 * Implementation note:
 *  - We examine the postfix tokens because they’re already normalized.
 *  - A std::set<char> avoids duplicates and keeps A<B<C ordering.
 */
void Truth_Table::detectVariables() {

  used_variables.clear();

  // Use postfix for a reliable scan (tokens are already clean)
  vector<string> parts = expression.convertToPostfix();

  set<char> found; // Set to avoid duplicate entries

  for (const string& part : parts) {
    if (part == "A" || part == "B" || part == "C") {
      found.insert(part[0]); // 'A' / 'B' / 'C'
    }
  }

  // Copy into vector in sorted order (A → C)
  used_variables.assign(found.begin(), found.end());

}



/**
 * @brief Step 2 — Generate all input combinations for detected variables.
 *  - If n variables are used, there are 2^n rows.
 *  - We map bits of the row index i onto variables left→right (MSB→LSB).
 *    Example (A,B,C): i=5 (101b) → A=1, B=0, C=1.
 */
void Truth_Table::generateCombinations() {
  input_combinations.clear();
  const int n = used_variables.size();
  const int total = 1 << n; // 2^n combinations

  for (int i = 0; i < total; ++i) {
    map<char, bool> row;

    // Fill left→right: j=0 reads MSB, j=n-1 reads LSB
    for (int j = 0; j < n; ++j) {
      const bool value = (i >> (n - j - 1)) & 1;
      row[used_variables[j]] = value;
    }

    input_combinations.push_back(row);
  }
}

/**
 * @brief Step 3 — Print the truth table.
 * Columns:
 *   - One column per variable (A/B/C)
 *   - One column per intermediate step (labels from evaluateWithSteps())
 */
void Truth_Table::displayTable() {

  vector<string> postfixForm = expression.convertToPostfix();

  // Header: variable names
  for (char var : used_variables)
    cout << "|" << left << setw(5) << var;
  cout << "|";

  // Header: step labels (use the first row just to get the label names)
  auto testSteps = expression.evaluateWithSteps(postfixForm, input_combinations[0]).first;
  for (const auto& step : testSteps) {
    cout << left << setw(20) << step.first << "|";
  }
  cout << endl;

  // Separator row (simple fixed widths matching above)
  for (int i = 0; i < used_variables.size(); ++i)
    cout << "|-----";
  cout << "|";
  for (int i = 0; i < testSteps.size(); ++i)
    cout << "--------------------|";
  cout << endl;

  // Body: one row per input assignment
  for (const auto& values : input_combinations) {
    // Print A/B/C values
    for (char var : used_variables)
      cout << "|" << left << setw(5) << values.at(var);
    cout << "|";

    // Evaluate all steps for this row and print boolean results
    auto resultPair = expression.evaluateWithSteps(postfixForm, values);
    for (const auto& step : resultPair.first) {
      cout << left << setw(20) << step.second << "|";
    }
    cout << endl;
  }
}


