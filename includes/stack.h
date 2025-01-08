// #include <iostream>

// struct No
// {
//   string valor;
//   int pos_x;
//   int pos_y;
//   No *proximo;
// };

// class Stack
// {
// private:
//   No *topo;

// public:
//   Stack();
//   ~Stack();
//   bool isEmpty();
//   bool push(char item, int pos_x, int pos_y);
//   No pop();
//   void print();
// };

// Stack::Stack()
// {
//   topo = nullptr;
// }

// Stack::~Stack()
// {
//   while (topo != nullptr)
//   {
//     No* novoTopo = topo->proximo;
//     No* topoAntigo = topo;
//     topo = novoTopo;
//     delete topoAntigo;
//   }
// }

// bool Stack::isEmpty()
// {
//   return (topo == nullptr);
// }

// bool Stack::push(char item, int pos_x, int pos_y)
// {
//   No *novoNo = new No();
//   novoNo->valor = item;
//   novoNo->pos_x = pos_x;
//   novoNo->pos_y = pos_y;
//   novoNo->proximo = topo;
//   topo = novoNo;
// }
// No Stack::pop()
// {
//   if (this->isEmpty())
//   {
//     std::cerr << "Erro: Pilha vazia" << std::endl;
//   }else{
//     No item = *topo;
//     No* noAuxiliar = topo;
//     topo = topo->proximo;
//     delete noAuxiliar;
//     return item;
//   }
// }
// void Stack::print()
// {
//   No* noAuxiliar = topo;
//   while (noAuxiliar != nullptr){
//     std::printf("%c[%d][%d], ", noAuxiliar->valor, noAuxiliar->pos_x, noAuxiliar->pos_y);
//     noAuxiliar = noAuxiliar->proximo;
//   }
//   std::cout << "" << std::endl;
// }

#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <string>
#include <cstddef>

// Classe Cell
class Cell {
private:
    int pos_x;
    int pos_y;

public:
    Cell() : pos_y(0), pos_x(0) {}

    Cell(int x, int y) : pos_y(y), pos_x(x) {}

    int getX() const { return pos_x; }
    void setX(int pos_x){this->pos_x = pos_x;}
    int getY() const { return pos_y; }
    void setY(int pos_y){this->pos_y = pos_y;}


    Cell& operator=(const Cell& other) {
        if (this != &other) {
            this->setX(other.getX());
            this->setY(other.getY());
        }
        return *this;
    }

    Cell &operator=(const std::pair<int, int> &new_value)
    {
        this->setX(new_value.first);
        this->setY(new_value.second);
        return *this;
    }
    Cell& assign(int pos_x, int pos_y) {
        if (this->getX() != pos_x, this->getY() != pos_y) {
            this->setX(pos_x);
            this->setY(pos_y);
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Cell& pos) {
        os << "[" << pos.getY() << ", " << pos.getX() << "]";
        return os;
    }
};

template <typename T>
struct No {
    T valor;
    No<T>* proximo;

    No(const T& valor, No<T>* proximo = nullptr) : valor(valor), proximo(proximo) {}
};


template <typename T>
class Stack {
private:
    No<T>* topo;
    int size = 0;
public:
    Stack() : topo(nullptr) {}

    ~Stack() {
        while (topo != nullptr) {
            No<T>* noAuxiliar = topo->proximo;
            delete topo;
            topo = noAuxiliar;
        }
    }

    Stack(const Stack& other) : topo(nullptr) {
        Stack<T> temp_stack;
        No<T>* noAuxiliar = other.topo;

        while (noAuxiliar != nullptr) {
            temp_stack.push(noAuxiliar->valor);
            noAuxiliar = noAuxiliar->proximo;
        }

        while (!temp_stack.isEmpty()) {
            this->push(temp_stack.top());
            temp_stack.pop();
        }
    }

    Stack& operator=(const Stack& other) {
    if (this != &other) {
        while (!this->isEmpty()) {
            this->pop();
        }
        Stack<T> temp_stack;
        No<T>* noAuxiliar = other.topo;

        while (noAuxiliar != nullptr) {
            temp_stack.push(noAuxiliar->valor);
            noAuxiliar = noAuxiliar->proximo;
        }
        while (!temp_stack.isEmpty()) {
            this->push(temp_stack.top());
            temp_stack.pop();
        }
    }
    return *this;
}


    bool isEmpty() const {
        return (topo == nullptr);
    }

    T top() const {
        if(isEmpty()){
            std::cerr << "Erro: Pilha vazia" << std::endl;
        }
        return topo->valor;
    }

    void push(const T& item) {
        No<T>* novoNo = new No<T>(item, topo);
        topo = novoNo;
        size++;
    }

    void pop() {
        if (isEmpty()) {
            std::cerr << "Erro: Pilha vazia" << std::endl;
            return;
        }
        No<T>* noAuxiliar = topo;
        topo = topo->proximo;
        delete noAuxiliar;
        size--;
    }

    int get_size() const {
        return size;
    }

    void print() const {
        No<T>* noAuxiliar = topo;
        while (noAuxiliar != nullptr) {
            std::cout << noAuxiliar->valor;
            if (noAuxiliar->proximo != nullptr) {
                std::cout << ", ";
            }
            noAuxiliar = noAuxiliar->proximo;
        }
        std::cout << std::endl;
    }
};

// Especialização do método print para Stack<Cell>
template <>
void Stack<Cell>::print() const {
    No<Cell>* noAuxiliar = topo;
    while (noAuxiliar != nullptr) {
        const Cell& pos = noAuxiliar->valor;
        std::cout << "[" << pos.getY() << ", " << pos.getX() << "]";
        if (noAuxiliar->proximo != nullptr) {
            std::cout << ", ";
        }
        noAuxiliar = noAuxiliar->proximo;
    }
    std::cout << std::endl;
}

#endif
