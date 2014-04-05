#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
#include <map>
#include <cstdlib>
#include <ctime>

using namespace std;

#define MAXR 800
#define MAXC 2000
#define MINP 90

int R,C,M[MAXR][MAXC];
char aux[MAXC];

void read(){
    scanf("%d %d",&R,&C);
    
    memset(M,0,sizeof M);
    
    for(int i = 0;i < R;++i){
        scanf("%s",aux);
        
        for(int j = 0;j < C;++j)
            if(aux[j] != '.')
                M[i][j] = 1;
    }
}

int sum[MAXR + 1][MAXC + 1];

void precalc(){
    memset(sum,0,sizeof sum);
    
    for(int i = 0;i < R;++i){
        for(int j = 0;j < C;++j){
            sum[i + 1][j + 1] = sum[i + 1][j] + sum[i][j + 1] - sum[i][j] + M[i][j];
        }
    }
}

int calc(int r1, int c1, int r2, int c2){
    return sum[r1 + 1][c1 + 1] - sum[r1 + 1][c2] - sum[r2][c1 + 1] + sum[r2][c2];
}

void method1(){
    int ans = 0,minans;
    
    for(int P = 100;P >= 80;--P){
        ans = 0;
        
        for(int i = 0;i < R;++i){
            for(int j = 0;j < C;++j){
                int maxs = min(min(i,j),min(R - 1 - i,C - 1 - j));
                
                for(int k = maxs;k >= 0;--k){
                    if(calc(i - k,j - k,i + k,j + k) * 100 >= P * (2 * k + 1) * (2 * k + 1)){
                        ++ans;
                        
                        for(int r = i - k;r <= i + k;++r){
                            for(int c = j - k;c <= j + k;++c){
                                if(M[r][c] == 1) M[r][c] = 0;
                                else ++ans;
                            }
                        }
                        
                        break;
                    }
                }
            }
        }
        
        printf("P = %d : %d\n",P,ans);
        
        if(P == 100) minans = ans;
        else minans = min(minans,ans);
    }
    
    printf("%d\n",minans);
}

#define vint vector<int>
int opt[800][1600];
int mm[800][1600];

struct nodo {
    int r,c,h;
    nodo() {}
    nodo(int r, int c, int h) : r(r), c(c), h(h) {}
};
bool operator<(nodo A, nodo B) {
    //return A.h > B.h;

    if(A.h > B.h) return true;
    if(A.h < B.h) return false;
    int oA = calc(A.r+A.h/2, A.c+A.h/2, A.r-A.h/2, A.c-A.h/2);
    int oB = calc(B.r+B.h/2, B.c+B.h/2, B.r-B.h/2, B.c-B.h/2);

    return (A.h*A.h-oA)*oB < (B.h*B.h-oB)*oA;

}

void method2() {

    vector<nodo> nodos;
    for(int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            int l = 0;
            int s = -1;
            vint va;
            for(;i-l >= 0 && j-l >= 0 && i+l < R && j+l < C; l++) {
                int tmp = 0;
                /*
                for(int k = j-l; k <= j+l; k++) if (!M[i-l][k]) tmp++;
                if(l) {
                    for(int k = j-l; k <= j+l; k++) if (!M[i+l][k]) tmp++;            
                    for(int k = i-l+1; k < i+l; k++) if (!M[k][i-l]) tmp++;
                    for(int k = i-l+1; k < i+l; k++) if (!M[k][i+l]) tmp++;
                }
                s += tmp*2 - 8*l;
                va.push_back(s);
                */
                int oA = calc(i+l, j+l, i-l, j-l);
                if(1+((2*l+1)*(2*l+1)-oA) > oA) break;
                if(l>10) break;
            }
            
            //int jj = min_element(va.begin(), va.end()) - va.begin();
            //opt[i][j] = jj*2 + 1;
            opt[i][j] = 2*max(--l, 0)+1;
            if (l == 0 && M[i][j] == 0) ;
            else nodos.push_back( nodo (i, j, opt[i][j]) );
        }
        cout << i << endl;
    }

    //for(int i = 0; i < R; i++) for(int j = 0; j < C; j++) printf("%d%c", opt[i][j], j+1 == C? 10 : 32);
    sort( nodos.begin(), nodos.end() );
    
    cout <<"--------\n";
    memset(mm, 0, sizeof(mm));
    int ans = 0;
    for(int t = 0; t < nodos.size(); t++) {
        bool cont = 1;
        int l = nodos[t].h/2;
        int r = nodos[t].r;
        int c = nodos[t].c;
        if(t == 0) cout << r << " - " << c << endl;
        for(int i = r-l; i <= r+l; i++) for(int j = c-l; j <= c+l; j++) {
            if (mm[i][j] == 0) {
                cont = 0;
                i = j = 1<<30;
            }
        }
        if (cont) continue;
        if (l == 0 && M[r][c] == 0) continue;
        ans++;

        cout << l << endl;
        //cout << r << " " << c << endl;
        for(int i = r-l; i <= r+l; i++) for(int j = c-l; j <= c+l; j++)
            mm[i][j] = 1;

    }
    //printf("%d\n", ans);
    int erase=0;
    for(int i=0; i<R; i++) for(int j=0; j<C; j++) {
        if(M[i][j]==0 and mm[i][j]==1) erase++;
    }
    cout << "----\n";
    cout << ans << endl;
    cout << erase << endl;
    cout << ans+erase << endl;
}


