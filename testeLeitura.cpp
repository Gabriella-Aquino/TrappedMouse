#include <iostream>
#include "includes/file_utils.h"
#include <vector>
#include <string>
#include "includes/stack.h"

int main()
{
  using namespace std;
  vector<string> matrizLab = readFile("../input.txt");
  for (const auto &line : matrizLab)
  {
    cout << line << endl;
  }

  return 0;
}