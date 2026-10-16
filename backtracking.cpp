
#include <bits/stdc++.h>
using namespace std;
vector<int> actual;
//resolver nsuma 
void resolver(int restante, int maximo) {
    if (restante == 0) {
        for (int i = 0; i < (int)actual.size(); i++) {
            if (i > 0) cout << " ";
            cout << actual[i];
        }
        cout << "\n";
        return;
    }

    for (int x = min(restante, maximo); x >= 1; x--) {
        actual.push_back(x);

        resolver(restante - x, x);

        actual.pop_back();
    }
}

//parentesis
void resolver(int n, int abiertos, int cerrados, string actual) {
    if ((int)actual.size() == 2 * n) {
        cout << actual << '\n';
        return;
    }

    if (abiertos < n) {
        resolver(n, abiertos + 1, cerrados, actual + "(");
    }

    if (cerrados < abiertos) {
        resolver(n, abiertos, cerrados + 1, actual + ")");
    }
}

//resolver 
vector<int> a = {1, 2, 3, 4};
vector<int> elegidos;

void backtracking(int i) {
    if (i == (int)a.size()) {
        cout << "{ ";
        for (int x : elegidos) cout << x << " ";
        cout << "}\n";
        return;
    }

    elegidos.push_back(a[i]);
    backtracking(i + 1);

    elegidos.pop_back();

    backtracking(i + 1);
}

int main() {
    backtracking(0);
}
