#include <iostream>
#include "includes/file_utils.h"
#include "includes/stack.h"

int main()
{
  using namespace std;
  Maze_data matrizLab = readFile("input.txt");
  for (const auto &line : matrizLab.maze)
  {
    cout << line << endl;
  }

  return 0;
}