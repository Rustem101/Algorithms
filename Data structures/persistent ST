#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
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
#define ll long long
#define ld long double
#define eb emplace_back
#define ub upper_bound
#define lb lower_bound
#define ios ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define file(s) if (fopen(s".in", "r")) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)
 
using namespace std;
 
const int N = 1e5 + 11, mod = 1e9 + 7;
const int MAX = 2e7;
const int INF1 = 2e9 + 11;
const ll INF2 = 2e18 + 11;
const int base = 500;
const int P = 31;
const int dx[] = {1, -1, 0, 0, 1, 1, -1, -1};
const int dy[] = {0, 0, 1, -1, 1, -1, 1, -1};
const double EPS = 1e-9;
const double PI = acos(-1.0);
 
class Problems {
private:
    int n, q, a[N];
    map<int,int>id, m, val;
    struct node {
        node *l, *r;
        int val;
        node() {}
        node(node *left, node *right, int vl) {
            l = left;
            r = right;
            val = vl;
        }
    };
    node *version[N];
public:
    inline void build(node *cur, int l, int r) {
        if (l == r) {
            cur->val = 0;
            return;
        }
        cur->l = new node(NULL, NULL, 0);
        cur->r = new node(NULL, NULL, 0);
        build(cur->l, l, md);
        build(cur->r, md + 1, r);
    }
    inline void upd(node *prev, node *cur, int l, int r, int pos) {
        if (l == r) {
            cur->val = prev -> val + 1;
            return;
        }
        if (pos <= md) {
            cur -> r = prev -> r;
            cur->l = new node(NULL, NULL, 0);
            upd(prev->l, cur->l, l, md, pos);
        } else {
            cur->l = prev->l;
            cur->r = new node(NULL, NULL, 0);
            upd(prev->r, cur->r, md + 1, r, pos);
        }
        cur->val = cur->l->val + cur->r->val;
    }
    inline int get(node *prev, node *cur, int l, int r, int k) {
        if (l == r) return l;
        int cnt = cur->l->val - prev->l->val;
        if (k <= cnt) return get(prev->l, cur->l, l, md, k);
        else return get(prev->r, cur->r, md + 1, r, k - cnt);
    }
    inline void Solution() {
        cin >> n >> q;
        fo(i, 1, n, 1) {
            cin >> a[i];
            m[a[i]];
        }
        int cnt = 0;
        for (auto & it : m) {
            id[it.F] = ++cnt;
            val[cnt] = it.F;
        }
        version[0] = new node(NULL, NULL, 0);
        build(version[0], 1, n);
        fo(i, 1, n, 1) {
            version[i] = new node(NULL, NULL, 0);
            upd(version[i - 1], version[i], 1, n, id[a[i]]);
        }
        while (q--) {
            int l, r, k;
            cin >> l >> r >> k;
            cout << val[get(version[l - 1], version[r], 1, n, k)] << "\n";
        }
    }
} Problem;
main() {
    file("lca");
    ios;
    Problem.Solution();
    return 0;
}
/**
 
*/
 
