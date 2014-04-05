#include <cstdio>

using namespace std;

#define MAXR 800
#define MAXC 2000

char M[MAXR][MAXC],op[10];
int N,R = 716, C = 1522;

int main(){
    scanf("%d",&N);
    
    for(int i = 0;i < R;++i)
        for(int j = 0;j < C;++j)
            M[i][j] = '.';
    
    for(int i = 0;i < N;++i){
        scanf("%s",op);
        
        if(op[0] == 'P'){
            int x,y,k;
            scanf("%d %d %d",&x,&y,&k);
            
            for(int r = x - k;r <= x + k;++r)
                for(int c = y - k;c <= y + k;++c)
                    M[r][c] = '#';
        }else{
            int x,y;
            scanf("%d %d",&x,&y);
            
            M[x][y] = '.';
        }
    }
    
    printf("%d %d\n",R,C);
    
    for(int i = 0;i < R;++i)
        puts(M[i]);
    
    return 0;
}
