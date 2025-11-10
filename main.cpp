/**
 * @file main.cpp
 * @brief Entry point for the Boolean Truth Table Simulator.
 *
 * Steps:
 *  1. Ask user for a Boolean expression (A, B, C and operators).
 *  2. Parse and analyze it using Boolean_Expression.
 *  3. Display detected operators with their meanings.
 *  4. Generate and print the corresponding truth table.
 */

#include <iostream>
#include <string>
#include "Boolean_Expression.h"
#include "Truth_Table.h"

using namespace std;

int main()
{
    cout << "*** BOOLEAN TRUTH TABLE SIMULATOR ***\n" << endl;

    // Step 1 : Get user input
    cout << "Enter Boolean Expression (max 3 operators with 3 variables: A, B, C): \n> ";
    string user_expression;
    getline(cin, user_expression);

    // Step 2 : Create a Boolean_Expression object
    Boolean_Expression expr(user_expression);

    // Step 3 : Show detected operators and their explanations
    cout << "\nOperators Detected and Explained:\n";
    const auto& operators = expr.getOperators();   // NOTE: const reference, no copying

    for (const auto& op : operators) // op is a unique_ptr<...>&
    {
        cout << "- " << op->getName() << ": " << op->getExplanation() << endl;
    }

    // Step 4 : Generate and Display the truth table
    cout << "\nGenerating Truth Table...\n" << endl;
    Truth_Table table(expr);
    table.displayTable();

    return 0;
}