
#include "TPair.h"

void setPair(TPair* Pair, TNo pt1, TNo pt2){
	Pair->point1 = pt1;
	Pair->point2 = pt2;
}

void setDistance(TPair* Pair, double distance){
	Pair->distance = distance;
}

//Parte de dividir e conquistar (está toda ok)
TPair closestPointDC(TNo* Points, int size){
	TPair pair;
	if (size <= 3){
		pair = bruteForce(Points, size); //tempo constante
		return pair;
	}
	int half = size/2;
	TNo* LeftPoints = new TNo[half];
	copy(LeftPoints, Points, 0, half);
	cout <<"LP"<<endl;
	printPoints(LeftPoints, half);
	TNo* RightPoints = new TNo[size-half];
	copy(RightPoints, Points, half, size);
	cout <<"RP"<<endl;
	printPoints(RightPoints, size-half);
	TPair leftDist = closestPointDC(LeftPoints, half); //encontra o par de menor distância no quadrante esquerdo atual do plano
	cout << "leftDist = " << leftDist.distance << " points: (" << leftDist.point1.x << ", " << leftDist.point1.y << ") " << "(" << leftDist.point2.x << ", " << leftDist.point2.y << ") " << endl;
	TPair rightDist = closestPointDC(RightPoints, size-half); //encontra o par de menor distância no quadrante direito atual do plano
	cout << "rightDist = " << rightDist.distance << " points: (" << rightDist.point1.x << ", " << rightDist.point1.y << ") " << "(" << rightDist.point2.x << ", " << rightDist.point2.y << ") " << endl;
	if(leftDist.distance < rightDist.distance)
		pair = leftDist;
	else pair = rightDist;
	cout << "Min(L, R) = " << pair.distance << " points: (" << pair.point1.x << ", " << pair.point1.y << ") " << "(" << pair.point2.x << ", " << pair.point2.y << ") " << endl;
	TPair pair2 = CPDC(Points, size, pair.distance); //esta função está errada, achei várias formas de fazê-la, mas essa não deu
	if(pair2.distance < pair.distance)
		pair = pair2;
	return pair; //retorna o par de distância mínima que está OU na esquerda OU na direita
}

double euclidianDistance(TNo p1, TNo p2){
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

/*Parte de combinar
Esta parte deve verificar em uma faixa de pontos que pegue tanto pontos do quadrante esquerdo quanto direito o par de menor distância
para depois comparar com o que foi encontrado em closestPointDC e obter o menor de todos do plano*/
//ESTA FUNÇÃO ESTÁ ERRADA E HÁ DIFERENTES FORMAS DE FAZÊ-LA
//O erro costuma ser mais percebido acima de 5 ou 7 pontos
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
	cout << "-----LR-----" << endl;
	merge(leftAndRightPts, j, 1); //sinaliza que os pontos devem ser ordenados pela coordenada Y --> O(nlgn)
	printPoints(leftAndRightPts, j);
	for(int i = 0; i < j - 1; i++){
		int k = i + 1;
		//if(k == j) break;
		while(k <= j && (abs(leftAndRightPts[k].y - leftAndRightPts[i].y) < distance)){
			double dist = euclidianDistance(leftAndRightPts[k], leftAndRightPts[i]);
			cout << "dist && distance " << dist << " && " << distance << endl;
			if(dist < distance){
				distance = dist;
				TNo pt1 = createTNo(leftAndRightPts[k].x, leftAndRightPts[k].y);
            	TNo pt2 = createTNo(leftAndRightPts[i].x, leftAndRightPts[i].y);
            	cout << endl;
            	cout << "pt1 " << pt1.x << "," << pt1.y << endl;
            	cout << "pt2 " << pt2.x << "," << pt2.y << endl;
            	cout << "TESTE ANTES " << pair.distance <<" (" << pair.point1.x << ", " << pair.point1.y << ") " << " (" << pair.point2.x << ", " << pair.point2.y << ")" << endl; 
            	setPair(&pair, pt1, pt2);
            	setDistance(&pair, dist);
            	cout << "TESTE DEPOIS " << pair.distance <<" (" << pair.point1.x << ", " << pair.point1.y << ") " << " (" << pair.point2.x << ", " << pair.point2.y << ")" << endl; 
			}
			k++;
		}
	}
	cout << "---CPDC---" << endl << pair.distance << " points: (" << pair.point1.x << ", " << pair.point1.y << ") " << "(" << pair.point2.x << ", " << pair.point2.y << ") " << endl;
	return pair;
}

//O força bruta está correto, podemos usá-lo para saber se o DC está correto ou não
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
    cout << "brute currentMin = " << min << " points: (" << pair.point1.x << ", " << pair.point1.y << ") " << "(" << pair.point2.x << ", " << pair.point2.y << ") " << endl;
    return pair;
}
