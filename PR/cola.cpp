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


struct Cola{
    Node* front = nullptr;
    Node* back = nullptr;

    void push(int val) {
        Node* nuevo = new Node(val);
        if (front == nullptr) {
            front = nuevo;
            back = nuevo;
        }else {
            back->next = nuevo;
            back = nuevo;
        }
    }

    void pop() {
        if (front == nullptr) return;

        Node* temp = front;
        front = front-> next;

        if (front == nullptr) {
            back = nullptr;
        }
        delete temp;
    }

    int peek() {
        if (front == nullptr) return -1;

        return front->dato;
    }

    bool isEmpty() {
        return front == nullptr;
    }

};


int main() {
    cin.tie(0)-> sync_with_stdio(false);

    Cola miCola;

    miCola.push(10);
    miCola.push(20);
    cout << "Asi esta el inicio ahora mismo" << miCola.peek()<< endl;

    miCola.pop();
    cout << "Asi esta el inicio despues del pop" << miCola.peek()<< endl;



}