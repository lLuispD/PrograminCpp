#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Usamos long long porque los puntajes pueden ser muy grandes o pequeños.
using ll = long long;

// Un valor muy pequeño para representar -infinito
const ll INF = 1e18;

// Ancho de la banda. Un poco más que 100 por seguridad.
const int K = 105;
// Límite de búsqueda para los gaps (k). 2*K + 5 es un límite seguro.
const int MAX_K_SEARCH = 2 * K + 5;

int n, m;
int match, mismatch, gap_cost;
string a, b;

// La tabla de DP. [índice i][índice j mapeado][estado]
// Dimensiones: (n+1) x (2*K + 1) x 3
vector<vector<vector<ll>>> dp;

// Función para obtener el puntaje de match/mismatch
int get_score(char c1, char c2) {
    return (c1 == c2) ? match : mismatch;
}

// Mapea la coordenada (i, j) a un índice en nuestra banda
// j_mapeado = j - i + K. El centro (i=j) se mapea a K.
int map_j(int i, int j) {
    return j - i + K;
}

// Comprueba si (i, j) está dentro de nuestra banda
bool is_in_band(int i, int j) {
    return abs(i - j) <= K;
}

// Función segura para obtener valores de la tabla DP.
// Devuelve -INF si está fuera de los límites o fuera de la banda.
ll get_dp(int i, int j, int state) {
    if (i < 0 || j < 0 || i > n || j > m) {
        return -INF;
    }
    if (!is_in_band(i, j)) {
        return -INF;
    }
    return dp[i][map_j(i, j)][state];
}

int main() {
    // Optimización de I/O en C++
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> a >> m >> b >> match >> mismatch >> gap_cost;

    // Inicializar la tabla de DP con -INF
    dp.assign(n + 1, vector<vector<ll>>(2 * K + 1, vector<ll>(3, -INF)));

    // --- Casos Base ---

    // 1. (0, 0): No hay alineación, costo 0.
    // Estado 0: match/mismatch, 1: gap en b, 2: gap en a
    dp[0][map_j(0, 0)][0] = 0;

    // 2. Eje Y (i > 0, j = 0): Solo gaps en b
    for (int i = 1; i <= n; ++i) {
        if (!is_in_band(i, 0)) break;
        dp[i][map_j(i, 0)][1] = (ll)i * i * gap_cost;
    }

    // 3. Eje X (i = 0, j > 0): Solo gaps en a
    for (int j = 1; j <= m; ++j) {
        if (!is_in_band(0, j)) break;
        dp[0][map_j(0, j)][2] = (ll)j * j * gap_cost;
    }

    // --- Llenado de la Tabla (Programación Dinámica) ---

    for (int i = 1; i <= n; ++i) {
        // Solo iteramos j dentro de la banda alrededor de i
        for (int j = max(1, i - K); j <= min(m, i + K); ++j) {

            int mj = map_j(i, j); // Índice j mapeado

            // --- Estado 0: a[i] se alinea con b[j] (Match/Mismatch) ---
            // Puede venir de cualquiera de los 3 estados en (i-1, j-1)
            ll prev_diag = max({ get_dp(i - 1, j - 1, 0),
                                get_dp(i - 1, j - 1, 1),
                                get_dp(i - 1, j - 1, 2) });

            if (prev_diag > -INF) {
                dp[i][mj][0] = prev_diag + get_score(a[i - 1], b[j - 1]);
            }

            // --- Estado 1: a[i] se alinea con un gap ('-') ---
            // Buscamos un bloque de gap de longitud k (de 1 a i)
            ll max_gap_b = -INF;
            for (int k = 1; k <= i && k < MAX_K_SEARCH; ++k) {
                // Viene de un estado (i-k, j) que NO sea un gap en b
                ll prev_state = max(get_dp(i - k, j, 0), get_dp(i - k, j, 2));
                if (prev_state > -INF) {
                    max_gap_b = max(max_gap_b, prev_state + (ll)k * k * gap_cost);
                }
            }
            dp[i][mj][1] = max_gap_b;

            // --- Estado 2: b[j] se alinea con un gap ('-') ---
            // Buscamos un bloque de gap de longitud k (de 1 a j)
            ll max_gap_a = -INF;
            for (int k = 1; k <= j && k < MAX_K_SEARCH; ++k) {
                // Viene de un estado (i, j-k) que NO sea un gap en a
                ll prev_state = max(get_dp(i, j - k, 0), get_dp(i, j - k, 1));
                if (prev_state > -INF) {
                    max_gap_a = max(max_gap_a, prev_state + (ll)k * k * gap_cost);
                }
            }
            dp[i][mj][2] = max_gap_a;
        }
    }

    // --- Resultado Final ---
    // La respuesta es el máximo de los 3 estados en la celda (n, m)
    ll final_score = max({ get_dp(n, m, 0),
                          get_dp(n, m, 1),
                          get_dp(n, m, 2) });

    cout << final_score << endl;

    return 0;
}