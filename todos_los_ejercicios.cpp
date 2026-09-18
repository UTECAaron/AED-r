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
        while (at < (int)chains[chain_position].size() and chains[chain_position][at].first != key) {
            ++at;
        }
        if (at == (int)chains[chain_position].size()) {
            chains[chain_position].emplace_back(key, value_type());
            ++_size; // Solo aumenta si la clave es totalmente nueva
        }
        return chains[chain_position][at].second;
    }

    bool has_key (const key_type &key) const {
        int chain_position = _hash(key);
        int at = 0;
        while (at < (int)chains[chain_position].size() and chains[chain_position][at].first != key) {
            ++at;
        }
        return at != (int)chains[chain_position].size();
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

namespace p01 {
/*
 1. Contains Duplicate (LeetCode 217)
 Entrada: n, luego n enteros.
 Salida: "true" si hay un valor repetido, "false" si no.
 Clave del hash: to_string(valor) -> presencia (1/0).
*/
void solve(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    my_map<string,int> seen(200003);

    for (int i = 0; i < n; i++){
        long long x; cin >> x;
        string key = to_string(x);
        if (seen.has_key(key)) { cout << "true\n"; return; }
        seen[key] = 1;
    }
    cout << "false\n";
}
} // namespace p01

namespace p02 {
/*
 2. Two Sum (LeetCode 1)
 Entrada: n, luego n enteros (nums), luego target.
 Salida: dos indices (0-indexados) cuya suma es target.
 Clave del hash: to_string(valor) -> indice donde se vio por ultima vez.
*/
void solve(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    vector<long long> a(n);
    for (auto &x : a) cin >> x;
    long long target; cin >> target;

    my_map<string,int> idx(200003);
    for (int i = 0; i < n; i++){
        long long need = target - a[i];
        string key = to_string(need);
        if (idx.has_key(key)) {
            cout << idx[key] << " " << i << "\n";
            return;
        }
        idx[to_string(a[i])] = i;
    }
}
} // namespace p02

namespace p03 {
/*
 3. Registration System (Codeforces 4C)
 Entrada: n, luego n nombres.
 Salida: "OK" si el nombre estaba libre, o nombre+contador si estaba ocupado.
 Clave del hash: nombre -> cuantas veces se registro antes (0 = libre).
*/
void solve(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    my_map<string,int> cnt(200003);

    for (int i = 0; i < n; i++){
        string name; cin >> name;
        int &c = cnt[name];
        if (c == 0) cout << "OK\n";
        else cout << name << c << "\n";
        c++;
    }
}
} // namespace p03

namespace p04 {
/*
 4. Contains Duplicate II (LeetCode 219)
 Entrada: n, k, luego n enteros.
 Salida: "true" si existen dos indices iguales a distancia <= k, si no "false".
 Clave del hash: to_string(valor) -> ultimo indice donde se vio ese valor.
*/
void solve(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k; cin >> n >> k;
    vector<long long> a(n);
    for (auto &x : a) cin >> x;

    my_map<string,int> lastIdx(200003);
    for (int i = 0; i < n; i++){
        string key = to_string(a[i]);
        if (lastIdx.has_key(key) && i - lastIdx[key] <= k) {
            cout << "true\n";
            return;
        }
        lastIdx[key] = i;
    }
    cout << "false\n";
}
} // namespace p04

namespace p05 {
/*
 5. Subarray Sums I (CSES 1660)
 Entrada: n x, luego n enteros positivos.
 Salida: cantidad de subarreglos contiguos con suma exactamente x.
 Tecnica: prefijos + conteo de prefijos previos (prefix_sum - x).
 Clave del hash: to_string(prefijo) -> cuantas veces aparecio ese prefijo.
*/
void solve(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; long long x; cin >> n >> x;
    vector<long long> a(n);
    for (auto &v : a) cin >> v;

    my_map<string,long long> cnt(400003);
    cnt[to_string(0LL)] = 1;

    long long s = 0, ans = 0;
    for (int i = 0; i < n; i++){
        s += a[i];
        string need = to_string(s - x);
        if (cnt.has_key(need)) ans += cnt[need];
        cnt[to_string(s)]++;
    }
    cout << ans << "\n";
}
} // namespace p05

namespace p06 {
/*
 6. Distinct Values Subarrays (CSES 3420)
 Entrada: n, luego n enteros.
 Salida: cantidad de subarreglos contiguos con todos los elementos distintos.
 Tecnica: ventana deslizante, guardando la ultima posicion de cada valor.
 Clave del hash: to_string(valor) -> ultima posicion vista.
*/
void solve(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    vector<long long> a(n);
    for (auto &v : a) cin >> v;

    my_map<string,int> lastPos(400003);
    long long ans = 0;
    int left = 0;

    for (int right = 0; right < n; right++){
        string key = to_string(a[right]);
        if (lastPos.has_key(key) && lastPos[key] >= left) left = lastPos[key] + 1;
        lastPos[key] = right;
        ans += (right - left + 1);
    }
    cout << ans << "\n";
}
} // namespace p06

namespace p07 {
/*
 7. Same Differences (Codeforces 1520D)
 Entrada: t casos. Por caso: n, luego n enteros.
 Salida: cantidad de pares (i<j) con a[j]-a[i] == j-i.
 Truco: a[i]-i es igual para todo el grupo -> contar pares dentro de cada grupo.
 Clave del hash: to_string(a[i]-i) -> cuantos elementos de ese grupo van vistos.
*/
void solve(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<long long> a(n);
        for (auto &v : a) cin >> v;

        my_map<string,long long> cnt(400003);
        long long ans = 0;
        for (int i = 0; i < n; i++){
            string key = to_string(a[i] - i);
            if (cnt.has_key(key)) ans += cnt[key];
            cnt[key]++;
        }
        cout << ans << "\n";
    }
}
} // namespace p07

