#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>
#include <deque>
#include <iterator>
#include <algorithm>
#include <math.h>
#include<random>
#include <unordered_set>


using namespace std;

template <class T>
inline void hash_combine(std::size_t& seed, const T& v)
{
	seed ^= int(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

struct ObjectHasher
{
	std::size_t operator()(vector<vector<int>>  k) const
	{
		std::size_t hash = 0;
		for (int i = 0; i < k.size(); ++i) {
			for (int j = 0; j < k[i].size(); j++) {
					hash_combine(hash, k[i][j]);
				}
			}
		return hash;
	}
};

struct vertex {
	vector<vector<int>> a;


	bool operator==(const vertex &b) {
		if (a.size() != b.a.size()) return 0;
		for (int i = 0; i < a.size(); i++) {
			if (a[i].size() != b.a[i].size()) {
				return false;
			}
			for (int j = 0; j < a[i].size(); j++) {
				if (a[i][j] != b.a[i][j]) return false;
			}
		}
		return true;
	}
	//int cursize;
};



int main() {
	//freopen("input3.txt", "r", stdin);
	//freopen("output3.txt", "w", stdout);
	vector<vector<int>> begin(8);
	for (int i = 0; i < 8; i++) {
		cout << "Print cards of " << i + 1 << ' ' << "heap:" << '\n';
		string r;
		for (int j = 0; j < 9; j++) {
			cin >> r;
			if (r.length() == 2) {
				begin[i].push_back(10);
				continue;
			}
			char c = r[0];
			if (c >= '0' && c <= '9') begin[i].push_back(int(c - '0'));
			if (c == 'V') begin[i].push_back(11);
			if (c == 'D') begin[i].push_back(12);
			if (c == 'K') begin[i].push_back(13);
			if (c == 'T') begin[i].push_back(14);
		}
	}

	unordered_map<vector<vector<int>>, int, ObjectHasher> dist;

	dist[begin] = 0;

	deque<vector<vector<int>>> cur;
	cur.push_back(begin);

	while (cur.empty() != 0) {
		vector<vector<int>> now = cur[0];
		cur.pop_front();
		bool t = true;

		for (int i = 0; i < 8; i++) {
			if (now[i].size() != 0) {
				t = false;
			}
		}

		if (t) {
			cout << "YES for" << dist[now] << '\n';
			break;
		}

		for (int i = 0; i < 8; i++) {
			if (now[i].size() == 9) {
				bool l = true;
				for (int j = 1; j < 9; j++) {
					if (now[i][j] > now[i][j - 1]) l = false;
				}
				if (l) {
					vector<vector<int>> c = now;
					c[i] = vector<int>(0);
					if (dist[c] == 0) {
						dist[c] = dist[now];
						cur.push_front(c);
					}
				}
			}
			for (int j = 0; j < 9; j++) {
				if (i == j) continue;
				if (now[j].size() != 0 && now[i].back() < now[j].back()) {
					vector<vector<int>> r = now;
					int c = r[i].back();
					r[i].pop_back();
					r[j].push_back(c);
					if (dist[r] != 0) {
						dist[r] = dist[now] + 1;
						cur.push_back(r);
					}
				}
			}
		}
	}
	cout << "NO" << endl;
	//system("pause");
	return 0;
}
