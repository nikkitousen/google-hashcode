#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

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
    for(int x = 40;x <= 49;++x){
        for(int MAXFAIL = 30;MAXFAIL >= 25;--MAXFAIL){
            clear();
            seed = x;
            
            for(int i = 0;i < C;++i){
                int pos = S;
                int curt = 0;
                
                sol[i].push_back(pos);
                int nsol = 1;
                
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
    //srand (time(NULL));
    method1();
    
    return 0;
}
