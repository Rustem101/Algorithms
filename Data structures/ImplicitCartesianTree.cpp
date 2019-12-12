//#pragma GCC optimize ("Ofast")
//#pragma GCC optimize ("unroll-loops")
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

using ll = long long;

const int N = 1e5 + 11, mod = 1e9 + 7, mod2 = 998244353;
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


mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());


int n, m;
struct node {
    node *l, *r;
    int y, val, sz, mn;
    bool rev;
    node() {}
    node (int val_, int y_) {
        y = y_;
        val = mn = val_;
        sz = 1;
        rev = 0;
        l = r = NULL;
    }
};

typedef node * pnode;

pnode root;

int get_sz(pnode t) {
    if (t == NULL) return 0;
    return t->sz;
}

int get_min(pnode t) {
    if (t == NULL) return INF1;
    return t->mn;
}

void push(pnode &t) {
    if (t == NULL || t->rev == 0) return;
    swap(t->l, t->r);
    if (t->l) t->l->rev ^= 1;
    if (t->r) t->r->rev ^= 1;
    t->rev = 0;
}

void upd(pnode &t) {
    if (t == NULL) return;
    t->sz = get_sz(t->l) + 1 + get_sz(t->r);
    t->mn = min(t->val, min(get_min(t->l), get_min(t->r)));
}

void merge(pnode &t, pnode a, pnode b) {
    push(a), push(b);
    if (!a) {
        t = b;
    } else {
        if (!b) {
            t = a;
        } else {
            if (a->y > b->y) {
                merge(a->r, a->r, b);
                t = a;
            } else {
                merge(b->l, a, b->l);
                t = b;
            }
        }
    }
    upd(t);
}

void split(pnode t, pnode &l, pnode &r, int k) {
    push(t);
    if (!t) l = r = NULL;
    else {
        int sz = get_sz(t->l) + 1;
        if (sz <= k) {
            split(t->r, t->r, r, k - sz);
            l = t;
        } else {
            split(t->l, l, t->l, k);
            r = t;
        }
    }
    upd(t);
}

void rev(int left, int right) {
    pnode a, b;
    split(root, root, a, left - 1);
    split(a, a, b, right - left + 1);
    a->rev ^= 1;
    merge(root, root, a);
    merge(root, root, b);
}

int get(int l, int r) {
    pnode a, b;
    split(root, root, a, l - 1);
    split(a, a, b, r - l + 1);
    int ret = get_min(a);
    merge(root, root, a);
    merge(root, root, b);
    return ret;
}
main() {
    file("dirtraverse");
    //ios;
    cin >> n >> m;
    root = NULL;
    fo(i, 1, n, 1) {
        int x;
        cin >> x;
        pnode add = new node(x, rand());
        merge(root, root, add);
    }
    while (m --) {
        int type, l, r;
        cin >> type >> l >> r;
        if (type == 1) rev(l, r);
        else cout << get(l, r) << "\n";
    }
    cerr << "\nTime elapsed: " << (clock() + 0.0) / CLOCKS_PER_SEC;
    return 0;
}
/**
5 100

1 2 3 4 5

*/
