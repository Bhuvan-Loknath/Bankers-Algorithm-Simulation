# Bankers-Algorithm-Simulation

This repository contains an implementation of the Banker's Algorithm, which is a deadlock-avoidance technique used in operating systems to allocate resources safely among several processes.

## Files in the Repository

- `banker_algorithm.c` - The main C program implementing the Banker's Algorithm.
- `maximum.txt` - A text file containing the maximum resource requests for each customer.
- `Makefile` - A Makefile to compile `banker_algorithm.c`.
- `README.md` - Documentation for this project.

---

## Compilation, Usage, and Cleanup

The following code snippet will **compile**, **run**, and **clean up** the project:

```bash
# 1. Compile the code
make

# 2. Run the banker_algorithm with resource instances
./banker_algorithm <R1> <R2> <R3> <R4>

# Example:
./banker_algorithm 10 5 7 8

# 3. Enter commands to request or release resources:
# - 'RQ cust_num R1 R2 R3 R4' to request resources
# - 'RL cust_num R1 R2 R3 R4' to release resources
# - '*' to display the current values of the data structures
# - 'exit' to quit

# 4. Clean up the compiled files
make clean
