#include <iostream>

using namespace std;

struct Node {
    int dato;
    Node* next;

    Node(int value) {
        dato = value;
        next = nullptr;
    }
};


struct Pila {
    Node* top = nullptr;

    void push(int val) {
        Node* nuevo = new Node(val);
        nuevo->next = top;
        top = nuevo;
    }

    void pop(){
        if (top == nullptr) return;
        Node* temp = top;
        top = top->next;
        delete temp;
    }

    int peek() {
        if (top == nullptr) return -1;

        return top-> dato;
    }

    bool isEmpty() {
        return top == nullptr;
    }



};

int main() {
    cin.tie(0) -> sync_with_stdio(false);


    int n;

    cin >> n;
    Pila miPila;

    for (int i = 0; i < n ; ++i) {
        int  x;
        cin >> x;
        miPila.push(x);

    }

    cout << "El tope actual es "<< miPila.peek()<< endl;

    miPila.pop();
    cout << "El tope actual es "<< miPila.peek()<< endl;


    return 0;
}