
struct LCA {
	int di[N];
	int in[N];
	int lg[N];
	pair<int,int> st[20][N];

	vector < pair < int, int > > order;
	void zfs (int v, int dist = 0, int pr = 0) {
		in[v] = order.size();
		order.pb({dist, v});
		di[v] = dist;
		for (auto to : g[v]) if (to != pr) {
			zfs(to, dist + 1, v);
			order.pb({dist, v});
		}
	}
	void clear() {
		order.clear();
	}

	int lca (int a, int b) {
		a = in[a];
		b = in[b];
		if (a > b) swap(a, b);
		int len = b - a + 1;
		len = lg[len];
 
		return min(st[len][a], st[len][b - (1 << len) + 1]).S;
	}

	int dist (int a, int b) {	
		return di[a] + di[b] - 2 * di[lca(a, b)];
	}

	void build () {
		for (int j = 2; j < N; j ++)
			lg[j] = lg[j / 2] + 1;
 
		for (int i = 0; i < order.size(); i ++) {
			st[0][i] = order[i];
		}
 
		for (int i = 1; i <= lg[order.size()]; i ++) {
			for (int j = 0; j + (1 << i) - 1 < order.size(); j ++) {
				st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
			}
		}
	}
} ;
