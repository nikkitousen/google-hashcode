#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

#define MAXR 800
#define MAXC 2000

int R,C,M[MAXR][MAXC],M2[MAXR][MAXC];
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

void update(int r, int c, int val){
    for(int x = r;x <= MAXR;x += x & -x)
        for(int y = c;y <= MAXC;y += y & -y)
            sum[x][y] += val;
}

int query(int r, int c){
    int ret = 0;
    
    for(int x = r;x > 0;x -= x & -x)
        for(int y = c;y > 0;y -= y & -y)
            ret += sum[x][y];
    
    return ret;
}

int query(int r1, int c1, int r2, int c2){
    return query(r2 + 1,c2 + 1) - query(r1,c2 + 1) - query(r2 + 1,c1) + query(r1,c1);
}

int precalc(){
    memset(sum,0,sizeof sum);
    
    for(int i = 0;i < R;++i){
        for(int j = 0;j < C;++j){
            if(M[i][j] == 1) update(i + 1,j + 1,1);
        }
    }
}

/*void copy(){
    for(int i = 0;i < R;++i)
        for(int j = 0;j < C;++j)
            M2[i][j] = M[i][j];
}*/

void method1(){
    int ans = 0,minans;
    
    for(int P = 91;P >= 70;--P){
        memset(M2,0,sizeof M2);
        precalc();
        ans = 0;
        
        /*for(int i = 0;i < R;++i){
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
        }*/
        
        int maxs = min((R - 1) / 2,(C - 1) / 2);
        
        for(int k = maxs;k >= 0;--k){
            for(int i = k;i + k < R;++i){
                for(int j = k;j + k < C;++j){
                    if(query(i - k,j - k,i + k,j + k) * 100 >= P * (2 * k + 1) * (2 * k + 1)){
                    
                        ++ans;
                        //printf("PAINTSQ %d %d %d\n",i,j,k);
                        
                        for(int r = i - k;r <= i + k;++r){
                            for(int c = j - k;c <= j + k;++c){
                                if(M[r][c] == 1 && M2[r][c] == 0){
                                    M2[r][c] = 1;
                                    update(r + 1,c + 1,-1);
                                }else if(M[r][c] == 0){
                                    ++ans;
                                    //printf("ERASECELL %d %d\n",r,c);
                                }
                            }
                        }
                    }
                }
            }
        }
        
        printf("P = %d : %d (%d)\n",P,ans,sum[R][C]);
    }
}

int main(){
    read();
    method1();
    
    return 0;
}