void method3() {
    vector< pair<int, int> > indexes;

    for(int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            indexes.push_back(make_pair(i, j));
        }
    }

    srand(time(NULL));
    for(int i=R*C-1; i>0; i--) {
        int j = rand() % i;
        swap(indexes[i], indexes[j]);
    }


    memset(mm, 0, sizeof(mm));
    vector<nodo> nodos;
    int ans=0;
    for(int l=301; l>0; l-=2) {
        for(int k=0; k<R*C; k++) {

            int i=indexes[k].first;
            int j=indexes[k].second;
            if(i+l > R or j+l > C) continue;

                int ones = calc(i+l-1, j+l-1, i, j);
                //if(ones*100 < 100*l*l) continue;
                int news=0;
                int toerase=0;
                for(int ii=i; ii<i+l; ii++) {
                    for(int jj=j; jj<j+l; jj++) {
                        if(M[ii][jj] and !mm[ii][jj]) news++;
                        if(!M[ii][jj] and !mm[ii][jj]) toerase++;
                    }
                }
                //if(news == 0 or news < ones*10/45) continue;
                if(!(news > 0 and toerase+1 < news)) continue;
                ans++;
                nodos.push_back(nodo(i+l/2, j+l/2, l/2));
                for(int ii=i; ii<i+l; ii++) {
                    for(int jj=j; jj<j+l; jj++) {
                        mm[ii][jj] = 1;
                    }
                }

        }
    }
    for(int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if(mm[i][j] and !M[i][j]) nodos.push_back(nodo(i, j, -1));
        }
    }

    cout << nodos.size() << endl;
    /*
    for(int i=0; i<nodos.size(); i++) {
        if(nodos[i].h >= 0) cout << "PAINTSQ " << nodos[i].r << " " << nodos[i].c << " " << nodos[i].h << endl;
        else cout << "ERASECELL " << nodos[i].r << " " << nodos[i].c << endl;
    }
    */
}



void method4() {

    memset(mm, 0, sizeof(mm));
    vector<nodo> nodos;
    int ans=0;
    for(int l=57; l>0; l-=2) {
        for(int il=0; il<l; il++) {
            for(int ri=il; ri<R; ri+=l) {
                for(int jl=0; jl<l; jl++) {
                    for(int rj=jl; rj<C; rj+=l) {
            
            int i = R-ri-1;
            int j = C-rj-1;
            if(i+l > R or j+l > C) continue;

            int ones = calc(i+l-1, j+l-1, i, j);
            if(ones*100 < 100*l*l) continue;
            int news=0;
            int toerase=0;
            for(int ii=i; ii<i+l; ii++) {
                for(int jj=j; jj<j+l; jj++) {
                    if(M[ii][jj] and !mm[ii][jj]) news++;
                    if(!M[ii][jj] and !mm[ii][jj]) toerase++;
                }
            }
            if(news == 0 or news < ones*10/45) continue;
            //if(news == 0 or toerase+1 > max(1, news/30)) continue;
            ans++;
            nodos.push_back(nodo(i+l/2, j+l/2, l/2));
            for(int ii=i; ii<i+l; ii++) {
                for(int jj=j; jj<j+l; jj++) {
                    mm[ii][jj] = 1;
                }
            }
                    }
                }
            }
        }
    }
    for(int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if(mm[i][j] and !M[i][j]) nodos.push_back(nodo(i, j, -1));
        }
    }

    cout << nodos.size() << endl;
    /*
    for(int i=0; i<nodos.size(); i++) {
        if(nodos[i].h >= 0) cout << "PAINTSQ " << nodos[i].r << " " << nodos[i].c << " " << nodos[i].h << endl;
        else cout << "ERASECELL " << nodos[i].r << " " << nodos[i].c << endl;
    }
    */
    
    
    
}







int main(){
    read();
    precalc();
    method4();
    
    return 0;
}
