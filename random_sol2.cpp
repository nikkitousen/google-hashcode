#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>

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

vector<int> sol[MAXC],prefix[MAXC];

void print(){
    cout << C << endl;
    
    for(int i = 0;i < C;++i){
        cout << sol[i].size() << endl;
        
        for(int j = 0;j < sol[i].size();++j)
            cout << sol[i][j] << endl;
    }
}

struct node{
    int pos,dist,par;
    
    node(){}
    
    node(int _pos, int _dist, int _par) :
        pos(_pos), dist(_dist), par(_par){}
    
    bool operator < (node X)const{
        return dist > X.dist;
    }
};

int dist[MAXN],prev[MAXN];

void dijkstra(int start){
    memset(dist,-1,sizeof dist);
    
    priority_queue<node> Q;
    Q.push(node(start,0,-2));
    
    while(!Q.empty()){
        node cur = Q.top();
        Q.pop();
        
        if(dist[cur.pos] != -1) continue;
        dist[cur.pos] = cur.dist;
        prev[cur.pos] = cur.par;
        
        for(int i = to[cur.pos].size() - 1;i >= 0;--i){
            int nxt = to[cur.pos][i];
            
            if(dist[nxt] == -1)
                Q.push(node(nxt,cur.dist + cost[ id[cur.pos][i] ],cur.pos));
        }
    }
}

#include <ctime>

typedef long long ptype;

ptype seed = 47;

ptype my_rand(){
    seed = (seed * 279470273) % 4294967291LL;
    return seed;
    //return rand();
}

void clear(){
    for(int i = 0;i < C;++i)
        sol[i].clear();
}

int method1(){
    for(int x = 1;x <= 70;++x){
        seed = x;
        int r[C];
        
        for(int i = 0;i < C;++i){
            do{
                r[i] = rand() % N;
            }while(dist[ r[i] ] > T);
            
            //cout << r[i] << " " << dist[ r[i] ] << endl;
            
            prefix[i].clear();
            
            int pos = r[i];
            prefix[i].push_back(pos);
            
            while(pos != S){
                pos = prev[pos];
                //cout << pos << " " <<dist[pos] << endl;
                prefix[i].push_back(pos);
            }
            
            reverse(prefix[i].begin(),prefix[i].end());
        }
        for(int MAXFAIL = 26;MAXFAIL >= 26;--MAXFAIL){
            clear();
            seed = x;
            
            for(int i = 0;i < C;++i){
                sol[i] = prefix[i];
                int pos = r[i];
                int curt = dist[ r[i] ];
                int nsol = sol[i].size();
                int fail = 0;
                
                while(curt < T){
                    int go = my_rand() % to[pos].size();
                    
                    bool ok = (cost[ id[pos][go] ] + curt <= T);
                    
                    if(sol[i][nsol - 1] == to[pos][go])
                        ok = false;
                    
                    //if(to[pos][go] != pos && !visited[ id[pos][go] ] && cost[ id[pos][go] ] + curt <= T){
                    if(ok){
                        fail = 0;
                        
                        curt += cost[ id[pos][go] ];
                        pos = to[pos][go];
                        sol[i].push_back(pos); ++nsol;
                        //cout << sol[i].size() << " " << curt << endl;
                    }else{
                        fail++;
                        //25 28 30
                        if(fail == MAXFAIL) break;
                    }
                }
            }
            
            print();
        }
    }
}

int main(){
    ios::sync_with_stdio(0);
    
    read();
    
    dijkstra(S);
    srand (time(NULL));
    method1();
    
    return 0;
}
