/**
timus 1469
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,sse3,sse4,popcnt,abm,mmx")
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

const int N = 1e5 + 11, mod = 1e9 + 7, mod2 = 998244353;
const int MAX = 3e5 + 11;
const int INF1 = 2e9 + 11;
const ll INF2 = 2e18 + 11;
const double INF3 = 1e8 + 11;
const int base = 500;
const int P = 31;
const int dx[] = {1, -1, 0, 0, 1, 1, -1, -1};
const int dy[] = {0, 0, 1, -1, 1, -1, 1, -1};
const double EPS = 1e-6;
const double PI = acos(-1.0);


template<typename T> using ordered_set = tree <T, null_type, less <T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T1, typename T2> inline void chmin(T1 &a, T2 b) { if (a > b) a = b; }
template<typename T1, typename T2> inline void chmax(T1 &a, T2 b) { if (a < b) a = b; }


typedef pair <int, int> pii;
typedef pair <ll, ll> pll;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int id1,id2;
double x;
struct point {
    int x,y,id;
} p[N],p2[N];
inline bool operator< (point a, point b) { return (a.x!=b.x ? a.x<b.x : a.y<b.y) ;}
struct seg {
    point p,q;
    int id;
} a[N];
inline double get_y(seg a) { return (a.p.x==a.q.x ? a.p.y : a.p.y + (a.q.y-a.p.y)*(x-a.p.x)/(a.q.x-a.p.x)) ;}
inline bool operator< (seg a, seg b) { return (a.id!=b.id and get_y(a)<get_y(b)) ;}
inline bool operator== (seg a, seg b) { return (a.id==b.id) ;}
int n,ans;
inline int orient(point a, point b, point c) {
    int val=(b.y-a.y)*(c.x-b.x)-(c.y-b.y)*(b.x-a.x);
    if (!val) return 0;
    if (val>0) return 1;
    return 2;
}
inline bool betw(point a, point b, point c) {
    return (min(a.x,c.x)<=b.x and b.x<=max(a.x,c.x) and
            min(a.y,c.y)<=b.y and b.y<=max(a.y,c.y));
}
inline bool inters(seg a, seg b) {
    int o1=orient(a.p,a.q,b.p);
    int o2=orient(a.p,a.q,b.q);
    int o3=orient(b.p,b.q,a.p);
    int o4=orient(b.p,b.q,a.q);
    if (o1!=o2 and o3!=o4) return 1;
    return (!o1 and betw(a.p,b.p,a.q) || !o2 and betw(a.p,b.q,a.q) ||
            !o3 and betw(b.p,a.p,b.q) || !o4 and betw(b.p,a.q,b.q));
}
inline bool cmp(pair <bool, point> a, pair <bool, point> b) {
    if (a.S.x!=b.S.x) return a.S.x<b.S.x;
    if (a.F!=b.F) return a.F<b.F;
    return a.S.y<b.S.y;
}
vector < set<seg>:: iterator > loc;
main() {
    file("cowjump");
    ios;
    cin>>n;
    vector < pair <bool, point> > events;
    fo(i,1,n,1) {
        cin>>a[i].p.x>>a[i].p.y>>a[i].q.x>>a[i].q.y;
        a[i].id=a[i].p.id=a[i].q.id=i;
        if (a[i].p.x>a[i].q.x) swap(a[i].p,a[i].q);
        events.pb({0, a[i].p});
        events.pb({1, a[i].q});
    }
    sort(all(events),&cmp);
    set <seg> active;
    loc.resize(n+10);
    for (int i=0;i<2*n;++i) {
        x=events[i].S.x;
        int ind=events[i].S.id;
        if (events[i].F) {
            auto bef=loc[ind], after=loc[ind];
            ++after;
            if (bef!=active.begin() and after!=active.end()) {
                --bef;
                if (inters(a[bef->id],a[after->id])) {
                    id1=bef->id;
                    id2=after->id;
                    break;
                }
            }
            active.erase(loc[ind]);
        } else {
            auto it=active.lb(a[ind]);
            if (it!=active.end() and inters(a[ind],a[it->id])) {
                id1=ind;
                id2=it->id;
                break;
            }
            if (it!=active.begin()) {
                --it;
                if (inters(a[ind],a[it->id])) {
                    id1=ind;
                    id2=it->id;
                    break;
                }
                ++it;
            }
            loc[ind]=active.ins(it,a[ind]);
        }
    }
    if (id1>id2) swap(id1,id2);
    if (!id1) return !(cout<<"NO");
    cout<<"YES\n"<<id1<<' '<<id2;
    return 0;
}
/**

*/
