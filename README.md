# Boolean Truth Table Simulator

A **C++ console application** that parses and evaluates Boolean logic expressions using variables `A`, `B`, and `C`, and automatically generates a **truth table** with detailed step-by-step evaluation.

---

## How to Build and Run (CLion or CMake)

1. Open the project in **CLion** (or any IDE that supports CMake).  
2. Click **Build → Build Project**.  
3. Run `main.cpp`.  
4. When prompted, enter a Boolean expression (e.g., `A AND B`, `(A OR B) AND (NOT C)`).  
5. The program will generate and display a truth table showing all input combinations and intermediate logic steps.

---

## Example Expressions to Try

| # | Expression | Description |
|---|-------------|-------------|
| 1 | `A AND B` | Simple AND gate |
| 2 | `A OR B` | Simple OR gate |
| 3 | `A AND (B OR C)` | Nested operations with parentheses |
| 4 | `NOT A` | Unary NOT gate |
| 5 | `(A AND B) OR (NOT C)` | Combined logic expression |

---

## Design Overview

### 1. Boolean_Expression
- Converts infix expressions to postfix (Reverse Polish Notation)  
- Evaluates expressions **step-by-step** using stack-based evaluation  
- Supports operators: **AND, OR, NOT, NAND, NOR, XOR**  
- Handles parentheses correctly for operator precedence  

---

### 2. Truth_Table
- Detects which variables (`A`, `B`, `C`) are actually used  
- Generates all **binary input combinations** (2ⁿ)  
- Displays a **formatted truth table** with aligned columns  
- Uses `evaluateWithSteps()` to show all **intermediate logic results**

---

### 3. Operator Classes  
(AND_Operator, OR_Operator, NOT_Operator, NAND_Operator, NOR_Operator, XOR_Operator)
- Each operator class inherits from the abstract base class **Boolean_Operator**  
- Encapsulates its own logic gate behavior via overridden `evaluate()` methods  
- Designed with **polymorphism** for easy extension (e.g., adding new operators like IMPLIES or XNOR)

---

## How It Works (Step-by-Step)

1. **Tokenization**  
   The expression string is split into tokens (variables, operators, and parentheses).  
   Example: (A AND B) OR (NOT C)
             → {"(", "A", "AND", "B", ")", "OR", "(", "NOT", "C", ")"}

2. **Conversion to Postfix**  
Uses the **Shunting Yard algorithm** to handle operator precedence and parentheses.  
Example: {"A", "B", "AND", "C", "NOT", "OR"}

3. **Evaluation with Stacks**  
Evaluates the postfix expression using a value stack and a label stack.  
- Each step is labeled (e.g., `NOT C`, `(A AND B)`, `(A AND B) OR (NOT C)`)  
- These step labels become the truth table column headings.

4. **Truth Table Generation**  
- Generates all possible combinations of A, B, and C (2ⁿ rows).  
- Evaluates the expression for each combination.  
- Displays each intermediate step and the final result in a clean, aligned table.

---
## Example Output (Simplified)

(A AND B) OR (NOT C)

|A    |B    |C    |(A AND B)           |NOT C               |((A AND B) OR NOT C)|
|-----|-----|-----|--------------------|--------------------|--------------------|
|0    |0    |0    |0                   |1                   |1                   |
|0    |0    |1    |0                   |0                   |0                   |
|0    |1    |0    |0                   |1                   |1                   |
|0    |1    |1    |0                   |0                   |0                   |
|1    |0    |0    |0                   |1                   |1                   |
|1    |0    |1    |0                   |0                   |0                   |
|1    |1    |0    |1                   |1                   |1                   |
|1    |1    |1    |1                   |0                   |1                   |

---

## Key Features
- Uses **Object-Oriented Design** with inheritance and polymorphism  
- Implements **Shunting Yard algorithm** for reliable parsing  
- Uses **smart pointers (`std::unique_ptr`)** for automatic memory management  
- Produces **aligned and readable truth tables** with `std::setw()`  
- Extensible — new logical operators can be added easily
  
---

## Future Improvements
- Support more variables dynamically (A–Z)  
- Add additional operators: XNOR, IMPLIES, etc.  
- Allow saving truth tables to a `.txt` file  
- GUI or web-based version for easier visualization

---

