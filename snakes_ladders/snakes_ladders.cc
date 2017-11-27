// HackerRank Puzzle "The Quickest Way Up"
// Based on a Snakes and Ladders game,
// given the endpoints of the snakes and ladders,
// find the fewest moves to win the game
// (assuming arbitrary control over the die).
// Board is 10 x 10, numbered 1 to 100.

#include <climits>  // INT_MAX
#include <deque>  // used in BFS node queue
#include <iostream>
#include <vector>

// Using fstream for inputs/outputs in local code dev,
// iostream for actual code submission.
#include <fstream>
#include <string>

// For good coding practice, avoiding namespace std.
// using namespace std;

void AddEdge(std::vector<std::vector<int>>& graph, int node1, int node2) {
  graph[node1].push_back(node2);
}

void AddHop(std::vector<std::vector<int>>& graph, int node1, int node2) {
  // Add a snake or ladder.
  // This is not as simple as adding an edge, since that would improperly
  // represent what counts as a "move" in the game path.

  // The start node will no longer be the start of any moves.
  while (!graph[node1].empty()) {
    graph[node1].pop_back();
  }

  // Replace any edges pointing to the start node
  // with edges that point to the end node.
  // The method here has O(n*m) complexity for every AddHop call,
  // where n = number of squares and m = potential moves per turn,
  // which could be problematic on large boards but is tolerable
  // for tests of the scale given in the problem description.
  // For this problem, n = 100 for a 100-square board,
  // and m = 6 for a 6-sided die.
  for (size_t i = 1; i <= 100; ++i) {
    for (size_t j = 0; j < graph[i].size(); ++j) {
      if (graph[i][j] == node1) {
        graph[i][j] = node2;
      }
    }
  }
}

std::vector<std::vector<int>> BuildBasicBoard() {
  int kBoardSize = 100;
  std::vector<int> empty_node;
  // Using kBoardSize+1 to create dummy node 0 and use 1-based indexing.
  std::vector<std::vector<int>> board(kBoardSize + 1, empty_node);
  for (int position = 1; position <= 100; ++position) {
    for (int die = 1; die <= 6 && position + die <= 100; ++die) {
      AddEdge(board, position, position + die);
    }
  }
  return board;
}

void PrintGraph(const std::vector<std::vector<int>>& graph) {
  for (size_t i = 0; i < graph.size(); ++i) {
    std::cout << "Node " << i << ": ";
    for (size_t j = 0; j < graph[i].size(); ++j) {
      std::cout << graph[i][j] << " ";
    }
    std::cout << "\n";
  }
}

void PrintQueue(const std::deque<int>& queue) {
  std::cout << "Queue contents: ";
  for (const int& item : queue) {
    std::cout << item << " ";
  }
  std::cout << "\n";
}

int BFS(const std::vector<std::vector<int>>& graph, int start, int end) {
  std::vector<int> distance(graph.size(), INT_MAX);
  std::vector<int> parent(graph.size(), 0);
  int current_node;
  int next_node;
  std::deque<int> horizon(1, start);  // Load first node onto BFS horizon
  distance[start] = 0;
  parent[start] = 0;
  bool end_found = false;
  while (!horizon.empty() && !end_found) {
    current_node = horizon.front();
    std::cout << "Current node " << current_node << " with queue contents ";
    PrintQueue(horizon);
    for (size_t adjacency_index = 0;
         adjacency_index < graph[current_node].size(); ++adjacency_index) {
      next_node = graph[current_node][adjacency_index];
      if (distance[next_node] > distance[current_node] + 1) {
        distance[next_node] = distance[current_node] + 1;
        parent[next_node] = current_node;
        horizon.push_back(next_node);  // Add next node onto horizon
        if (next_node == end) {
          end_found = true;
        }
      }
    }
    // std::cout << "Current node's distance is " << distance[current_node] << ".\n";
    horizon.pop_front();
  }
  if (distance[end] == INT_MAX) {
    // Return value for end-not-found as -1.
    distance[end] = -1;
  }
  return distance[end];
}

int main() {
  /* Enter your code here. Read input from STDIN. Print output to STDOUT */
  // std::string file_name = "input00.txt";
  // std::string file_name = "custom_input.txt";
  std::string file_name = "input03.txt";
  std::ifstream cin_file(file_name);

  int num_tests;
  cin_file >> num_tests;
  int num_ladders;
  int num_snakes;
  int edge_start;
  int edge_end;
  for (int test = 0; test < num_tests; ++test) {
    std::vector<std::vector<int>> board = BuildBasicBoard();
    cin_file >> num_ladders;
    for (int line = 0; line < num_ladders; ++line) {
      cin_file >> edge_start >> edge_end;
      AddHop(board, edge_start, edge_end);
    }
    cin_file >> num_snakes;
    for (int line = 0; line < num_snakes; ++line) {
      cin_file >> edge_start >> edge_end;
      AddHop(board, edge_start, edge_end);
    }
    // PrintGraph(board);
    // Solution will be length of breadth-first search from square 1 to 100.
    int num_steps = BFS(board, 1, 100);
    std::cout << "Number of steps is ";
    std::cout << num_steps << '\n';
  }

  return 0;
}