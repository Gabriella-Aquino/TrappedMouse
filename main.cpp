#include <iostream>
#include "includes/file_utils.h"

#include "includes/stack.h"
// #include <windows.h>

#include <chrono>
#include "includes/maze.h"

int main()
{
  using namespace std;
  using namespace chrono;

  // SetConsoleOutputCP(CP_UTF8);

  try
  {
    auto start = high_resolution_clock::now();
    Maze_data maze_file = readFile("input.txt");
    Maze maze(maze_file.maze, maze_file.entryPos, maze_file.exitPos, maze_file.width, maze_file.height);

    // Verifica se a matriz está vazia (indicando erro)
    if (maze.getMaze().empty())
    {
      cerr << "Erro ao carregar a matriz." << endl;
      return 1; // Retorna erro
    }

    // for (const auto &linha : maze.getMaze())
    // {
    //   for (char c : linha)
    //   {
    //     cout << c;
    //   }
    //   cout << endl;
    // }
    // cout << "entryPos struct: " << maze_file.entryPos.first << ", " << maze_file.entryPos.second << endl; //certo
    // cout << "exitPos struct: " << maze_file.exitPos.first << ", " << maze_file.exitPos.second << endl; //certo
    // maze.printMazeFile();
    maze.printMaze();
    maze.exitMaze();
    // maze.printMaze();

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Tempo de execução: " << duration.count() << " ms" << endl;
  }
  catch (const std::runtime_error &e)
  {
    cerr << "Erro: " << e.what() << endl;
    return 1;
  }

  return 0;
}