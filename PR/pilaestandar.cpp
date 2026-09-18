#include <iostream>
#include <stack>

using namespace std;

int main() {
    cin.tie(0)-> sync_with_stdio(false);

    int n;
    cin >> n;

    stack<int> miPila;

    for (int i = 0 ; i < n ; ++i) {
        int x;
        cin >> x;
        miPila.push(x);
    }

    if (!miPila.empty()) {
        cout << "El tope actual es : " << miPila.top() << endl;
    }

    miPila.pop();

    if (!miPila.empty()) {
        cout << "El tope actual es : " << miPila.top() << endl;
    }

    return 0;
}

// ==========================================
// FUNCIONES DE LA LIBRERÍA ESTÁNDAR <stack>
// ==========================================

// miPila.push(valor);  // Inserta un elemento en la parte superior (tope) de la pila.
// miPila.pop();        // Elimina el elemento del tope (no devuelve nada, solo lo borra).
// miPila.top();        // Devuelve el valor del elemento que está en el tope sin borrarlo.
// miPila.empty();      // Devuelve 'true' si la pila está vacía, o 'false' si tiene elementos.
// miPila.size();       // Devuelve un entero con la cantidad total de elementos en la pila.