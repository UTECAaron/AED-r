#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

template<typename key_type, typename value_type>
struct my_map {
    int m;
    int _size;
    vector<vector<pair<key_type, value_type>>> chains;

    my_map(int m = 1) : m(m), _size(0) {
        chains.resize(m);
    }

    value_type& operator [] (const key_type &key) {
        int chain_position = _hash(key);
        int at = 0;
        while (at < chains[chain_position].size() and chains[chain_position][at].first != key) {
            ++at;
        }
        if (at == chains[chain_position].size()) {
            chains[chain_position].emplace_back(key, value_type());
            ++_size; // Solo aumenta si la clave es totalmente nueva
        }
        return chains[chain_position][at].second;
    }

    bool has_key (const key_type &key) const {
        int chain_position = _hash(key);
        int at = 0;
        while (at < chains[chain_position].size() and chains[chain_position][at].first != key) {
            ++at;
        }
        if (at == chains[chain_position].size()) {
            return false;
        }
        return true;
    }

    // Hash adaptado para cadenas (string) utilizando polynomial rolling hash
    int _hash(key_type key) const {
        const int B = 311;
        const int MOD = 1e9 + 7;
        unsigned long long hash_value = 0;

        for (char c : key) {
            hash_value = (hash_value * B + (c - 'a' + 1)) % MOD;
        }

        return hash_value % m;
    }

    int size() const {
        return _size;
    }

    bool empty() const {
        return _size == 0;
    }
};

int main() {
    // Optimización de la velocidad de entrada y salida
    cin.tie(0) -> sync_with_stdio(false);

    int n;
    if (!(cin >> n)) return 0;

    // Creamos nuestro mapa con claves de tipo string y un millón de cubos para evitar TLE
    my_map<string, bool> groups(1000003);

    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;

        // Ordenamos los caracteres de la cadena para obtener la firma del anagrama
        sort(s.begin(), s.end());

        // Al asignar en el mapa, si la firma ya existe no hace nada extra,
        // pero si es nueva, la inserta y aumenta automáticamente el contador interno.
        groups[s] = true;
    }

    // El tamaño del mapa representa exactamente el número de clases de equivalencia
    cout << groups.size() << "\n";

    return 0;
}