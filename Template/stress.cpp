#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
//#include <chrono>
//#include <random>
//#include <unordered_map>

using namespace std;

typedef long long ll;
//mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

int fast() {
	return 0;
}

int slow() {
	return 0;
}

int gen() {
	return 0;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
#if defined(_DEBUG)
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
#endif
	int test = 1;
	while (1) {
		cout << test++ << '\n';

		int t = gen();
		int res1 = fast(), res2 = slow();
		if (res1 != res2) {
			freopen("output.txt", "w", stdout);
			//out
			return;
		}
	}
}