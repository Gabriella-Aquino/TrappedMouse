#include <iostream>
#include "includes/file_utils.h"
#include "includes/stack.h"
#include <chrono>
#include "includes/maze.h"

int main(int argc, char* argv[])
{
  using namespace std;
  using namespace chrono;

  try
  {
    bool debug = false;
    string file_name = "";
    for(int i = 1; i < argc; i++){
      string arg = argv[i];
      if(arg == "--debug"){
        debug = true;
      }
      if (arg == "--maze"){
        if(i + 1 < argc){
          file_name = argv[i+1];
          i++;
        }else{
          cerr << "Erro: Nenhum arquivo especificado após --arquivo" << endl;
          return 1;
        }
      }
    }
    //dimensões do txt: largura altura
    if (file_name == "")
      file_name = "mazes/input.txt";
    
    Maze_data maze_file = readFile(file_name);
    Maze maze(maze_file.maze, maze_file.entryPos, maze_file.exitPos, maze_file.width, maze_file.height);

    if (maze.getMaze().empty())
    {
      cerr << "Erro ao carregar a matriz." << endl;
      return 1;
    }

    maze.exitMaze();
    if(debug) maze.printLog();
    
    auto end = high_resolution_clock::now();
  }
  catch (const std::runtime_error &error)
  {
    cerr << "Erro " << error.what() << endl;
    return 1;
  }

  return 0;
}