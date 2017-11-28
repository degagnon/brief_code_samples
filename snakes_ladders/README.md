# Snakes and Ladders Shortest-Path Problem

## Premise
This problem, obtained from [HackerRank](https://www.hackerrank.com/) as "The Quickest Way Up", presents the question: What is the minimum number of moves from square 1 to square 100 in a snakes-and-ladders game with arbitrary control over the die? 

It is known that the board will always be 100 squares in size, and the die can return 1, 2, 3, 4, 5, or 6 at your choosing. There will be no more than 15 snakes and 15 ladders, and no snakes or ladders will share any endpoints. If no path to square 100 exists, the code is to return the value "-1".

## Implementation
This problem can be modeled as a directed graph where each node represents a square on the game board and each edge represents a move. A move, in this scenario, includes a die roll and potentially a slide along a snake or ladder. The shortest path to square 100 can be found via breadth-first search.

To model the board, I implemented an adjacency list with a vector of vectors of integers. Each sub-vector corresponds to a square on the board, where the square's number and the sub-vector's index within the main vector are identical (a dummy sub-vector at index zero helps with index alignment). For example, `board[3]` is a vector that contains the numbers of all the squares accessible from position 3. Within that vector, `board[3][0]` and `board[3][1]` hold integers of accessible squares from position 3. `board[0]` is empty, as it does not correspond to any physical board position.

Where snakes or ladders are given with source and destination coordinates (`node1` and `node2`, respectively), the board is modified to account for the new pathways. First, the adjacencies of `node1` are removed, since this node will no longer be a starting position for any move. Then, the full adjacency list is checked such that any connection to `node1` is replaced with `node2`.

To apply breadth-first search, we start with only the first square in the horizon queue and assume that all other squares are infinitely far away. Here, "infinite" is considered equivalent to `INT_MAX`, the largest number in the integer data type. The first square's adjacencies are added to the horizon, and distances to each square are relaxed to correspond to the shortest distance found. The process ends when square 100 is added to the horizon or when the horizon becomes empty (that is, there are no more connected adjacencies to explore). If square 100 has been found, then its distance is returned. Otherwise, a distance of "-1" is returned, in accordance with the problem prompt.

## Further Discussion
For simplicity, I chose to separate the functions of board-building and adding the snakes and ladders. However, it could be a bit wasteful to build the board only to erase parts of it, requiring the program to check through each item of the adjacency list to make corrections every time a snake or ladder is added. If I were to rewrite the code, I might try to collect the snakes and ladders into their own `vector` of `pairs` and then build the board afterward, incorporating the snakes and ladders along the way.