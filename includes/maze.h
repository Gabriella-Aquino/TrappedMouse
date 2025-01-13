#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <string>
#include "stack.h"
#include <thread>
#include <sstream>
#include <chrono>

using namespace std;
using namespace chrono;

class Maze
{
private:
  Cell current_cell, exit_cell, entry_cell;
  char exit_marker = 'e', entry_marker = 'm', visited = '.', passage = '0', wall = '1';
  int num_cols, num_rows;
  Stack<Cell> moves; // mazeStack
  vector<string> maze;
  stringstream log;
  time_point<high_resolution_clock> start_time;
  bool is_timing = false; 

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
  void logMenssage(const string& message);
  void printLog();
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

void Maze:: logMenssage(const string& message){
  log << message << endl;
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
  if (!is_timing) {
    start_time = chrono::high_resolution_clock::now();
    is_timing = true;
  }
  vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
  if (maze[current_cell.getY()][current_cell.getX()] == exit_marker)
  {
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end_time - start_time);
    logMenssage("\nTempo de execução do findPath: " + to_string(duration.count()) +  " ms\nACHOU!");
    return true;
  }
  for (const auto &direction : directions)
  {
    pair<int, int> new_cell;
    int new_line = current_cell.getY() + direction.first;
    int new_column = current_cell.getX() + direction.second;

    logMenssage("\nposicao atual: " + to_string(current_cell.getY()) + ", " + to_string(current_cell.getX()) + " ---- " + string(1, maze[current_cell.getY()][current_cell.getX()]));
    logMenssage("posicao em analise:" + to_string(new_line) + ", " + to_string(new_column) + " ---- " + string(1, maze[new_line][new_column]));
    bool in_maze = (0 <= new_line && new_line < num_cols) && (0 <= new_column && new_column < num_rows);
    if (!in_maze)
      continue;
    bool is_path = (maze[new_line][new_column] == passage) || (maze[new_line][new_column] == exit_marker);
    bool is_visited = maze[new_line][new_column] == visited;
    new_cell = {new_line, new_column};

    if (is_path && !is_visited)
    {
      maze[current_cell.getY()][current_cell.getX()] = visited;
      Cell next_cell(new_column, new_line);
      moves.push(next_cell);
      logMenssage("entrou no if: " + to_string(next_cell.getY()) + ", " + to_string(next_cell.getX()));


      if (findPath(next_cell))
      {
        return true;
      }

      moves.pop();
    }
  }
  return false;
}

void Maze::printLog(){
  cout << "----------------" << endl;
  cout << "DEBUG FIND PATH:" << endl;
  cout << "----------------" << endl;
  cout << log.str() << endl;
  moves.print();
}

void Maze::printMaze(vector<vector<bool>> &maze_bool, Cell current_cell, bool is_last)
{
  char wall_print = '|', passage_print = ' ', visited_print = '.', mouse_print = 'o', try_error_print = 'x', exit_print = '=';
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
      else if(maze[row][col] == exit_marker)
      {
        cout << exit_print;
      }
    }
    cout << endl;
  }
}
void Maze::printMazeLoop(Stack<Cell> path)
{
  vector<vector<bool>> maze_bool(num_rows, vector<bool>(num_cols, false));
  double animation_time = 5.0 / path.get_size();
  animation_time = max(animation_time, 0.1);
  animation_time = min(animation_time, 0.5);
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
  cout << entry_cell << endl;
  printMaze(maze_bool, entry_cell, false);
  this_thread::sleep_for(chrono::milliseconds(static_cast<int>(animation_time * 1000)));


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
    this_thread::sleep_for(chrono::milliseconds(static_cast<int>(animation_time * 1000)));
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