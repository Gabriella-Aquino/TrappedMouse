#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <string>
#include <tuple>
#include "stack.h"

using namespace std;

class Maze
{
private:
  Cell current_cell, exit_cell, entry_cell;
  char exitMarker = 'e', entryMarker = 'm', visited = '.', passage ='0', wall = '1';
  int num_cols, num_rows;
  Stack<Cell> moves; //mazeStack
  vector<string> maze;
  // vector<pair<int, int>> visited;

public:
  Maze(vector<string> maze, pair<int, int>pos_entry, pair<int, int> pos_exit, int num_cols, int num_rows);
  Maze() : maze({}) {};
  ~Maze();
  vector<string> getMaze();
  void exitMaze();
  bool findPath(Cell current_cell);
  void printMazeFile();
};

Maze::Maze(vector<string> maze, pair<int, int>pos_entry, pair<int, int> pos_exit, int num_cols, int num_rows)
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

vector<string> Maze::getMaze(){
  return maze;
}

void Maze::printMazeFile(){
  cout << "MAZE:" << endl;
  pair<int, int> exit;
  for (const auto &linha : maze)
    {
      for (char character : linha)
      {
        cout << character;
      }
      cout << endl;
    }
}
bool Maze::findPath(Cell current_cell){
  vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
  if (maze[current_cell.getY()][current_cell.getX()] == exitMarker)
  {
    return true;
  }
   
  for(const auto& direction: directions){
    pair<int, int> new_cell;
    int new_line = current_cell.getY() + direction.first;
    int new_column = current_cell.getX() + direction.second;

    bool in_maze = (0 <= new_line && new_line <  num_cols) && (0 <= new_column && new_column < num_rows);
    if(!in_maze) continue;
    bool is_path = (maze[new_line][new_column] == passage) || (maze[new_line][new_column] == exitMarker);
    bool is_visited = maze[new_line][new_column] == visited;
    new_cell = {new_line, new_column};

    cout<< "current_cell: " << current_cell.getY() <<", " << current_cell.getX() << " ---- " <<maze[current_cell.getY()][current_cell.getX()] << endl;
    cout << "posicao em analise: " << new_line << ", " << new_column << " ---- " << maze[new_line][new_column] << endl;

    if(is_path && !is_visited){
      maze[current_cell.getY()][current_cell.getX()] = visited;
      Cell next_cell(new_column, new_line);
      moves.push(next_cell);
      cout << "entrou no if: " << next_cell.getY() << ", " << next_cell.getX() << endl;

      if(findPath(next_cell)){
        return true;
      }

      moves.pop();
    }
  }
  return false;
}
//Stack<Cell> Maze::exitMaze()
void Maze::exitMaze(){
  if(findPath(current_cell)){
    cout << "achou!";
    moves.print();
  }else{
    cout << "Não ha caminho :(" << endl;
  }
}


#endif
