#include <iostream>
#include <queue>
using namespace std;





int main() {

    queue<int> q;

    q.push(10); q.push(20);

    cout << q.front() << endl;

    q.pop();

    cout << q.front() << endl;

    return 0;
}



// ==========================================
// FUNCIONES DE LA LIBRERÍA ESTÁNDAR <queue>
// ==========================================

// miCola.push(valor);  // Inserta un elemento al final de la cola (por donde entran).
// miCola.pop();        // Elimina el elemento del frente de la cola (el primero en llegar).
// miCola.front();      // Devuelve el valor del elemento que está al frente (el próximo en salir).
// miCola.back();       // Devuelve el valor del último elemento que acaba de entrar.
// miCola.empty();      // Devuelve 'true' si la cola está vacía, o 'false' si tiene elementos.
// miCola.size();       // Devuelve un entero con la cantidad total de elementos en la cola.