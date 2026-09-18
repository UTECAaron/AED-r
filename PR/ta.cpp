import os

estructura = {
    "Seccion_1": {
        "1_Contains_Duplicate.cpp": """/*
    Fuente: LeetCode 217 (Easy)
    Consigna: Dado un arreglo de enteros, determina si algún valor aparece al menos dos veces. 
    Si todos los elementos son distintos, la respuesta debe ser falsa.
    Entrada: n elementos del arreglo.
    Salida: true si hay duplicado, false en caso contrario.
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n; if (!(cin >> n)) return 0;
    unordered_set<int> seen; bool duplicated = false;
    for (int i = 0; i < n; ++i) { int x; cin >> x; if (seen.count(x)) duplicated = true; seen.insert(x); }
    cout << (duplicated ? "true\\n" : "false\\n");
    return 0;
}""",
        "2_Two_Sum.cpp": """/*
    Fuente: LeetCode 1 (Easy)
    Consigna: Dado un arreglo de enteros y un objetivo, encuentra dos posiciones distintas cuyos valores sumen exactamente el objetivo.
    Entrada: n, target y luego los n elementos.
    Salida: Los dos índices encontrados.
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n; long long target; if (!(cin >> n >> target)) return 0;
    vector<long long> nums(n); for (int i = 0; i < n; ++i) cin >> nums[i];
    unordered_map<long long, int> mp;
    for (int i = 0; i < n; ++i) {
        long long complement = target - nums[i];
        if (mp.count(complement)) { cout << mp[complement] << " " << i << "\\n"; return 0; }
        mp[nums[i]] = i;
    }
    return 0;
}""",
        "3_Registration_System.cpp": """/*
    Fuente: Codeforces 4C (Easy)
    Consigna: Se procesan solicitudes de nombres de usuario. Si no existe, se acepta (OK). 
    Si ya existe, se genera un nuevo nombre agregando al final el menor entero positivo disponible.
    Entrada: n y luego n nombres.
    Salida: OK o el nombre modificado con el sufijo numérico.
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n; if (!(cin >> n)) return 0;
    unordered_map<string, int> db;
    while (n--) {
        string s; cin >> s;
        if (db[s] == 0) { cout << "OK\\n"; db[s] = 1; }
        else { cout << s << db[s] << "\\n"; db[s]++; }
    }
    return 0;
}"""
    },
    "Seccion_2": {
        "4_Contains_Duplicate_II.cpp": """/*
    Fuente: LeetCode 219 (Easy)
    Consigna: Dado un arreglo y un entero k, determina si existen dos índices distintos con el mismo valor y distancia <= k.
    Entrada: n, k y el arreglo de n elementos.
    Salida: true o false.
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n, k; if (!(cin >> n >> k)) return 0;
    vector<int> nums(n); for (int i = 0; i < n; ++i) cin >> nums[i];
    unordered_map<int, int> last_pos; bool found = false;
    for (int i = 0; i < n; ++i) {
        if (last_pos.count(nums[i]) && i - last_pos[nums[i]] <= k) { found = true; break; }
        last_pos[nums[i]] = i;
    }
    cout << (found ? "true\\n" : "false\\n");
    return 0;
}""",
        "5_Subarray_Sums_I.cpp": """/*
    Fuente: CSES 1660 (Medium)
    Consigna: Dado un arreglo de enteros positivos, cuenta cuántos subarreglos contiguos tienen suma exactamente x.
    Entrada: n, x y los elementos del arreglo.
    Salida: Cantidad de subarreglos válidos.
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n; long long x; if (!(cin >> n >> x)) return 0;
    vector<long long> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
    long long current_sum = 0, count = 0; int left = 0;
    for (int right = 0; right < n; ++right) {
        current_sum += a[right];
        while (current_sum > x && left <= right) { current_sum -= a[left]; left++; }
        if (current_sum == x) count++;
    }
    cout << count << "\\n";
    return 0;
}""",
        "6_Distinct_Values_Subarrays.cpp": """/*
    Fuente: CSES 3420 (Medium)
    Consigna: Cuenta cuántos subarreglos contiguos tienen todos sus elementos distintos entre sí.
    Entrada: n y los elementos del arreglo.
    Salida: Cantidad total de subarreglos con elementos únicos.
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n; if (!(cin >> n)) return 0;
    vector<long long> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
    unordered_map<long long, int> last_seen; long long total = 0; int left = 0;
    for (int right = 0; right < n; ++right) {
        if (last_seen.count(a[right])) left = max(left, last_seen[a[right]] + 1);
        last_seen[a[right]] = right;
        total += (right - left + 1);
    }
    cout << total << "\\n";
    return 0;
}""",
        "7_Same_Differences.cpp": """/*
    Fuente: Codeforces 1520D (Medium)
    Consigna: Cuenta los pares de índices (i, j) con i < j que cumplen a_j - a_i = j - i.
    Entrada: t (casos de prueba), luego n y el arreglo por cada caso.
    Salida: Cantidad de pares para cada caso.
*/
#include <bits/stdc++.h>
using namespace std;
void solve() {
    int n; cin >> n;
    unordered_map<int, long long> counts; long long ans = 0;
    for (int i = 1; i <= n; ++i) {
        int a; cin >> a; int key = a - i;
        ans += counts[key]; counts[key]++;
    }
    cout << ans << "\\n";
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int t; if (cin >> t) while (t--) solve();
    return 0;
}""",
        "8_Group_Anagrams.cpp": """/*
    Fuente: LeetCode 49 (Medium)
    Consigna: Dado un arreglo de cadenas, agrupa juntas aquellas que sean anagramas entre sí.
    Entrada: n y las n cadenas.
    Salida: Los grupos formados de anagramas.
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n; if (!(cin >> n)) return 0;
    unordered_map<string, vector<string>> groups;
    for (int i = 0; i < n; ++i) {
        string s; cin >> s; string key = s;
        sort(key.begin(), key.end());
        groups[key].push_back(s);
    }
    for (auto& pair : groups) {
        cout << "[ ";
        for (const string& s : pair.second) cout << "\\"" << s << "\\" ";
        cout << "]\\n";
    }
    return 0;
}"""
    },
    "Seccion_3": {
        "9_Subarray_Sums_II.cpp": """/*
    Fuente: CSES 1661 (Medium)
    Consigna: Dado un arreglo con positivos, negativos y ceros, cuenta cuántos subarreglos contiguos suman x.
    Entrada: n, x y los n elementos.
    Salida: Cantidad de subarreglos que suman x.
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n; long long x; if (!(cin >> n >> x)) return 0;
    unordered_map<long long, long long> prefix_counts;
    prefix_counts[0] = 1; long long current_sum = 0, total = 0;
    for (int i = 0; i < n; ++i) {
        long long val; cin >> val; current_sum += val;
        long long needed = current_sum - x;
        if (prefix_counts.count(needed)) total += prefix_counts[needed];
        prefix_counts[current_sum]++;
    }
    cout << total << "\\n";
    return 0;
}""",
        "10_Romantic_Glasses.cpp": """/*
    Fuente: Codeforces 1915E (Medium)
    Consigna: Determina si existe un subarreglo contiguo donde la suma de elementos en posiciones impares 
    sea igual a la suma en posiciones pares.
    Entrada: t casos, cada uno con n y el arreglo.
    Salida: YES o NO por caso.
*/
#include <bits/stdc++.h>
using namespace std;
void solve() {
    int n; cin >> n; vector<long long> a(n);
    for (int i = 0; i < n; ++i) { cin >> a[i]; if (i % 2 == 1) a[i] = -a[i]; }
    unordered_map<long long, bool> seen; long long current_sum = 0; seen[0] = true; bool possible = false;
    for (int i = 0; i < n; ++i) {
        current_sum += a[i];
        if (seen.count(current_sum)) { possible = true; break; }
        seen[current_sum] = true;
    }
    cout << (possible ? "YES\\n" : "NO\\n");
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int t; if (cin >> t) while (t--) solve();
    return 0;
}""",
        "11_Monocarps_String.cpp": """/*
    Fuente: Codeforces 2145C (Medium)
    Consigna: Mínima cantidad de caracteres contiguos a eliminar de una cadena (sólo 'a' y 'b') 
    para que la cantidad de 'a' y 'b' restantes sean iguales.
    Entrada: t casos, cada uno con n y la cadena s.
    Salida: Longitud mínima a eliminar o -1.
*/
#include <bits/stdc++.h>
using namespace std;
void solve() {
    int n; cin >> n; string s; cin >> s;
    int total_a = 0, total_b = 0;
    for (char c : s) { if (c == 'a') total_a++; else total_b++; }
    int diff = total_a - total_b;
    if (diff == 0) { cout << 0 << "\\n"; return; }
    unordered_map<int, int> last_idx; last_idx[0] = -1;
    int current_sum = 0, min_len = n + 1;
    for (int i = 0; i < n; ++i) {
        current_sum += (s[i] == 'a' ? 1 : -1);
        int needed = current_sum - diff;
        if (last_idx.count(needed)) min_len = min(min_len, i - last_idx[needed]);
        last_idx[current_sum] = i;
    }
    cout << (min_len > n ? -1 : min_len) << "\\n";
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int t; if (cin >> t) while (t--) solve();
    return 0;
}""",
        "12_Divisible_Pairs.cpp": """/*
    Fuente: Codeforces 1931D (Medium/Hard)
    Consigna: Cuenta pares (i, j) con i < j tales que (a_i + a_j) es divisible por x y (a_i - a_j) es divisible por y.
    Entrada: t casos, con n, x, y y el arreglo.
    Salida: Cantidad de pares válidos.
*/
#include <bits/stdc++.h>
using namespace std;
void solve() {
    long long n, x, y; cin >> n >> x >> y;
    vector<long long> a(n); map<pair<long long, long long>, long long> counts; long long ans = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        long long rem_x = a[i] % x, rem_y = a[i] % y;
        long long needed_x = (x - rem_x) % x, needed_y = rem_y;
        ans += counts[{needed_x, needed_y}];
        counts[{rem_x, rem_y}]++;
    }
    cout << ans << "\\n";
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int t; if (cin >> t) while (t--) solve();
    return 0;
}""",
        "13_Subarray_Sum_Equals_K.cpp": """/*
    Fuente: LeetCode 560 (Medium)
    Consigna: Dado un arreglo de enteros y un entero k, calcula el número total de subarreglos contiguos que suman k.
    Entrada: n, k y el arreglo de enteros.
    Salida: Cantidad total de subarreglos.
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n; long long k; if (!(cin >> n >> k)) return 0;
    unordered_map<long long, long long> prefix_counts;
    prefix_counts[0] = 1; long long current_sum = 0, total = 0;
    for (int i = 0; i < n; ++i) {
        long long val; cin >> val; current_sum += val;
        long long needed = current_sum - k;
        if (prefix_counts.count(needed)) total += prefix_counts[needed];
        prefix_counts[current_sum]++;
    }
    cout << total << "\\n";
    return 0;
}""",
        "14_Longest_Consecutive_Sequence.cpp": """/*
    Fuente: LeetCode 128 (Medium)
    Consigna: Encuentra la longitud de la secuencia consecutiva más larga presente en un arreglo desordenado (O(n)).
    Entrada: n y los elementos del arreglo.
    Salida: Longitud de la secuencia máxima.
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n; if (!(cin >> n)) return 0;
    unordered_set<int> s; for (int i = 0; i < n; ++i) { int x; cin >> x; s.insert(x); }
    int longest = 0;
    for (int num : s) {
        if (!s.count(num - 1)) {
            int current_num = num, current_streak = 1;
            while (s.count(current_num + 1)) { current_num++; current_streak++; }
            longest = max(longest, current_streak);
        }
    }
    cout << longest << "\\n";
    return 0;
}"""
    },
    "Seccion_4": {
        "15_Sum_of_Four_Values.cpp": """/*
    Fuente: CSES 1642 (Medium)
    Consigna: Encuentra cuatro posiciones distintas cuyos valores sumen exactamente x.
    Entrada: n, x y los elementos del arreglo.
    Salida: Las 4 posiciones (1-based) o IMPOSSIBLE.
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n; long long x; if (!(cin >> n >> x)) return 0;
    vector<long long> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
    unordered_map<long long, pair<int, int>> sum_map;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            long long target = x - a[i] - a[j];
            if (sum_map.count(target)) {
                auto p = sum_map[target];
                cout << p.first << " " << p.second << " " << (i + 1) << " " << (j + 1) << "\\n";
                return 0;
            }
        }
        for (int j = 0; j < i; ++j) sum_map[a[j] + a[i]] = {j + 1, i + 1};
    }
    cout << "IMPOSSIBLE\\n";
    return 0;
}""",
        "16_4Sum_II.cpp": """/*
    Fuente: LeetCode 454 (Medium)
    Consigna: Dados cuatro arreglos de longitud n, cuenta cuántas tuplas (i, j, k, l) suman exactamente cero.
    Entrada: n y luego los 4 arreglos de tamaño n.
    Salida: Cantidad total de tuplas con suma cero.
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n; if (!(cin >> n)) return 0;
    vector<int> nums1(n), nums2(n), nums3(n), nums4(n);
    for (int i = 0; i < n; ++i) cin >> nums1[i];
    for (int i = 0; i < n; ++i) cin >> nums2[i];
    for (int i = 0; i < n; ++i) cin >> nums3[i];
    for (int i = 0; i < n; ++i) cin >> nums4[i];
    unordered_map<int, int> sum_ab;
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) sum_ab[nums1[i] + nums2[j]]++;
    long long count = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int target = -(nums3[i] + nums4[j]);
            if (sum_ab.count(target)) count += sum_ab[target];
        }
    }
    cout << count << "\\n";
    return 0;
}"""
    }
}

base_dir = "Ejercicios_Hash"
os.makedirs(base_dir, exist_ok=True)

for seccion, archivos in estructura.items():
    sec_path = os.path.join(base_dir, seccion)
    os.makedirs(sec_path, exist_ok=True)
    for nombre_archivo, contenido in archivos.items():
        file_path = os.path.join(sec_path, nombre_archivo)
        with open(file_path, "w", encoding="utf-8") as f:
            f.write(contenido)

print("¡Carpeta 'Ejercicios_Hash' creada con éxito y con los enunciados dentro de cada archivo!")