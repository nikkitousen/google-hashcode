#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define MAXR 800
#define MAXC 2000
#define MINP 90

int R,C,M[MAXR][MAXC], mm[MAXR][MAXC];

int main()
{
	ifstream original ("doodle.txt");
	string aux;
	memset(M, 0, sizeof(M));

	original >> R >> C;
	for(int i=0; i<R; i++) {
		original >> aux;
		for(int j=0; j<C; j++) if(aux[j] != '.') M[i][j] = 1;
	}
	
	int T;
	cin >> T;
	memset(mm, 0, sizeof(mm));
	while(T--) {
		cin >> aux;
		int r, c, h;
		if(aux == "PAINTSQ") {
			cin >> r >> c >> h;
			for(int i=max(0, r-h); i<=min(R-1, r+h); i++) {
				for(int j=max(0, c-h); j<=min(C-1, c+h); j++) {
					mm[i][j] = 1;
				}
			}
		} else if (aux == "ERASECELL") {
			cin >> r >> c;
			mm[r][c] = 0;
		} else {
			cout << "Wrong command: " << aux << endl;
			return 0;
		}
	}

	cout << "Checking....\n";
	for(int i=0; i<R; i++) {
		for(int j=0; j<C; j++) {
			if(M[i][j] != mm[i][j]) {
				cout << "Check failed at cell " << i << ", " << j << endl;
				return 0;
			}
		}
	}
	cout << "Check SUCCESFULL!\n";

}
