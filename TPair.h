
#include <iostream>
#include "TNo.h"
#ifndef TPAIR_H
#define TPAIR_H
using namespace std;

typedef struct {
	TNo point1;
	TNo point2;
	double distance;
}TPair;

void setPair(TPair*, TNo, TNo);
void setDistance(TPair*, double);
double euclidianDistance(TNo, TNo);
TPair closestPointDC(TNo*, int);
TPair CPDC(TNo*, int, double);
TPair bruteForce(TNo*, int);

#endif