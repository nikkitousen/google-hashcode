#include <bits/stdc++.h>
#define f(i,x,y) for (int i = x; i < y; i++)
#define fd(i,x,y) for(int i = x; i>= y; i--)
#define FOR(it,A) for(typeof A.begin() it = A.begin(); it!=A.end(); it++)
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define vint vector<int>
#define ll long long
#define clr(A,x) memset(A, x, sizeof A)
#define pb push_back
#define pii pair<int,int>
#define fst first
#define snd second
#define ones(x) __builtin_popcount(x)
#define cua(x) (x)*(x)
#define eps (1e-9)
#define oo (1<<30)
#define debug(x) cout <<#x << " = " << x << endl
#define adebug(x,n) cout <<#x<<endl; f(i,0,n)cout<<x[i]<<char(i+1==n?10:32)
#define mdebug(x,m,n) cout <<#x<<endl; f(i,0,m)f(j,0,n)cout<<x[i][j]<<char(j+1==n?10:32)
#define N 12000
#define M 18000
#define VIZ(e, x) (e.u == x? e.v : e.u)
using namespace std;
template<class T> inline void mini(T &a,T b){if(b<a) a=b;}
template<class T> inline void maxi(T &a,T b){if(b>a) a=b;}

struct punto {
	double x,y;
	int id;
	punto(double x, double y): x(x), y(y) {}
	punto() {}
	punto operator+ (punto p) { return punto(x + p.x, y + p.y); }
	punto operator- (punto p) { return punto(x - p.x, y - p.y); }
	punto operator* (double t) { return punto(x*t, y*t); }
	punto operator/ (double t) { return punto(x/t, y/t); }
	double operator*(punto p) { return x*p.x + y*p.y; }
	double operator%(punto p) { return x*p.y - y*p.x; }
	punto operator~() { return punto(-y,x); }
	void read() { scanf("%lf%lf", &x, &y); }
	void print() { printf("%.6f %.6f\n", x, y); }
};

int cmp(double a, double b=0) { return a < b-eps? -1 : a > b+eps? 1 : 0; }
bool operator<(punto A, punto B) {
	int ca = cmp(A.x, B.x);
	if (ca) return ca < 0;
	int cb = cmp(A.y, B.y);
	return cb < 0;
}
double norma(punto a, punto b = punto(0,0)) { return hypot(a.x-b.x, a.y-b.y); }
double angulo(punto a, punto b) { 
	a = a/norma(a);
	b = b/norma(b);
	double calfa = a*b;
	mini(calfa, 1.0);
	maxi(calfa, -1.0);
	return acos(calfa);
}

vector<punto> hull (vector<punto> v){
	punto H[v.size()+1];
	int sz = 0;
	sort (all(v));

	f(i,0,v.size()) {
		while (sz>=2 && (H[sz-1] - v[i]) % (H[sz-2] - v[i]) > -eps) sz--;
		H[sz++] = v[i];
	}
	int t = sz+1;
	fd(i,v.size()-1,0){
		while (sz>=t && (H[sz-1] - v[i]) % (H[sz-2] - v[i]) > -eps) sz--;
		H[sz++] = v[i];
	}
	sz--;
	return vector<punto>(H, H + sz);
}

struct edge {
	int u,v,d,t,score;
	edge(int u, int v, int d, int t, int score) {}
	edge() {}
	void read() {
		scanf("%d%d%d%d%d", &u, &v, &d, &t, &score);
	}
} z[M];
bool operator< (edge A, edge B) {
	return A.score > B.score;
}
bool orden(int i, int j) {
	return z[i] < z[j];
}

int n,m,T,C,S;
vint E[12000];
int mark[18000];


int deg[N];
int who[N];
struct nodo {
	int v,w;
	nodo(int v, int w) : v(v), w(w) {}
};
bool operator<(nodo A, nodo B) { return A.w < B.w; }

int dijkstra(int s, int t) {
	multiset<nodo> A;
	A.insert( nodo(s, 0) );
	map<int,int> d; d[s] = 0;
	while(A.empty() == 0) {
		multiset<nodo>::iterator it = A.begin();
		nodo q = *it; A.erase(it);
		if (q.v == t) return d[q.v];
		f(i,0,E[q.v].size()) {
			edge &e = z[ E[q.v][i] ];
			int v = VIZ(e, q.v);
			int tmp = e.t + d[q.v];
			if (d.count(v)==0 || tmp < d[v]) {
				d[v] = tmp;
				who[v] = q.v;
				A.insert( nodo(v, tmp) );
			}
		}
	}
	return d[t];
}
vint rec(int c, int s, int t) {
	vint w;
	while(t!=s) {
		w.pb(t);
		t = who[t];
	}
	reverse(all(w));
	return w;
}

int pos[8], time_ac[8];
int tot[8];
int p[8][N];
void print(int c, int len) {
	printf("%d\n", len);
	int x = S;
	f(j,0,len) {
		printf("%d\n", p[c][j]);
	}
}

int main(){
	srand(time(0));
	cin >> n >> m >> T >> C >> S;
	vector<punto> pp(n);
	f(i,0,n) {
		pp[i].read();
		pp[i].id = i;
	}
	vector<punto> H = hull(pp);

	int indices[8] = {0,2,8,14,20,24,26,30};


	f(i,0,m) {
		edge &e = z[i];
		e.read();
		if (e.d == 1) {
			E[e.u].pb( i );
		} else {
			E[e.u].pb( i );
			E[e.v].pb( i );
		}
		deg[e.u]++;
		deg[e.v]++;
	}

	vint camino[8];
	f(c,0,8) {
		int tt = dijkstra(S, H[ indices[c] ].id);
		vint w = rec(c, S, H[ indices[c] ].id);
		camino[c] = w;
		p[c][tot[c]++] = S;
		debug(w.size());
//		f(i,0,w.size()) p[c][tot[c]++] = w[i];
	}
	

	cout << C << endl;
	f(c,0,C) {
		print(c, tot[c]);
	}
}


