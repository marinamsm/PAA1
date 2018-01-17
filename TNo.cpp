
#include "TNo.h"

TNo createTNo(int x, int y){
	TNo N;
	setCoordinates(&N, x, y);
	return N;
}

TNo* createPoints(int size) {
	TNo* Nos = new TNo[size];
	for(int i = 0; i < size; i++){
		int x, y;
		cin >> x >> y;
		Nos[i] = createTNo(x, y);
	}
	return Nos;
}

void setCoordinates(TNo* N, int x, int y){
	N->x = x;
	N->y = y;
}

int getXCoordinate(TNo* N){
	return N->x;
}

int getYCoordinate(TNo* N){
	return N->y;
}

void printPoints(TNo* Nos, int size) {
	for(int i = 0; i < size; i++){
		cout << Nos[i].x << " " << Nos[i].y << endl;
	}
}

void merge(TNo* Nos, int size, int flag){
	int esq , dir ;
	int b = 1;
	while(b < size){
		esq = 0;
		while(esq+b < size){
			dir = esq+2*b;
			if(dir > size) dir = size ;
			mergeIntercala(Nos, esq, esq+b-1, dir-1, flag);
			esq = esq+2*b;
		}
		b *= 2;
	}
}

void mergeIntercala(TNo* Nos, int esq, int meio, int dir, int flag){
	int i, j, k;
	int tamA = meio-esq+1;
	int tamB = dir-meio;
	TNo* A = new TNo[tamA];
	TNo* B = new TNo[tamB];
	for(i = 0; i < tamA; i++) A[i] = Nos[i+esq];
	for(i = 0; i < tamB; i++) B[i] = Nos[i+meio+1];
	for(i = 0, j = 0, k = esq; k <= dir; k++){
		if(i == tamA) Nos[k] = B[j++];
		else if (j == tamB ) Nos[k] = A[i++];
		else if (flag == 0 && A[i].x < B[j].x) Nos[k] = A[i++];
		else if (flag != 0 && A[i].y < B[j].y) Nos[k] = A[i++];
		else Nos[k] = B[j++];
	}
	delete[] A;
	delete[] B;
}

void copy(TNo* Destination, TNo* Origin, int init, int end){
	int size = end - init;
	for(int i = 0; i < size; i++){
		Destination[i] = Origin[init];
		init++;
	}
}