/**
Solution based on this problem: https://www.spoj.com/problems/DISUBSTR/
not on the ioi syllabus
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
 
int te, n, lcp[N], id[N];
string s;
inline vector <int> build() {
    int cnt[N];
    int cur = 0, cn[N], c[N], p[N], pn[N], cnt2[N];
    memset(cnt, 0, sizeof cnt);
    fo(i, 0, n, 1) cn[i] = c[i] = p[i] = pn[i] = 0;
    for (int i = 0; i < n; ++i) cnt[s[i]]++;
    fo(i, 1, 255, 1) cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; --i) p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    for (int i = 1; i < n; ++i) {
        if (s[p[i]] != s[p[i - 1]]) ++cur;
        c[p[i]] = cur;
    }
    for (int h = 0; (1 << h) < n; ++h) {
        for (int i = 0; i < n; ++i) pn[i] = (p[i] - (1 << h)) + (p[i] - (1 << h) < 0 ? n : 0);
        memset(cnt, 0, sizeof cnt);
        for (int i = 0; i < n; ++i) ++cnt[c[pn[i]]];
        int prev = -1;
        fo(i, 1, cur, 1) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; --i) p[--cnt[c[pn[i]]]] = pn[i];
        cur = 0;
        cn[p[0]] = 0;
        for (int i = 1; i < n; ++i) {
            int f = p[i] + (1 << h), s = p[i - 1] + (1 << h);
            f %= n;
            s %= n;
            if (c[p[i]] != c[p[i - 1]] || c[f] != c[s]) ++cur;
            cn[p[i]] = cur;
        }
        fo(i, 0, n, 1) c[i] = cn[i];
    }
    vector <int> ret;
    for (int i = 1; i < n; ++i) ret.eb(p[i]);
    return ret;
}
main() {
    file("console");
    ios;
    cin >> te;
    while (te--) {
        cin >> s;
        s = s + ' ';
        n = s.size();
        memset(id, 0, sizeof id);
        memset(lcp, 0, sizeof lcp);
        vector <int> suff = build();
        s.pop_back();
        n = suff.size();
        for (int i = 0; i < n; ++i) id[suff[i]] = i;
        int len =  0;
        for (int i = 0; i < n; ++i) {
            if (id[i] == n - 1) {
                len = 0;
                continue;
            }
            int j = suff[id[i] + 1];
            while (i + len < n && j + len < n && s[i + len] == s[j + len]) ++len;
            lcp[id[i]] = len;
            if (len > 0) --len;
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) ans += n - suff[i] - lcp[i];
        cout << ans << "\n";
    }
    return 0;
}
