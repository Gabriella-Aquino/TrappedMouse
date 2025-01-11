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
  Maze_data mazeData;
  vector<string> maze;
  string line;
  bool isFirstLine = true;
  int mCount = 0, eCount = 0;
  string validChars = "mMeE01";
  int rowCount = 0;

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
      stream >> mazeData.width >> mazeData.height;
      isFirstLine = false;
      continue;
    }
    // Tratamento de erros
    if (line.size() != mazeData.width)
    {
      throw std::runtime_error("labirinto invalido: linha desproporcional ou dimensoes incompativeis");
    }
    for (int col = 0; col < line.size(); col++) // char character : line
    {
      char character = line[col];
      if (character == 'm' || character == 'M')
      {
        character = tolower(character);
        mazeData.entryPos = {col + 1, rowCount + 1};
        mCount++;
      }
      if (character == 'e' || character == 'E')
      {
        character = tolower(character);
        mazeData.exitPos = {col+1, rowCount+1};
        eCount++;
      }
      if (validChars.find(character) == string::npos)
      {
        throw std::runtime_error("labirinto invalido: Caractere diferente de m, e, 1 ou zero");
      }
      line[col] = character;
    }

    line = "1" + line + "1";
    mazeData.maze.push_back(line);
    ++rowCount;
  }

  if (mazeData.height != rowCount)
  {
    throw std::runtime_error("labirinto invalido: Dimensoes incompativeis");
  }
  if (mCount != 1 || eCount != 1)
  {
    throw std::runtime_error("labirinto invalido: O arquivo deve conter exatamente um 'm' e um 'e'!");
  }

  string wallLine(mazeData.width + 2, '1');
  mazeData.maze.insert(mazeData.maze.begin(), wallLine);
  mazeData.maze.push_back(wallLine);

  mazeData.width = mazeData.width + 2;
  mazeData.height = mazeData.height + 2;

  file.close();

  return mazeData;
}

#endif
