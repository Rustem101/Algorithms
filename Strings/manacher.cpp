//#pragma GCC optimize ("Ofast")
//#pragma GCC optimize ("unroll-loops")
//#pragma GCC target("avx,avx2,fma")

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
//using namespace __gnu_pbds;
//using namespace __gnu_cxx;


using ll = long long;

//#define int ll

using pii = pair<int,int>;
using pll = pair<ll,ll>;
using vi = vector<int>;



const int N = 2e5 + 11, mod = 1e9 + 7, mod2 = 998244353;
const int MAX = 1e5 + 11;
const int INF1 = 2e9 + 11;
const ll INF2 = 6e18 + 11;
const double INF3 = 1e8 + 11;
const int base = 500;
const int P = 31;
const int dx[] = {1, -1, 0, 0, 1, 1, -1, -1};
const int dy[] = {0, 0, 1, -1, 1, -1, 1, -1};
const double EPS = 1e-4;
const double PI = acos(-1.0);


//template<typename T> using ordered_set = tree <T, null_type, less <T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T1, typename T2> inline void chmin(T1 &a, T2 b) { if (a > b) a = b; }
template<typename T1, typename T2> inline void chmax(T1 &a, T2 b) { if (a < b) a = b; }


mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());


main() {
  file("threesum");
  ios;
  function<ll(string)> manacher = [&](string s) {
    vector <int> d1(n), d2(n);
    int l = 0, r = -1;
    ll ret = 0;
    for (int i = 0; i < n; ++i) {
      if (i <= r) d1[i] = min(r - i + 1, d1[l + r - i]);
      else d1[i] = 1;
      while (i - d1[i] >= 0 and i + d1[i] < n and s[i - d1[i]] == s[i + d1[i]]) ++d1[i];
      if (i + d1[i] - 1 > r) l = i - d1[i] + 1, r = i + d1[i] - 1;
    }
    l = 0, r = -1;
    for (int i = 0; i < n; ++i) {
      if (i <= r) d2[i] = min(r - i + 1, d2[l + r - i + 1]);
      while (i - d2[i] - 1 >= 0 and i + d2[i] < n and s[i + d2[i]] == s[i - d2[i] - 1]) ++d2[i];
      if (i + d2[i] - 1 > r) l = i - d2[i], r = i + d2[i] - 1;
      ret += d1[i] + d2[i];
    }
    return ret;
  };
  return 0;
}
/**

*/
