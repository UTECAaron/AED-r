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

void insertFirst(Node* &head, int value) {
    Node* nuevo = new Node(value);
    nuevo->next = head;
    head = nuevo;
}

void insertLast(Node* &head, int value) {
    Node* nuevo = new Node(value);

    if (head == nullptr) {
        head = nuevo;
        return;
    }


    Node* actual = head;
    while (actual->next != nullptr) {
        actual= actual->next;
    }

    actual ->next = nuevo;

}


void printList(Node* head) {
    Node* actual = head;

    while (actual != nullptr) {
        cout << actual->dato << " ";
        actual = actual ->next;
    }
}

void eliminarInicio(Node* &head) {
    if (head == nullptr) return;

    Node* temp =head;
    head = head->next;
    delete temp;
}

void eliminarPorValor(Node* &head,int valorBuscado) {
    if ( head == nullptr) return;

    if (head -> dato == valorBuscado) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node* actual = head;
    Node* anterior = nullptr;

    while (actual != nullptr && actual->dato != valorBuscado) {
        anterior = actual;
        actual= actual->next;
    }

    if (actual  == nullptr) return;

    //ahora ya lo logramos entonces
    anterior-> next = actual->next;
    delete actual;


}


int main() {

    cin.tie(0) -> sync_with_stdio(false);
    int n;

    cin >> n;


    Node* head = nullptr;

    for ( int i = 0 ; i < n ; ++i) {
        int x;
        cin >> x ;
        insertLast(head,x);
    }


    printList(head);

    cout << endl <<  "despues de eliminar: ";
    eliminarPorValor(head,20);

    printList(head);

    return 0;
}