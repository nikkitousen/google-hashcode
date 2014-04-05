#define _USE_MATH_DEFINES

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <set>
#include <cassert>

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

#define SQ(x) ((x)*(x))

using namespace std;

#define MAXN 11348
#define MAXM 17958
#define MAXT 54000
#define MAXC 8

int N,M,T,C,S;
double lat[MAXN],lon[MAXN];
int A[MAXM],B[MAXM],D[MAXM],cost[MAXM],len[MAXM];
vector<int> to[MAXN],id[MAXN];
bool mark[MAXM+1];
int edges[MAXM+1];

int pos[10], consumed[10];

void read(){
    cin >> N >> M >> T >> C >> S;
    
    for(int i = 0;i < N;++i){
        cin >> lat[i] >> lon[i];
    }
    
    for(int i = 0;i < M;++i){
        cin >> A[i] >> B[i] >> D[i] >> cost[i] >> len[i];
        
        to[ A[i] ].push_back(B[i]);
        id[ A[i] ].push_back(i);
        
        if(D[i] == 2){
            to[ B[i] ].push_back(A[i]);
            id[ B[i] ].push_back(i);
        }
    }

    memset(consumed, 0, sizeof(consumed));
    memset(mark, 0, sizeof(mark));
}

vector<int> sol[MAXC];

void print(){
    cout << C << endl;
    
    for(int i = 0;i < C;++i){
        cout << sol[i].size() << endl;
        
        for(int j = 0;j < sol[i].size();++j)
            cout << sol[i][j] << endl;
        //cout << endl;
    }
}

typedef long long ptype;

ptype seed = 79;

ptype my_rand(){
    seed = (seed * 279470273) % 4294967291LL;
    return seed;
}

void clear(){
    for(int i = 0;i < C;++i)
        sol[i].clear();
}


int ans;
vector<int> moves[10];
vector<int> auxmoves;

int total_dist[MAXN];
int times_used[MAXM];

int dijkstra(int carid, int source, int target, int modif=1) {
    set< pair<int , pair<int, int > > > pool;
    int edgeused[MAXN];
    bool done[MAXN];
    memset(done, 0, sizeof(done));


    pool.insert(MP(0, MP(source, -1)));
    while(!pool.empty()) {
        pair< int, pair<int, int> > upair = *(pool.begin());
        pool.erase(pool.begin());
        int u = upair.second.first;
        int edgeid = upair.second.second;
        int dist = upair.first/SQ(times_used[edgeid]+1);
        if(done[u]) continue;
        if(target == -1)
            total_dist[u] = dist;


        edgeused[u] = edgeid;
        
        done[u] = true;

        //cout << u << endl;

        if(u == target) break;

        REP(i, to[u].size()) {
            if(!done[to[u][i]] /*and times_used[id[u][i]] < 15 */ and consumed[carid]+dist+cost[id[u][i]] <= T) {
                pool.insert(MP((dist+cost[id[u][i]])*SQ(times_used[id[u][i]]+1), MP(to[u][i], id[u][i])));
            } else {
                //cout << i << " " << consumed[carid] << " " << dist << " " << cost[id[u][i]] << endl;
            }
        }
    }

    if(target < 0) {
        return -2;
    }

    if(!done[target]) return -1;

    assert( edgeused[source] == -1 );

    int curr = target;
    int total_cost=0;
    auxmoves.clear();
    while(edgeused[curr] >= 0) {
        if(modif) auxmoves.PB(curr);
        int eid = edgeused[curr];
        if(modif) consumed[carid] += cost[eid];

        total_cost += cost[eid];
        if(!mark[eid] and modif) {
            mark[eid] = true;
            ans += len[eid];
        }
        if(modif) times_used[eid]++;

        if(curr == B[eid]) curr = A[eid];
        else curr = B[eid];
    }

    assert( curr == source );

    if(modif and SZ(auxmoves) > 0) {
        for(int i=SZ(auxmoves)-1; i>=0; i--) moves[carid].PB(auxmoves[i]);
    }
    
    return total_cost;

}
double minlat, maxlat, minlon, maxlon;
double earth_distance(double lat1, double lon1, double lat2, double lon2) {
    double R = 6371; // km
    double dlat = (lat2 - lat1) * M_PI / 180.0;
    double dlon = (lon2 - lon1) * M_PI / 180.0;
    lat1 = lat1 * M_PI / 180.0;
    lat2 = lat2 * M_PI / 180.0;
    
    double a = sin(dlat/2) * sin(dlat/2) + sin(dlon/2) * sin(dlon/2) * cos(lat1) * cos(lat2);
    double c = 2.0 * atan2(sqrt(a), sqrt(1-a));
    double d = R * c;
    
    return d;
}

