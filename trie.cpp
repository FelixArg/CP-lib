// static array trie
struct Trie {
	struct node {
		int cnt;
		// fix alphabet size!
		int to[26];
		node() {
			cnt = 0;
			memset(to, -1, sizeof(to));
		}
	};

	//fix constant!
	node data[1000 + 1];
	int free = 1;

	void add(string& s) {
		int cur = 0;
		int sz = s.size();
		for (int i = 0; i < sz; i++) {
			int next = s[i] - 'a';
			if (data[cur].to[next] == -1) {
				data[cur].to[next] = free++;
			}
			cur = data[cur].to[next];
		}
		data[cur].cnt++;
	}

	void del(string& s) {
		int cur = 0;
		int sz = s.size();
		for (int i = 0; i < sz; i++) {
			int next = s[i] - 'a';
			if (data[cur].to[next] == -1)
				return;
			cur = data[cur].to[next];
		}
		data[cur].cnt = max(0, data[cur].cnt - 1);
	}

	bool in_trie(string& s) {
		int cur = 0;
		int sz = s.size();
		for (int i = 0; i < sz; i++) {
			int next = s[i] - 'a';
			if (data[cur].to[next] == -1)
				return 0;
			cur = data[cur].to[next];
		}
		return data[cur].cnt > 0;
	}
};


// map trie(less memory, more time)
struct Trie {
	struct node {
		int cnt;
		map<char, int> to;
		node() {
			cnt = 0;
		}
	};

	//fix constant!
	node data[1000 + 1];
	int free = 1;

	void add(string& s) {
		int cur = 0;
		int sz = s.size();
		for (int i = 0; i < sz; i++) {
			char next = s[i];
			if (data[cur].to.count(next) == 0) {
				data[cur].to[next] = free++;
			}
			cur = data[cur].to[next];
		}
		data[cur].cnt++;
	}

	void del(string& s) {
		int cur = 0;
		int sz = s.size();
		for (int i = 0; i < sz; i++) {
			char next = s[i];
			if (data[cur].to.count(next) == 0)
				return;
			cur = data[cur].to[next];
		}
		data[cur].cnt = max(0, data[cur].cnt - 1);
	}

	bool in_trie(string& s) {
		int cur = 0;
		int sz = s.size();
		for (int i = 0; i < sz; i++) {
			char next = s[i];
			if (data[cur].to.count(next) == 0)
				return 0;
			cur = data[cur].to[next];
		}
		return data[cur].cnt > 0;
	}
};


//static array Aho-Corasick
struct Trie_AC {
	struct node {
		int cnt;
		int p;
		int ch;
		int link;
		// fix alphabet size!
		int to[26];
		int go[26];
		node() {
			cnt = 0;
			p = -1;
			link = -1;
			ch = -1;
			memset(to, -1, sizeof(to));
			memset(go, -1, sizeof(go));
		}
	};

	//fix constant!
	node data[1000 + 1];
	int free = 1;

	void add(string& s) {
		int cur = 0;
		int sz = s.size();
		for (int i = 0; i < sz; i++) {
			int next = s[i] - 'a';
			if (data[cur].to[next] == -1) {
				data[cur].to[next] = free++;
				data[free - 1].ch = next;
				data[free - 1].p = cur;
			}
			cur = data[cur].to[next];
		}
		data[cur].cnt++;
	}

	int go(int x, int ch) {
		if (data[x].go[ch] == -1) {
			if (data[x].to[ch] == -1)
				return data[x].go[ch] = x == 0 ? 0 : go(link(x), ch);
			else
				return data[x].go[ch] = data[x].to[ch];
		}
		return data[x].go[ch];
	}

	int link(int x) {
		if (data[x].link == -1) {
			if (x == 0 || data[x].p == 0)
				return data[x].link = 0;
			else
				return data[x].link = go(link(data[x].p), data[x].ch);
		}
		return data[x].link;
	}
};