namespace p08 {
/*
 8. Group Anagrams (LeetCode 49)
 Entrada: n, luego n cadenas.
 Salida: cada grupo de anagramas en una linea (cadenas originales separadas por espacio).
 Clave del hash: cadena ordenada (firma del anagrama) -> lista de indices originales.
*/
void solve(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    vector<string> strs(n);
    for (auto &s : strs) cin >> s;

    my_map<string, vector<int>> groups(20011);
    vector<string> order; // para recordar el orden de aparicion de cada firma

    for (int i = 0; i < n; i++){
        string key = strs[i];
        sort(key.begin(), key.end());
        if (!groups.has_key(key)) order.push_back(key);
        groups[key].push_back(i);
    }

    for (auto &key : order){
        auto &idxs = groups[key];
        for (size_t j = 0; j < idxs.size(); j++){
            cout << strs[idxs[j]] << (j + 1 < idxs.size() ? ' ' : '\n');
        }
    }
}
} // namespace p08

namespace p09 {
/*
 9. Subarray Sums II (CSES 1661)
 Entrada: n x, luego n enteros (pueden ser negativos o cero).
 Salida: cantidad de subarreglos contiguos con suma exactamente x.
 Misma tecnica que el ejercicio 5; funciona igual con negativos porque
 to_string maneja el signo '-' sin problema.
*/
void solve(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; long long x; cin >> n >> x;
    vector<long long> a(n);
    for (auto &v : a) cin >> v;

    my_map<string,long long> cnt(400003);
    cnt[to_string(0LL)] = 1;

    long long s = 0, ans = 0;
    for (int i = 0; i < n; i++){
        s += a[i];
        string need = to_string(s - x);
        if (cnt.has_key(need)) ans += cnt[need];
        cnt[to_string(s)]++;
    }
    cout << ans << "\n";
}
} // namespace p09

namespace p10 {
/*
 10. Romantic Glasses (Codeforces 1915E)
 Entrada: t casos. Por caso: n, luego n enteros.
 Salida: "YES"/"NO" segun si existe un subarreglo con suma de posiciones
 impares == suma de posiciones pares (posiciones relativas al subarreglo).
 Truco: con b_i = a_i si i es impar, -a_i si es par (indices globales 1..n),
 y S = prefijos de b, la condicion se cumple si dos prefijos son iguales.
 Clave del hash: to_string(prefijo) -> visto o no.
*/
void solve(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<long long> a(n);
        for (auto &v : a) cin >> v;

        my_map<string,int> seen(400003);
        seen[to_string(0LL)] = 1;

        long long s = 0;
        bool found = false;
        for (int i = 1; i <= n; i++){
            int sign = (i % 2 == 1) ? 1 : -1;
            s += sign * a[i - 1];
            string key = to_string(s);
            if (seen.has_key(key)) { found = true; break; }
            seen[key] = 1;
        }
        cout << (found ? "YES" : "NO") << "\n";
    }
}
} // namespace p10

