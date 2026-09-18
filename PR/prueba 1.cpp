
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

    void erase(const key_type &key) {
        int chain_position = _hash(key);
        int at = 0;
        while (at < chains[chain_position].size() and chains[chain_position][at].first != key) {
            ++at;
        }
        if (at != chains[chain_position].size()) {
            if (at + 1 < chains[chain_position].size()) {
                swap(chains[chain_position][at], chains[chain_position].back());
            }
            chains[chain_position].pop_back();
            --_size;
        }
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

    // Hash 100% manual para enteros (Soporta positivos, negativos y cero)
    int _hash(key_type key) const {
        const int B = 311;
        const int MOD = 1e9 + 7;
        long long hash_value = 0;

        long long temp = key;
        bool es_negativo = false;

        if (temp < 0) {
            es_negativo = true;
            temp = -temp; // Pasamos a positivo para extraer dígitos
        }

        while (temp > 0) {
            int d = temp % 10;
            hash_value = (1ll * hash_value * B + (d + 1)) % MOD;
            temp /= 10;
        }

        // Modificador para que los negativos no colisionen con los positivos
        if (es_negativo) {
            hash_value = (1ll * hash_value * B + 7) % MOD;
        }

        return hash_value % m;
    }

    int size() const {
        return _size;
    }

    bool empty() const {
        return _size == 0;
    }

    void print() {
        for (int i = 0; i < m; ++i) {
            cout << "Bucket " << i << ": " << endl;
            for (auto &e : chains[i]) {
                cout << e.first << " --> " << e.second << endl;
            }
            cout << "End bucket" << endl;
        }
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(false);

    string r;
    cin >> r;

    my_map<char, int> freq;


    for (char c : r) {
        freq[c]++;
    }

    string m;
    cin >> m;


    if (r.length() > m.length()) {
        cout << "NO";
        return 0;
    }

    int letras_faltantes = r.length();

    for (char c : m) {
        if (freq.has_key(c) && freq[c] > 0) {
            freq[c]--;
            letras_faltantes--;
        }
    }

    if (letras_faltantes == 0 ) {
        cout << "SI";
    }else{
        cout <<"NO";
    }


    return 0;
}