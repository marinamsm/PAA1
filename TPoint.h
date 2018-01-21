
#include <iostream>
#include <cmath>
#include <float.h>
#ifndef TPOINT_H
#define TPOINT_H
using namespace std;

typedef struct {
	int x;
	int y;
}TPoint;

TPoint createTPoint(int, int);
void setCoordinates(TPoint*, int, int);
int getXCoordinate(TPoint*);
int getYCoordinate(TPoint*);
TPoint* createPoints(int);
void printPoints(TPoint*, int);
void merge(TPoint*, int, int);
void mergeIntercala(TPoint*, int, int, int, int);
void copy(TPoint*, TPoint*, int, int);

#endif