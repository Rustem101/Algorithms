/**
find problems on informatics.mccme.ru
*/
//#pragma GCC optimize("Ofast")
//#pragma GCC target("avx,avx2,fma")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
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

typedef long long ll;
typedef long double ld;

const int N = 3e5 + 11, mod = 1e9 + 7, mod2 = 998244353;
const int MAX = 3e5 + 11;
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

#define int ll

typedef pair <int, int> pii;
typedef pair <ll, ll> pll;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());


char op[N];

int res[N], n;

struct node {
    int x, y;
    node *l, *r;
    node() {}
    node(int x_, int y_) {
        x = x_;
        y = y_;
        l = NULL;
        r = NULL;
    }
};

typedef node * pnode;

pnode root = NULL;

inline void merge(pnode &t, pnode l, pnode r) {
    if (!l || !r) {
        t = (l ? l : r);
        return;
    }
    if (l->y > r->y) {
        merge(l->r, l->r, r);
        t = l;
    } else {
        merge(r->l, l, r->l);
        t = r;
    }
}
inline void split(pnode t, pnode &l, pnode &r, int x) {
    if (!t) {
        l = r = NULL;
        return;
    }
    if (t->x <= x) {
        split(t->r, t->r, r, x);
        l = t;
    } else {
        split(t->l, l, t->l, x);
        r = t;
    }
}
inline void add(pnode &t, pnode v) {
    if (!t) t = v;
    else {
        if (v->y > t->y) {
            split(t, v->l, v->r, v->x);
            t = v;
        } else {
            if (t->x < v->x) add(t->r, v);
            else add(t->l, v);
        }
    }
}
inline int get(pnode t, int val) {
    if (!t) return INF1;
    if (t->x < val) return get(t->r, val);
    return min(t->x, get(t->l, val));
}
main() {
    file("next");
    ios;
    cin >> n;
    fo(i, 1, n, 1) {
        int x;
        cin >> op[i] >> x;
        if (op[i] == '+') {
            if (!(i == 1 || op[i - 1] == '+')) x = (x + res[i - 1]) % (1000000000);
            pnode p = new node(x, uniform_int_distribution<int> (1, INF1) (rng));
            add(root, p);
        } else {
            res[i] = get(root, x);
            if (res[i] == INF1) res[i] = -1;
            cout << res[i] << "\n";
        }
    }
    return 0;
}
/**

*/