namespace p11 {
/*
 11. Monocarp's String (Codeforces 2145C)
 Entrada: t casos. Por caso: n, luego la cadena s (solo 'a'/'b').
 Salida: minima cantidad de caracteres contiguos a eliminar para igualar
 la cantidad de 'a' y 'b'; -1 si solo se logra eliminando todo.
 Truco: P[i] = prefijo de (+1 si 'a', -1 si 'b'). Se elimina el segmento
 (i, j] si P[j]-P[i] = P[n] (el total). Se busca, para cada j, el mayor i
 posible con ese valor de P, para minimizar j-i.
 Clave del hash: to_string(prefijo) -> indice mas reciente con ese valor.
*/
void solve(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--){
        int n; string s; cin >> n >> s;
        vector<int> P(n + 1, 0);
        for (int i = 0; i < n; i++) P[i + 1] = P[i] + (s[i] == 'a' ? 1 : -1);

        long long total = P[n];
        my_map<string,int> lastIndex(400003);
        lastIndex[to_string(P[0])] = 0;

        int best = n; // eliminar todo siempre es una opcion valida
        for (int j = 1; j <= n; j++){
            string need = to_string(P[j] - total);
            if (lastIndex.has_key(need)) best = min(best, j - lastIndex[need]);
            lastIndex[to_string(P[j])] = j;
        }
        cout << (best == n ? -1 : best) << "\n";
    }
}
} // namespace p11

namespace p12 {
/*
 12. Divisible Pairs (Codeforces 1931D)
 Entrada: t casos. Por caso: n x y, luego n enteros.
 Salida: cantidad de pares (i<j) con (a[i]+a[j]) % x == 0 y (a[i]-a[j]) % y == 0.
 Truco: a[i]-a[j] div. por y  <=>  a[i]%y == a[j]%y.
        a[i]+a[j] div. por x  <=>  a[j]%x == (x - a[i]%x) % x.
 Clave del hash: "resto_mod_y" + "_" + "resto_mod_x" -> cuantos ya vistos con esa combinacion.
*/
void solve(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--){
        int n; long long x, y; cin >> n >> x >> y;
        vector<long long> a(n);
        for (auto &v : a) cin >> v;

        my_map<string,long long> cnt(400003);
        long long ans = 0;

        for (int i = 0; i < n; i++){
            long long rx = a[i] % x;
            long long ry = a[i] % y;
            long long needRx = (x - rx) % x;

            string qkey = to_string(ry) + "_" + to_string(needRx);
            if (cnt.has_key(qkey)) ans += cnt[qkey];

            string skey = to_string(ry) + "_" + to_string(rx);
            cnt[skey]++;
        }
        cout << ans << "\n";
    }
}
} // namespace p12

namespace p13 {
/*
 13. Subarray Sum Equals K (LeetCode 560)
 Entrada: n, luego n enteros, luego k.
 Salida: cantidad de subarreglos contiguos (no vacios) con suma exactamente k.
 Misma tecnica de prefijos que los ejercicios 5 y 9.
*/
void solve(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    vector<long long> a(n);
    for (auto &v : a) cin >> v;
    long long k; cin >> k;

    my_map<string,long long> cnt(200003);
    cnt[to_string(0LL)] = 1;

    long long s = 0, ans = 0;
    for (int i = 0; i < n; i++){
        s += a[i];
        string need = to_string(s - k);
        if (cnt.has_key(need)) ans += cnt[need];
        cnt[to_string(s)]++;
    }
    cout << ans << "\n";
}
} // namespace p13

namespace p14 {
/*
 14. Longest Consecutive Sequence (LeetCode 128)
 Entrada: n, luego n enteros (n puede ser 0).
 Salida: longitud de la secuencia mas larga de enteros consecutivos.
 Tecnica: marcar presencia de cada valor; solo extender la cadena desde
 los valores que son "inicio" (v-1 no esta presente).
 Clave del hash: to_string(valor) -> presencia (1).
*/
void solve(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    vector<long long> a(n);
    for (auto &v : a) cin >> v;

    my_map<string,int> present(200003);
    for (auto v : a) present[to_string(v)] = 1;

    long long best = 0;
    for (auto v : a){
        if (!present.has_key(to_string(v - 1))){
            long long len = 1, cur = v;
            while (present.has_key(to_string(cur + 1))) { cur++; len++; }
            best = max(best, len);
        }
    }
    cout << best << "\n";
}
} // namespace p14