bool comp(int ii, int jj) {
    return total_dist[A[ii]] < total_dist[A[jj]];
    //return earth_distance(lat[A[ii]], lon[A[ii]], (minlat+maxlat)/2.0, (minlon+maxlon)/2.0) < earth_distance(lat[A[jj]], lon[A[jj]], (minlat+maxlat)/2.0, (minlon+maxlon)/2.0);
}




void method2() {

    minlat=100.0, maxlat=0.0, minlon=100.0, maxlon=0.0;

    REP(i, N) {
        minlat = min(minlat, lat[i]);
        minlon = min(minlon, lon[i]);
        maxlat = max(maxlat, lat[i]);
        maxlon = max(maxlon, lon[i]);
    }
    int centres[8] = { 532, 6862, 1506, 9731, 8651, 1532, 4663, 5607 };
    REP(i, C) pos[i] = S;

    int reledges[10][MAXM];
    REP(i, C) {
        //int go = my_rand() % N;
        int go = centres[i];
        dijkstra(i, pos[i], go);
        pos[i] = go;
        REP(j, M) reledges[i][j] = j;
        dijkstra(i, go, -1, 0);
        sort(reledges[i], reledges[i]+M, comp);
    }

    


    //REP(i, M) edges[i] = i;
    /*
    for(int i=M-1; i>0; i--) {
        int j = my_rand() % i;
        swap(edges[i], edges[j]);
    }
    */
    //dijkstra(0, S, -1, 0);

    //sort(edges, edges+M, comp);

    //REP(i, 100) cout << lat[A[edges[i]]] << " " << lon[B[edges[i]]] << " " << earth_distance(lat[A[edges[i]]], lon[A[edges[i]]], (minlat+maxlat)/2.0, (minlon+maxlon)/2.0) << endl;
    //set<int, comp> set_edges;


    memset(mark, 0, sizeof(mark));

    int esize=0;

    int kk1=0, kk2=M-1;
    int step = 0;
    REP(cc, C) {
        REP(kk, M) {
    //while(!set_edges.empty()) {
        
            int k = reledges[cc][kk];

            if(mark[k]) continue;
            int car=-1;
            int cardis=1000000000;
            int ret = 0;
            
            /*
            REP(i, C) {
                int auxret = dijkstra(i, pos[i], A[k], 0);
                if(auxret < 0) continue;
                //if(car < 0 or earth_distance(lat[A[k]], lon[A[k]], lat[pos[i]], lon[pos[i]]) < earth_distance(lat[A[k]], lon[A[k]], lat[car], lon[car])) {
                //    car = i;
                //}
                if(car<0 or auxret < cardis) {
                    car = i;
                    cardis = auxret;
                }

            }
            */

            car = cc;

            if(car < 0) continue;

            ret = dijkstra(car, pos[car], A[k]);
            if(ret < 0) continue;
            pos[car] = A[k];
            
            if(!mark[k] and consumed[car] + cost[k] <= T) {
                    consumed[car] += cost[k];
                    pos[car] = B[k];
                    moves[car].PB(B[k]);
                    ans += len[k];
                    times_used[k]++;
                    mark[k] = true;
                    
            }
            //for(int j=0; j<SZ(to[B[k]]); j++) if(!mark[id[B[k]][j]]) edges[esize++] = id[B[k]][j];
            //for(int j=0; j<SZ(to[A[k]]); j++) if(!mark[id[A[k]][j]]) edges[esize++] = id[A[k]][j];
        }
    }
    //cout << "done\n";
    cout << C << endl;
    
    REP(i, C) {
        cout << SZ(moves[i])+1 << endl;
        cout << S << endl;
        REP(j, SZ(moves[i])) cout << moves[i][j] << endl; 
    }
    
    cout << "ans: " << ans << endl;
}

int main(){
    ios::sync_with_stdio(0);
    
    read();
    ans = 0;
    method2();

    //method1();
    
    return 0;
}
