#include <cstdio>
#include <cstring>
#include <algorithm>

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

int precalc(){
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

int main(){
    read();
    precalc();
    method1();
    
    return 0;
}
