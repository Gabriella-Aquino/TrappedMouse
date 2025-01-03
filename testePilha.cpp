#include <iostream>
#include "includes/stack.h"

int main()
{
  using namespace std;

  //   Stack pilha;

  //   pilha.print();

  //   pilha.push('1', 1, 2);
  //   pilha.push('2', 9, 2);
  //   pilha.push('3', 7, 2);

  //   cout << "pilha:" << endl;
  //   pilha.print();

  //   cout << "pop:" << endl;
  //   pilha.pop();
  //   pilha.print();

  //   cout << "pop:" << endl;
  //   pilha.pop();
  //   pilha.print();

  //   cout << "pop:" << endl;
  //   pilha.pop();
  //   pilha.print();

  //   cout << "pop:" << endl;
  //   pilha.pop();
  //   pilha.print();

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
  tuple<int, int> new_tuple = {5, 5};
  pair<int, int> new_pair {5, 25};

  cout << "Antes da atribuição:" << endl;
  cout << "c1: " << c1 << endl;
  cout << "c2: " << c2 << endl;

  c1 = c2;
  c3 = tuple<int, int>{8, 8};
  c4.assign(10, 5);
  c5 = new_pair;

  cout << "\nDepois da atribuição:" << endl;
  cout << "c1: " << c1 << endl;
  cout << "c2: " << c2 << endl;
  cout << "c3: " << c3 << endl;
  cout << "c4: " << c4 << endl;
  cout << "c5: " << c5 << endl;
  return 0;
}