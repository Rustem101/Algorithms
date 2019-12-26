/**

problem: https://usaco.org/index.php?page=viewproblem2&cpid=970

     .=     ,        =.
  _  _   /'/    )\,/,/(_   \ \
   `//-.|  (  ,\\)\//\)\/_  ) |
   //___\   `\\\/\\/\/\\///'  /
,-"~`-._ `"--'_   `"""`  _ \`'"~-,_
\       `-.  '_`.      .'_` \ ,-"~`/
 `.__.-'`/   (-\        /-) |-.__,'
   ||   |     \O)  /^\ (O/  | .        <-  BESSIE THE COW
   `\\  |         /   `\    /
     \\  \       /      `\ /
      `\\ `-.  /' .---.--.\
        `\\/`~(, '()      ('
         /(O) \\   _,.-.,_)
        //  \\ `\'`      /
       / |  ||   `""""~"`
     /'  |__||
           `o

*/

#pragma GCC optimize ("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("avx,avx2,fma")


#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
#define pb push_back
#define F first
#define S second
#define ins insert
#define mp make_pair
#define fo(i, n1, n, x) for(int i = n1; i <= n; i += x)
#define foo(i, n, n1, x) for(int i = n; i >= n1; i -= x)
#define bit __builtin_popcount
#define md (l + ((r - l) / 2))
#define all(x) x.begin(),x.end()
#define eb emplace_back
#define ub upper_bound
#define lb lower_bound
#define ios ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define file(s) if (fopen(s".in", "r")) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;

using ll = long long;

const int N = 2e5 + 11, mod = 1e9 + 7, mod2 = 998244353;
const int MAX = 1e5 + 11;
const int INF1 = 2e9 + 11;
const ll INF2 = 2e18 + 11;
const double INF3 = 1e8 + 11;
const int base = 500;
const int P = 31;
const int dx[] = {1, -1, 0, 0, 1, 1, -1, -1};
const int dy[] = {0, 0, 1, -1, 1, -1, 1, -1};
const double EPS = 1e-4;
const double PI = acos(-1.0);


template<typename T> using ordered_set = tree <T, null_type, less <T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T1, typename T2> inline void chmin(T1 &a, T2 b) { if (a > b) a = b; }
template<typename T1, typename T2> inline void chmax(T1 &a, T2 b) { if (a < b) a = b; }


bool DEBUG = 1;
#define debug(x) if (DEBUG) {cerr << #x << " = " << x << "\n";}
#define debug_vec(x) if (DEBUG) {cerr << #x << " = {"; for(auto a : x) cerr << a << ","; cerr << "}" << endl;}

//#define int ll

typedef pair <int, int> pii;
typedef pair <ll, ll> pll;
typedef vector <int> vi;


mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int n, m, timer, tin[N], tout[N], a[N], res, up[33][N], t[N], ans[N], has[N];

bitset <100010> parity;
vi g[N];

struct query {
    int l, r, c, id, LCA;
    bool flag = 0;
} q[N];

bool cmp(query a, query b) {
    if (a.l / 320 != b.l / 320) return a.l < b.l;
    return a.r < b.r;
}

void dfs(int v, int pr) {
    tin[v] = ++timer;
    a[tin[v]] = v;
    up[0][v] = pr;
    fo(i, 1, 20, 1) up[i][v] = up[i - 1][up[i - 1][v]];
    for (int to : g[v]) {
        if (to != pr) dfs(to, v);
    }
    tout[v] = ++timer;
    a[tout[v]] = v;
}

bool upper(int a, int b) { return (tin[a] <= tin[b] and tout[b] <= tout[a]) ;}

int lca(int a, int b) {
    if (upper(a, b)) return a;
    if (upper(b, a)) return b;
    foo(i, 20, 0, 1) {
        if (!upper(up[i][a], b) and up[i][a]) a = up[i][a];
    }
    return up[0][a];
}

void f(int x) {
    if (!parity[a[x]]) has[t[a[x]]]++;
    else has[t[a[x]]]--;
    parity[a[x]].flip();
}
main() {
    file("milkvisits");
    ios;
    cin >> n >> m;
    fo(i, 1, n, 1) cin >> t[i];
    fo(i, 1, n - 1, 1) {
        int u, v;
        cin >> u >> v;
        g[u].eb(v);
        g[v].eb(u);
    }
    dfs(1, 1);
    fo(i, 1, m, 1) {
        cin >> q[i].l >> q[i].r >> q[i].c;
        q[i].id = i;
        if (tin[q[i].l] > tin[q[i].r]) swap(q[i].l, q[i].r);
        q[i].LCA = lca(q[i].l, q[i].r);
        if (q[i].LCA == q[i].l) {
            q[i].flag = 0;
            q[i].l = tin[q[i].l];
            q[i].r = tin[q[i].r];
        } else {
            q[i].flag = 1;
            q[i].l = tout[q[i].l];
            q[i].r = tin[q[i].r];
        }
    }
    sort(q + 1, q + m + 1, &cmp);
    int l = 0, r = 0;
    fo(i, 1, m, 1) {
        while (l < q[i].l) f(l++);
        while (l > q[i].l) f(--l);
        while (r < q[i].r) f(++r);
        while (r > q[i].r) f(r--);
        if (q[i].flag) f(tin[q[i].LCA]);
        ans[q[i].id] = (has[q[i].c] > 0);
        if (q[i].flag) f(tin[q[i].LCA]);
    }
    fo(i, 1, m, 1) cout << ans[i];
    cerr << "\nTime elapsed: " << (clock() + 0.0) / CLOCKS_PER_SEC;
    return 0;
}
/**

*/
