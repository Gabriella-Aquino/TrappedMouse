#include <iostream>
#include "includes/stack.h"

int main()
{
  using namespace std;

  Stack<std::string> pilhaString;
  pilhaString.push("Hello");
  pilhaString.push("World");
  pilhaString.print(); // Saída esperada: World, Hello,

  // Testando com struct
  Stack<Cell> pilhaPosicao;
  pilhaPosicao.push({1, 2});
  pilhaPosicao.push({3, 4});
  int num1 = 4, num2 = 5;
  pilhaPosicao.push({num1, num2});
  pilhaPosicao.pop();

  pilhaPosicao.print(); // Saída esperada:  [3,4], [1,2],

  cout << "Cell -------------" << endl;
  Cell c1(1, 2);
  Cell c2(3, 4);
  Cell c3;
  Cell c4;
  Cell c5;
  pair<int, int> new_pair {5, 25};

  cout << "Antes da atribuição:" << endl;
  cout << "c1: " << c1 << endl;
  cout << "c2: " << c2 << endl;

  c1 = c2;
  c4.assign(10, 5);
  c5 = new_pair;

  Stack<Cell> pilha_copia = pilhaPosicao;

  cout << "\nDepois da atribuição:" << endl;
  cout << "c1: " << c1 << endl;
  cout << "c2: " << c2 << endl;
  cout << "c4: " << c4 << endl;
  cout << "c5: " << c5 << endl;
  pilha_copia.print();
  return 0;
}