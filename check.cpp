#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#define FOR(i, A, B) for(int i=(A); i<(B); i++)
#define REP(i, N) for(int i=0; i<(N); i++)
#define SZ(v) ((int)(v).size())
#define ALL(v) (v).begin(), (v).end()
#define SORT(v) sort(ALL(v))
#define MP make_pair
#define PB push_back
#define VI vector<int>
#define VS vector<string>
#define PII pair<int, int>
#define X first
#define Y second

using namespace std;

int N, M, T, C, S;

struct edge
{
	int x, d, t, idx;
	edge() {}
    edge(int x, int d, int t, int idx) : x(x), d(d), t(t), idx(idx) {}
};

vector<edge> adj[20000];
bool mark[20000];


int main()
{
	ifstream input ("paris_54000.txt");
	//ifstream input ("input");
	double lat, lon;
	int a, b, d, t, dir;
	input >> N >> M >> T >> C >> S;
	REP(i, N) input >> lat >> lon;
	REP(i, M) {
		input >> a >> b >> dir >> t >> d;
		adj[a].PB(edge(b, d, t, i));
		if(dir > 1) adj[b].PB(edge(a, d, t, i));
		mark[i] = false;
	}

	int cc;
	cin >> cc;
	if(cc > C) {
		cout << "More cars than permitted\n";
		return 0;
	}

	int ans = 0;
	REP(k, cc) {
		int tt = 0;
		int curr = S;
		int moves;
		int next;
		cin >> moves;
		REP(kk, moves) {
			cin >> next;
			if(kk == 0) {
				if(next != S) {
					cout << "ERROR: car " << cc << " starting in a wrong node\n";
					return 0;
				} else continue;
			}
			bool ok = false;
			REP(i, adj[curr].size()) {
				if(adj[curr][i].x == next) {
					tt += adj[curr][i].t;
					if(!mark[adj[curr][i].idx]) {
						mark[adj[curr][i].idx] = true;
						ans += adj[curr][i].d;
					}
					ok = true;
					break;
				}
			}
			if(!ok) {
				cout << "ERROR: Trying to go from " << curr << " to " << next << " which are not adjacent\n";
				return 0;
			}
			if(tt > T) {
				cout << "ERROR: car " << k << " takes more time that available\n";
				cout << "time=" << tt << " when going form " << curr << " to " << next << endl;
				return 0;
			}
			curr = next;
		}
	}
	cout << "Success! Answer: " << ans << endl;
}
