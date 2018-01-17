
#include <iostream>
#include <cmath>
#include <float.h>
#ifndef TNO_H
#define TNO_H
using namespace std;

typedef struct {
	int x;
	int y;
}TNo;

TNo createTNo(int, int);
void setCoordinates(TNo*, int, int);
int getXCoordinate(TNo*);
int getYCoordinate(TNo*);
TNo* createPoints(int);
void printPoints(TNo*, int);
void merge(TNo*, int, int);
void mergeIntercala(TNo*, int, int, int, int);
void copy(TNo*, TNo*, int, int);

#endif