namespace p15 {
/*
 15. Sum of Four Values (CSES 1642)
 Entrada: n x, luego n enteros.
 Salida: cuatro posiciones distintas (1-indexadas) cuyos valores suman x,
 o "IMPOSSIBLE" si no existen.
 Tecnica: precomputar la suma de todos los pares (i,j), i<j, guardando
 TODOS los pares que logran cada suma (no solo uno), para poder descartar
 solapamientos de indices al buscar la pareja complementaria.
 Clave del hash: to_string(suma_del_par) -> lista de pares (i,j) con esa suma.
 Nota de complejidad: O(n^2) para construir el mapa y O(n^2) para buscar,
 mas el recorrido de listas por colisiones de suma; correcto pero no es la
 solucion mas rapida posible para n muy grande.
*/
void solve(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, x; cin >> n >> x;
    vector<long long> a(n);
    for (auto &v : a) cin >> v;

    my_map<string, vector<pair<int,int>>> pairSum(200003);
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            pairSum[to_string(a[i] + a[j])].push_back({i, j});

    for (int k = 0; k < n; k++){
        for (int l = k + 1; l < n; l++){
            long long need = x - a[k] - a[l];
            string key = to_string(need);
            if (!pairSum.has_key(key)) continue;
            for (auto &pr : pairSum[key]){
                int i = pr.first, j = pr.second;
                if (i != k && i != l && j != k && j != l){
                    cout << (i+1) << " " << (j+1) << " " << (k+1) << " " << (l+1) << "\n";
                    return;
                }
            }
        }
    }
    cout << "IMPOSSIBLE\n";
}
} // namespace p15

namespace p16 {
/*
 16. 4Sum II (LeetCode 454)
 Entrada: n, luego 4 lineas con n enteros cada una (nums1, nums2, nums3, nums4).
 Salida: cantidad de tuplas (i,j,k,l) con nums1[i]+nums2[j]+nums3[k]+nums4[l] == 0.
 Tecnica clasica: precomputar todas las sumas nums1[i]+nums2[j] en un mapa,
 luego para cada par (k,l) buscar -(nums3[k]+nums4[l]) en ese mapa.
 Clave del hash: to_string(suma) -> cuantos pares (i,j) logran esa suma.
*/
void solve(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    vector<long long> A(n), B(n), C(n), D(n);
    for (auto &v : A) cin >> v;
    for (auto &v : B) cin >> v;
    for (auto &v : C) cin >> v;
    for (auto &v : D) cin >> v;

    my_map<string, long long> sumAB(200003);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            sumAB[to_string(A[i] + B[j])]++;

    long long ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++){
            string key = to_string(-(C[i] + D[j]));
            if (sumAB.has_key(key)) ans += sumAB[key];
        }
    cout << ans << "\n";
}
} // namespace p16
/*
 =========================================================================
  COMO USAR ESTE ARCHIVO
 =========================================================================
 Todos los ejercicios estan aca, cada uno en su propio namespace (p01..p16)
 para que no choquen entre si. Compila una sola vez:

     g++ -O2 -std=c++17 -o sol todos_los_ejercicios.cpp

 Y corre el ejercicio que quieras pasando su numero como argumento;
 la entrada por stdin sigue siendo EXACTAMENTE la del enunciado original:

     ./sol 5   < entrada_ejercicio5.txt
     ./sol 12  < entrada_ejercicio12.txt

 Si vas a subir uno solo a un juez (Codeforces/CSES/etc.), copia unicamente
 el bloque "template" + el contenido de la funcion solve() del namespace
 que te interese, y renombra "solve" a "main" (sin argumentos, tipo int,
 con "return 0;" al final en vez de "return;").
 =========================================================================
*/

int main(int argc, char* argv[]){
    if (argc < 2){
        cerr << "Uso: " << argv[0] << " <numero_de_ejercicio (1-16)>\n";
        return 1;
    }
    int p = atoi(argv[1]);
    switch (p){
        case 1:  p01::solve(); break;
        case 2:  p02::solve(); break;
        case 3:  p03::solve(); break;
        case 4:  p04::solve(); break;
        case 5:  p05::solve(); break;
        case 6:  p06::solve(); break;
        case 7:  p07::solve(); break;
        case 8:  p08::solve(); break;
        case 9:  p09::solve(); break;
        case 10: p10::solve(); break;
        case 11: p11::solve(); break;
        case 12: p12::solve(); break;
        case 13: p13::solve(); break;
        case 14: p14::solve(); break;
        case 15: p15::solve(); break;
        case 16: p16::solve(); break;
        default:
            cerr << "Numero de ejercicio invalido (usa 1-16)\n";
            return 1;
    }
    return 0;
}
