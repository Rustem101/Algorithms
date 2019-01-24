/*
Heavy-light decomposition
Solution based on problem: https://www.spoj.com/problems/QTREE/
*/

#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,sse3,sse4,popcnt,abm,mmx")
#include <bits/stdc++.h>
#define pb push_back
#define F first
#define S second
#define ins insert
#define mp make_pair
#define mt make_tuple
#define fo(i, n1, n, x) for(int i = n1; i <= n; i += x)
#define foo(i, n, n1, x) for(int i = n; i >= n1; i -= x)
#define bit __builtin_popcount
#define md (l + ((r - l) / 2))
#define all(x) x.begin(),x.end()
#define ll long long
#define ld long double
#define eb emplace_back
#define ub upper_bound
#define lb lower_bound
#define ios ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define file(s) if (fopen(s".in", "r")) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

using namespace std;

const int N = 1e4 + 11, mod = 1e9 + 7, mod2 = 998244353;
const int MAX = 6e5 + 11;
const int INF1 = 2e9 + 11;
const ll INF2 = 2e18 + 11;
const int base = 500;
const int P = 31;
const int dx[] = {1, -1, 0, 0, 1, 1, -1, -1};
const int dy[] = {0, 0, 1, -1, 1, -1, 1, -1};
const double EPS = 1e-9;
const double PI = acos(-1.0);

template<typename T1, typename T2> inline void chmin(T1 &a, T2 b) { if (a > b) a = b; }
template<typename T1, typename T2> inline void chmax(T1 &a, T2 b) { if (a < b) a = b; }

int te, tin[N], tout[N], timer, up[22][N], chainNum = 1, ptr, vert[N], sz[N], t[N * 4], chainPos[N], chainId[N], chainST[N];
int price[N], d[N];
vector <int> idd[N];
vector < pair <int,int> > g[N];
inline void dfs(int v, int pr, int depth) {
    tin[v] = ++timer;
    d[v] = depth;
    up[0][v] = pr;
    sz[v] = 1;
    fo(i, 1, 17, 1) up[i][v] = up[i - 1][up[i - 1][v]];
    for (int i = 0; i < g[v].size(); ++i) {
        pair <int,int> to = g[v][i];
        if (to.F != pr) {
            vert[idd[v][i]] = to.F;
            dfs(to.F, v, depth + 1);
            sz[v] += sz[to.F];
        }
    }
    tout[v] = timer;
}
inline bool upper(int a, int b) {
    return (tin[a] <= tin[b] && tout[b] <= tout[a]);
}
inline int lca(int a, int b) {
    if (upper(a, b)) return a;
    if (upper(b, a)) return b;
    foo(i, 14, 0, 1) if (!upper(up[i][a], b) && up[i][a]) a = up[i][a];
    return up[0][a];
}
inline void buildHLD(int v, int cost, int pr) {
    if (chainST[chainNum] == -1) {
        chainST[chainNum] = v;
    }
    chainPos[v] = ++ptr;
    chainId[v] = chainNum;
    price[ptr] = cost;
    int idx = -1;
    int cc;
    for (auto & to : g[v]) {
        if (to.F == pr) continue;
        if (idx == -1 || sz[to.F] > sz[idx]) {
            idx = to.F;
            cc = to.S;
        }
    }
    if (~idx) buildHLD(idx, cc, v);
    for (auto & to : g[v]) {
        if (to.F != pr && to.F != idx) {
            ++chainNum;
            buildHLD(to.F, to.S, v);
        }
    }
}
inline int get(int v, int l, int r, int left, int right) {
    if (left > r || right < l) return -1;
    if (left <= l && r <= right) return t[v];
    int val1 = get(v + v, l, md, left, right);
    int val2 = get(v + v + 1, md + 1, r, left, right);
    return (val1 > val2 ? val1 : val2);
}
inline void upd(int v, int l, int r, int pos, int val) {
    if (l == r) {
        t[v] = val;
        return;
    }
    pos <= md ? upd(v + v, l, md, pos, val) : upd(v + v + 1, md + 1, r, pos, val);
    t[v] = (t[v + v] > t[v + v + 1] ? t[v + v] : t[v + v + 1]);
}
inline void buildST(int v, int l, int r) {
    if (l == r) {
        t[v] = price[l];
        return;
    }
    buildST(v + v, l, md);
    buildST(v + v + 1, md + 1, r);
    t[v] = (t[v + v] > t[v + v + 1] ? t[v + v] : t[v + v + 1]);
}
inline int go_up(int u, int v) {
    int uchain, vchain = chainId[v], ans = -1;
    while (1) {
        uchain = chainId[u];
        if (uchain == vchain) {
            if (u == v) break;
            chmax(ans, get(1, 1, ptr, chainPos[v] + 1, chainPos[u]));
            break;
        }
        chmax(ans, get(1, 1, ptr, chainPos[chainST[uchain]], chainPos[u]));
        u = up[0][chainST[uchain]];
    }
    return ans;
}
main() {
    file("console");
    scanf("%d", &te);
    while (te--) {
        int n;
        scanf("%d", &n);
        fo(i, 1, n, 1) {
            g[i].clear();
            idd[i].clear();
            chainST[i] = -1;
            fo(j, 0, 14, 1) up[j][i] = 0;
        }
        fo(i, 1, n - 1, 1) {
            int u, v, cost;
            scanf("%d %d %d", &u, &v, &cost);
            g[u].pb({v, cost});
            g[v].pb({u, cost});
            idd[u].eb(i);
            idd[v].eb(i);
        }
        ptr = 0;
        chainNum = 1;
        dfs(1, 0, 0);
        buildHLD(1, 0, 0);
        buildST(1, 1, ptr);
        while (1) {
            char s[33];
            scanf(" %s", &s);
            if (s[0] == 'D') break;
            int a, b;
            scanf("%d %d", &a, &b);
            if (s[0] == 'C') upd(1, 1, ptr, chainPos[vert[a]], b);
            else {
                int l = lca(a, b);
                int ans = go_up(a, l);
                int val = go_up(b, l);
                if (ans < val) ans = val;
                printf("%d\n", ans);
            }
        }
    }
    return 0;
}
