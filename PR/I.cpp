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
            ++_size;
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

    // Hash ultrarrápido adaptado para enteros (soporta negativos y positivos)
    int _hash(key_type key) const {
        unsigned long long x = key;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        x = x ^ (x >> 31);
        return x % m;
    }

    int size() const { return _size; }
    bool empty() const { return _size == 0; }
};

int main() {
    // Optimización de la velocidad de entrada y salida
    cin.tie(0) -> sync_with_stdio(false);

    int n;
    long long x;
    if (!(cin >> n >> x)) return 0;

    // Usamos 500,003 cubos para manejar eficientemente hasta 2*10^5 elementos sin colisiones graves
    my_map<long long, long long> prefix_counts(500003);

    // Caso base: una suma acumulada de 0 ocurre 1 vez al inicio
    prefix_counts[0] = 1;

    long long current_sum = 0;
    long long total_subarrays = 0;

    for (int i = 0; i < n; ++i) {
        long long val;
        cin >> val;

        current_sum += val;

        // Buscamos cuántas veces ha aparecido la suma (current_sum - x) previamente
        long long needed = current_sum - x;
        if (prefix_counts.has_key(needed)) {
            total_subarrays += prefix_counts[needed];
        }

        // Registramos la suma acumulada actual en el mapa
        prefix_counts[current_sum]++;
    }

    cout << total_subarrays << "\n";

    return 0;
}