
#include <iostream>
#include "TPoint.h"
#ifndef TPAIR_H
#define TPAIR_H
using namespace std;

typedef struct {
	TPoint point1;
	TPoint point2;
	double distance;
}TPair;

void setPair(TPair*, TPoint, TPoint);
void setDistance(TPair*, double);
double euclidianDistance(TPoint, TPoint);
TPair closestPointDC(TPoint*, int);
TPair CPDC(TPoint*, int, double);
TPair bruteForce(TPoint*, int);

#endif