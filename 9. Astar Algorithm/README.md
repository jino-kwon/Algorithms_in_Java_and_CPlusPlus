# 9. A* Algorithm (8-Puzzle Problem)

**Program Specs:**

Solve the 8-puzzle problem using A* search.
The 8 puzzle problem was invented by Noyes Palmer Chapman in the 1870s. It is played on a 3-by-3 grid with 8 square blocks labeled 1 through 8 and a blank square (marked as zero). The goal is to find the minimum path/steps needed to rearrange the blocks so that they are in order (as indicated in the given 'goal' state). You can slide blocks horizontally or vertically (but NOT diagonally) into the blank square.

The three A* functions to be used in this program are:

1. g(n) = # of moves from initial state to node/state n
2. h*(n) = the total distance for all tiles to move from node/state n to the goal state.
3. f*(n) = g(n) + h*(n)
