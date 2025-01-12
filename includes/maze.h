#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <string>
#include "stack.h"
#include <thread>

using namespace std;

class Maze
{
private:
  Cell current_cell, exit_cell, entry_cell;
  char exitMarker = 'e', entryMarker = 'm', visited = '.', passage = '0', wall = '1';
  int num_cols, num_rows;
  Stack<Cell> moves; // mazeStack
  vector<string> maze;

public:
  Maze(vector<string> maze, pair<int, int> pos_entry, pair<int, int> pos_exit, int num_cols, int num_rows);
  Maze() : maze({}) {};
  ~Maze();
  vector<string> getMaze();
  void exitMaze();
  bool findPath(Cell current_cell);
  void printMazeFile();
  void printMaze(vector<vector<bool>> &maze_bool, Cell current_cell, bool is_last);
  void printMazeLoop(const Stack<Cell> moves);
};

Maze::Maze(vector<string> maze, pair<int, int> pos_entry, pair<int, int> pos_exit, int num_cols, int num_rows)
{
  this->maze = maze;
  this->current_cell = pos_entry;
  this->entry_cell = pos_entry;
  this->exit_cell = pos_exit;
  this->num_cols = num_cols;
  this->num_rows = num_rows;
}

Maze::~Maze()
{
}

vector<string> Maze::getMaze()
{
  return maze;
}

void Maze::printMazeFile()
{
  for (const auto &linha : maze)
  {
    for (char character : linha)
    {
      cout << character;
    }
    cout << endl;
  }
}
bool Maze::findPath(Cell current_cell)
{
  vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
  if (maze[current_cell.getY()][current_cell.getX()] == exitMarker)
  {
    return true;
  }
  maze[current_cell.getY()][current_cell.getX()] = visited;
  for (const auto &direction : directions)
  {
    pair<int, int> new_cell;
    int new_line = current_cell.getY() + direction.first;
    int new_column = current_cell.getX() + direction.second;

    bool in_maze = (0 <= new_line && new_line < num_cols) && (0 <= new_column && new_column < num_rows);
    if (!in_maze)
      continue;
    bool is_path = (maze[new_line][new_column] == passage) || (maze[new_line][new_column] == exitMarker);
    bool is_visited = maze[new_line][new_column] == visited;
    new_cell = {new_line, new_column};

    // cout<< "current_cell: " << current_cell.getY() <<", " << current_cell.getX() << " ---- " <<maze[current_cell.getY()][current_cell.getX()] << endl;
    // cout << "posicao em analise: " << new_line << ", " << new_column << " ---- " << maze[new_line][new_column] << endl;

    if (is_path && !is_visited)
    {
      // maze[current_cell.getY()][current_cell.getX()] = visited;
      Cell next_cell(new_column, new_line);
      moves.push(next_cell);
      // cout << "entrou no if: " << next_cell.getY() << ", " << next_cell.getX() << endl;

      if (findPath(next_cell))
      {
        return true;
      }

      moves.pop();
    }
  }
  return false;
}

void Maze::printMaze(vector<vector<bool>> &maze_bool, Cell current_cell, bool is_last)
{
  char wall_print = '*', passage_print = ' ', visited_print = '.', mouse_print = 'o', try_error_print = 'x';
  for (int row = 0; row < num_rows; row++)
  {
    for (int col = 0; col < num_cols; col++)
    {
      if (row == current_cell.getY() && col == current_cell.getX())
      {
        cout << mouse_print;
        maze_bool[row][col] = true;
      }
      else if (maze[row][col] == wall)
      {
        cout << wall_print;
      }
      else if (maze[row][col] == passage)
      {
        cout << passage_print;
      }
      else if (maze_bool[row][col] == true)
      {
        cout << visited_print;
      }
      else if (maze[row][col] == visited && is_last)
      {
        cout << try_error_print;
      }
      else if (maze[row][col] == visited)
      {
        cout << passage_print;
      }
      else
      {
        cout << maze[row][col];
      }
    }
    cout << endl;
  }
}
void Maze::printMazeLoop(Stack<Cell> path)
{
  vector<vector<bool>> maze_bool(num_rows, vector<bool>(num_cols, false));
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
  cout << entry_cell << endl;
  printMaze(maze_bool, entry_cell, false);
  this_thread::sleep_for(chrono::seconds(1));


  while (!path.isEmpty())
  {
    #ifdef _WIN32
    system("cls");
    #else
      system("clear");
    #endif
    cout << path.top() << endl;
    bool is_last = path.get_size() == 1;
    printMaze(maze_bool, path.top(), is_last);
    path.pop();
    this_thread::sleep_for(chrono::seconds(1));
  }
};

void Maze::exitMaze()
{
  Stack<Cell> reversed_moves;
  if (findPath(current_cell))
  {
    while (!moves.isEmpty())
    {
      reversed_moves.push(moves.top());
      moves.pop();
    }
    moves = reversed_moves;
    printMazeLoop(reversed_moves);
    reversed_moves.print();
  }
  else
  {
    cout << "Não ha caminho :(" << endl;
  }
}

#endif
