#include <iostream>
#include "includes/file_utils.h"
#include "includes/stack.h"
#include <chrono>
#include "includes/maze.h"

int main()
{
  using namespace std;
  using namespace chrono;

  try
  {
    //dimensões do txt: largura altura
    Maze_data maze_file = readFile("mazes/input.txt");
    Maze maze(maze_file.maze, maze_file.entryPos, maze_file.exitPos, maze_file.width, maze_file.height);

    if (maze.getMaze().empty())
    {
      cerr << "Erro ao carregar a matriz." << endl;
      return 1;
    }

    maze.exitMaze();
    
    auto end = high_resolution_clock::now();
  }
  catch (const std::runtime_error &error)
  {
    cerr << "Erro " << error.what() << endl;
    return 1;
  }

  return 0;
}