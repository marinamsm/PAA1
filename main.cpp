
#include "TPoint.h"
#include "TPair.h"
#include <stdlib.h>
#include <time.h>

//COMPILAR: g++ *.cpp -o teste
/*EX. DE EXECUÇÃO PARA 1000 PONTOS NO ARQUIVO grupo1-1000pontos.txt:
	teste 1000 < grupo1-1000pontos.txt
*/ 
int main(int argc, char** argv) {
	int size = atoi(argv[1]);
	TPoint* Points = createPoints(size);
	double durationDC = 0.0;
	double durationBF = 0.0;
	clock_t inicio;
  	inicio=clock();
	//pre-processamento, podemos usar o qsort também que já vem pronto do próprio c++:
	merge(Points, size, 0); //a flag 0 sinaliza que os pontos devem ser ordenados pela coordenada X --> O(nlgn)
	TPair pair = closestPointDC(Points, size); //o prof quer que retorne a menor distância && o par de pontos que possui essa menor dist.
	durationDC = ((clock()-inicio)*1000.0)/CLOCKS_PER_SEC;
	cout << endl << "-----DC-----" << endl;
	cout << endl << "Ponto 1: (" << pair.point1.x << ", " << pair.point1.y << ") " << "Ponto 2: (" << pair.point2.x << ", " << pair.point2.y << ") "
	<< "Distancia = " << pair.distance << " Duracao: " << durationDC << " ms" << endl;
	cout << endl << "-----END----" << endl;
	inicio=clock();
	pair = bruteForce(Points, size); //o prof. pediu dois métodos, por DC e algum outro, este sempre acerta, é bom para comparar com o de DC
	durationBF = ((clock()-inicio)*1000.0)/CLOCKS_PER_SEC;
	cout << endl << "-----FB-----" << endl;
	cout << endl << "Ponto 1: (" << pair.point1.x << ", " << pair.point1.y << ") " << "Ponto 2: (" << pair.point2.x << ", " << pair.point2.y << ") "
	<< "Distancia = " << pair.distance << " Duracao: " << durationBF << " ms" << endl;
	cout << endl << "-----END----" << endl;
	delete[] Points;
	return 0;
}