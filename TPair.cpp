
#include "TPair.h"

void setPair(TPair* Pair, TNo pt1, TNo pt2){
	Pair->point1 = pt1;
	Pair->point2 = pt2;
}

void setDistance(TPair* Pair, double distance){
	Pair->distance = distance;
}

//Parte de dividir e conquistar
TPair closestPointDC(TNo* Points, int size){
	TPair pair;
	if (size <= 3){
		pair = bruteForce(Points, size); //tempo constante
		return pair;
	}
	int half = size/2;
	TNo* LeftPoints = new TNo[half];
	copy(LeftPoints, Points, 0, half);
	TNo* RightPoints = new TNo[size-half];
	copy(RightPoints, Points, half, size);
	TPair leftDist = closestPointDC(LeftPoints, half); //encontra o par de menor distância no quadrante esquerdo atual do plano
	TPair rightDist = closestPointDC(RightPoints, size-half); //encontra o par de menor distância no quadrante direito atual do plano
	if(leftDist.distance < rightDist.distance)
		pair = leftDist;
	else pair = rightDist;
	TPair pair2 = CPDC(Points, size, pair.distance); //encontrar o par de menor distância com um ponto à esquerda e um à direita
	if(pair2.distance < pair.distance)
		pair = pair2;
	return pair; //retorna o par de distância mínima
}

double euclidianDistance(TNo p1, TNo p2){
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

/*Parte de combinar
Esta parte deve verificar em uma faixa de pontos que pegue tanto pontos do quadrante esquerdo quanto direito o par de menor distância
para depois comparar com o que foi encontrado em closestPointDC e obter o menor de todos do plano*/
TPair CPDC(TNo* Points, int size, double distance){
	int midx = Points[size/2].x; //coordenada X do meio do vetor de pontos (já ordenados por X)
	int j = 0;
	TPair pair;
	TNo* leftAndRightPts = new TNo[size];
	pair.distance = DBL_MAX;
	for(int i = 0; i < size; i++){
		if(abs(Points[i].x - midx) < distance)
			leftAndRightPts[j++] = Points[i]; //guarda todos os pontos que se encontram à distância currentMin do meio do vetor de pontos
	}
	merge(leftAndRightPts, j, 1); //sinaliza que os pontos devem ser ordenados pela coordenada Y --> O(nlgn)
	printPoints(leftAndRightPts, j);
	for(int i = 0; i < j - 1; i++){
		int k = i + 1;
		while(k <= j && (abs(leftAndRightPts[k].y - leftAndRightPts[i].y) < distance)){
			double dist = euclidianDistance(leftAndRightPts[k], leftAndRightPts[i]);
			if(dist < distance){
				distance = dist;
				TNo pt1 = createTNo(leftAndRightPts[k].x, leftAndRightPts[k].y);
            	TNo pt2 = createTNo(leftAndRightPts[i].x, leftAndRightPts[i].y);
            	setPair(&pair, pt1, pt2);
            	setDistance(&pair, dist);
			}
			k++;
		}
	}
	return pair;
}

//força bruta O(n^2)
TPair bruteForce(TNo* Points, int size){
    double min = DBL_MAX;
    TPair pair;
    if(size == 1){
    	pair.point1 = Points[0];
    	pair.point2 = Points[0];
    	pair.distance = 0;
    	return pair;
    }
    for (int i = 0; i < size; i++){
        for (int j = i+1; j < size; j++){
            if (euclidianDistance(Points[i], Points[j]) < min){
            	min = euclidianDistance(Points[i], Points[j]);
            	TNo pt1 = createTNo(Points[i].x, Points[i].y);
            	TNo pt2 = createTNo(Points[j].x, Points[j].y);
            	setPair(&pair, pt1, pt2);
            	setDistance(&pair, min);
            }
        }
    }
    return pair;
}
