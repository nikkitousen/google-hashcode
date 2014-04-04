#include <cstdio>
#include <cstring>

using namespace std;

#define MAXR 800
#define MAXC 2000
#define MINP 55

int R,C,M[MAXR][MAXC];
char aux[MAXC];

void read(){
    scanf("%d %d",&R,&C);
    
    memset(M,0,sizeof M);
    
    for(int i = 0;i < R;++i){
        scanf("%s",aux[i]);
        
        for(int j = 0;j < C;++j)
            if(aux[j] != '.')
                M[i][j] = 1;
    }
}

int sum[MAXR + 1][MAXC + 1];

int precalc(){
    memset(sum,0,sizeof sum);
    
    for(int i = 0;i < R;++i){
        for(int j = 0;j < C;++j){
            sum[i + 1][j + 1] = sum[i + 1][j] + sum[i][j + 1] - sum[i][j];
        }
    }
}

int calc(int r1, int c1, int r2, int c2){
    return sum[r1 + 1][c1 + 1] - sum[r1 + 1][c2] - sum[r2][c1 + 1] + sum[r2][c2];
}

int main(){
    read();
    
    return 0;
}
