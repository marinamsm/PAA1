
#include "TPoint.h"

TPoint createTPoint(int x, int y){
	TPoint N;
	setCoordinates(&N, x, y);
	return N;
}

TPoint* createPoints(int size) {
	TPoint* Points = new TPoint[size];
	for(int i = 0; i < size; i++){
		int x, y;
		cin >> x >> y;
		Points[i] = createTPoint(x, y);
	}
	return Points;
}

void setCoordinates(TPoint* N, int x, int y){
	N->x = x;
	N->y = y;
}

int getXCoordinate(TPoint* N){
	return N->x;
}

int getYCoordinate(TPoint* N){
	return N->y;
}

void printPoints(TPoint* Points, int size) {
	for(int i = 0; i < size; i++){
		cout << Points[i].x << " " << Points[i].y << endl;
	}
}

void merge(TPoint* Points, int size, int flag){
	int esq , dir ;
	int b = 1;
	while(b < size){
		esq = 0;
		while(esq+b < size){
			dir = esq+2*b;
			if(dir > size) dir = size ;
			mergeIntercala(Points, esq, esq+b-1, dir-1, flag);
			esq = esq+2*b;
		}
		b *= 2;
	}
}

void mergeIntercala(TPoint* Points, int esq, int meio, int dir, int flag){
	int i, j, k;
	int tamA = meio-esq+1;
	int tamB = dir-meio;
	TPoint* A = new TPoint[tamA];
	TPoint* B = new TPoint[tamB];
	for(i = 0; i < tamA; i++) A[i] = Points[i+esq];
	for(i = 0; i < tamB; i++) B[i] = Points[i+meio+1];
	for(i = 0, j = 0, k = esq; k <= dir; k++){
		if(i == tamA) Points[k] = B[j++];
		else if (j == tamB ) Points[k] = A[i++];
		else if (flag == 0 && A[i].x < B[j].x) Points[k] = A[i++];
		else if (flag != 0 && A[i].y < B[j].y) Points[k] = A[i++];
		else Points[k] = B[j++];
	}
	delete[] A;
	delete[] B;
}

void copy(TPoint* Destination, TPoint* Origin, int init, int end){
	int size = end - init;
	for(int i = 0; i < size; i++){
		Destination[i] = Origin[init];
		init++;
	}
}