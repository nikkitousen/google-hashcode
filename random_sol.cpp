#include <iostream>
#include <algorithm>
#include <vector>

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

using namespace std;

#define MAXN 11348
#define MAXM 17958
#define MAXT 54000
#define MAXC 8

int N,M,T,C,S;
double lat[MAXN],lon[MAXN];
int A[MAXM],B[MAXM],D[MAXM],cost[MAXM],len[MAXM];
vector<int> to[MAXN],id[MAXN];

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

ptype seed = 47;

ptype my_rand(){
    seed = (seed * 279470273) % 4294967291LL;
    return seed;
}

void clear(){
    for(int i = 0;i < C;++i)
        sol[i].clear();
}

void method1(){
    clear();
    
    for(int i = 0;i < C;++i){
        int pos = S;
        int curt = 0;
        
        sol[i].push_back(pos);
        
        int fail = 0;
        
        while(curt < T){
            int go = my_rand() % to[pos].size();
            
            if(to[pos][go] != pos && cost[ id[pos][go] ] + curt <= T){
                fail = 0;
                
                curt += cost[ id[pos][go] ];
                pos = to[pos][go];
                sol[i].push_back(pos);
                //cout << sol[i].size() << " " << curt << endl;
            }else{
                fail++;
                if(fail == 10) break;
            }
        }
    }
    
    print();
}

void method2() {
    int pos[10], consumed[10];
    bool mark[MAXM];

    REP(i, C) pos[i] = S, consumed[i] = 0;
    REP(i, M) mark[i] = false;

    int ans=0;
    int curr=0;
    while(1) {
        int best=-1, besta=0, bestb=0, bestid=0;
        int times=C;
        while(times--) {
            int i = curr;
            int pi = pos[i];
            REP(j, SZ(to[pi])) {
                int k = id[pi][j];
                if(consumed[i]+cost[k] > T) continue;
                int gain = 0;
                if(!mark[k]) gain = len[k];
                if(gain > best) {
                    best = gain;
                    besta=i;
                    bestb=to[pi][j];
                    bestid=k;
                }
            }
            if(best > 0) break;
            curr = (curr+1)%C;
        }
        if(best < 0) break;
        if(best == 0) {
            int attempts=0;
            while(attempts < 10) {
                int go = my_rand() % to[pos[curr]].size();
                bestid = id[pos[curr]][go];
                if(consumed[curr]+cost[bestid] > T) {
                    attempts++;
                    continue;
                }
                bestb = go;
                break;
            }
        }
        ans += best;
        mark[bestid] = true;
        consumed[besta] += cost[bestid];
        pos[besta] = bestb;

        curr = (curr+1)%C;

        REP(i, C) cout << consumed[i] << " ";
        cout << endl;
    }
    cout << ans << endl;
}

int main(){
    ios::sync_with_stdio(0);
    
    read();
    method2();
    
    return 0;
}
