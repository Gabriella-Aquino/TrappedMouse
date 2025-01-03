#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cctype>

using namespace std;

struct Maze_data
{
  vector<string> maze;
  int width;
  int height;
  pair<int, int> entryPos;
  pair<int, int> exitPos;

  Maze_data() = default;
};

Maze_data readFile(const string &fileName);

Maze_data readFile(const string &fileName)
{
  Maze_data maze_data;
  vector<string> maze;
  string line;
  bool isFirstLine = true;
  int mCount = 0, eCount = 0;
  string validChars = "mMeE01";
  int rowCount = 0; // posso criar função size em stack

  ifstream file(fileName);
  if (!file.is_open())
  {
    throw std::runtime_error("Erro ao tentar abrir o arquivo: " + fileName);
  }

  while (getline(file, line))
  {
    if (line.empty())
      continue;
    if (isFirstLine)
    {
      istringstream stream(line);
      stream >> maze_data.width >> maze_data.height;
      isFirstLine = false;
      continue;
    }
    // Tratamento de erros
    if (line.size() != maze_data.width)
    {
      throw std::runtime_error("[Error: Matriz invalida] linha desproporcional ou dimensoes incompativeis");
    }
    for (int col = 0; col < line.size(); col++) // char character : line
    {
      char character = line[col];
      if (character == 'm' || character == 'M')
      {
        character = tolower(character);
        maze_data.entryPos = {rowCount+1, col+1};
        mCount++;
      }
      if (character == 'e' || character == 'E')
      {
        character = tolower(character);
        maze_data.exitPos = {rowCount+1, col+1};
        eCount++;
      }
      if (validChars.find(character) == string::npos)
      {
        throw std::runtime_error("[Error: Matriz invalida] Caractere diferente de m, e, 1 ou zero");
      }
      line[col] = character;
    }

    line = "1" + line + "1";
    maze_data.maze.push_back(line);
    ++rowCount;
  }

  if (maze_data.height != rowCount)
  {
    throw std::runtime_error("[Erro: Matriz invalida] Dimensoes incompativeis");
  }
  if (mCount != 1 || eCount != 1)
  {
    throw std::runtime_error("[Erro: Matriz invalida] O arquivo deve conter exatamente um 'm' e um 'e'!");
  }

  string wallLine(maze_data.width + 2, '1');
  maze_data.maze.insert(maze_data.maze.begin(), wallLine);
  maze_data.maze.push_back(wallLine);

  maze_data.width = maze_data.width + 2;
  maze_data.height = maze_data.height + 2;

  file.close();

  return maze_data;
}

#endif
