#include <bits/stdc++.h>
using namespace std;

//Lista para strings el orden etc 
template<typename key_type, typename value_type>
struct my_map_S {
	int m;
	int _size;
	vector<vector<pair<key_type, value_type>>> chains;
	my_map_S(int m = 1) : m(m), _size(0) {
		chains.resize(m);
	}
	value_type& operator [] (const key_type &key) {
		int chain_position = _hash(key);
		int at = 0;
		while (at < chains[chain_position].size() and chains[chain_position]
		[at].first != key) {
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
		while (at < chains[chain_position].size() and chains[chain_position]
		[at].first != key) {
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
		while (at < chains[chain_position].size() and chains[chain_position]
		[at].first != key) {
			++at;
		}
		if (at == chains[chain_position].size()) {
			return false;
		}
		return true;
	}
	int _hash(key_type key) const {
		const int B = 311;
		const int MOD = 1e9 + 7;
		int hash_value = 0;
		for (int i =0; i <key.size(); ++i) {
			int c = key[i] - 'a'+ 1;
			hash_value = (1ll * hash_value * B + c) % MOD;
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
void linear_sort(string &s) {
	vector<int>frec(26, 0);
	for (auto&c:s) {
		++frec[c - 'a'];
	}
	int ptr_s = 0;
	for (int i= 0; i < 26; ++i) {
		while (frec[i] >0) {
			s[ptr_s++] = i + 'a';
			frec[i]--;
		}
	}
}
int main() {
	cin.tie(0)->sync_with_stdio(false);
	int n ;
	cin >> n;
	my_map_S<string, int> M(4*n);
	for (int i = 0; i < n; ++i) {
		string s;
		cin >> s;
		linear_sort(s);
		M[s];
	}
	cout << M.size();
	return 0;
}
