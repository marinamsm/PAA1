
#include "TPair.h"

void setPair(TPair* Pair, TPoint pt1, TPoint pt2){
	Pair->point1 = pt1;
	Pair->point2 = pt2;
}

void setDistance(TPair* Pair, double distance){
	Pair->distance = distance;
}

//Parte de dividir e conquistar
TPair closestPointDC(TPoint* Points, int size){
	TPair pair;
	if (size <= 3){
		pair = bruteForce(Points, size); //tempo constante
		return pair;
	}
	int half = size/2; //divide o plano dos pontos ao meio
	TPoint* LeftPoints = new TPoint[half]; //guarda os pontos do lado esquerdo
	copy(LeftPoints, Points, 0, half);
	TPoint* RightPoints = new TPoint[size-half]; //guarda os pontos do lado direito
	copy(RightPoints, Points, half, size);
	TPair leftDist = closestPointDC(LeftPoints, half); //encontra o par de menor distância no quadrante esquerdo atual do plano
	TPair rightDist = closestPointDC(RightPoints, size-half); //encontra o par de menor distância no quadrante direito atual do plano
	if(leftDist.distance < rightDist.distance) //verifica em qual dos dois quadrantes está o par de menor distância atualmente
		pair = leftDist;
	else pair = rightDist;
	TPair pair2 = CPDC(Points, size, pair.distance); //encontra o par de menor distância com um ponto no quadrante esquerdo e um no direito
	if(pair2.distance < pair.distance) //verifica qual é o par de menor distância do plano
		pair = pair2;
	return pair; //retorna o par de distância mínima
}

double euclidianDistance(TPoint p1, TPoint p2){
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

/*Parte de combinar
Esta parte deve verificar em uma faixa de pontos que pegue tanto pontos do quadrante esquerdo quanto direito o par de menor distância
para depois comparar com o que foi encontrado em closestPointDC e obter o menor de todos do plano*/
TPair CPDC(TPoint* Points, int size, double distance){
	int midx = Points[size/2].x; //coordenada X do meio do vetor de pontos (já ordenados por X)
	int j = 0;
	TPair pair;
	TPoint* leftAndRightPts = new TPoint[size]; //para guardar os pontos da faixa central do plano
	pair.distance = DBL_MAX;
	for(int i = 0; i < size; i++){
		if(abs(Points[i].x - midx) < distance)
			leftAndRightPts[j++] = Points[i]; //guarda todos os pontos que se encontram na faixa central do plano
	}
	merge(leftAndRightPts, j, 1); //1 sinaliza que os pontos devem ser ordenados pela coordenada Y --> O(nlgn)
	for(int i = 0; i < j - 1; i++){
		int k = i + 1;
		//calcula a distância entre as coordenadas y de cada ponto
		while(k <= j && (abs(leftAndRightPts[k].y - leftAndRightPts[i].y) < distance)){
			double dist = euclidianDistance(leftAndRightPts[k], leftAndRightPts[i]);
			//se a distância for menor que a distância mínima atual então foi encontrado um novo par
			if(dist < distance){
				distance = dist;
				TPoint pt1 = createTPoint(leftAndRightPts[k].x, leftAndRightPts[k].y);
            	TPoint pt2 = createTPoint(leftAndRightPts[i].x, leftAndRightPts[i].y);
            	setPair(&pair, pt1, pt2);
            	setDistance(&pair, dist);
			}
			k++;
		}
	}
	delete[] leftAndRightPts;
	//retorna o par de distância mínima ou com distância infinita caso não exista nenhum na faixa central
	return pair; 
}

//força bruta O(n^2)
TPair bruteForce(TPoint* Points, int size){
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
            	TPoint pt1 = createTPoint(Points[i].x, Points[i].y);
            	TPoint pt2 = createTPoint(Points[j].x, Points[j].y);
            	setPair(&pair, pt1, pt2);
            	setDistance(&pair, min);
            }
        }
    }
    return pair;
}
