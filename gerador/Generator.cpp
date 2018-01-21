
#include "Generator.h"

void generatePoints(int init, int end, int size) {
	
	/* coordenadas do ponto: */
	int num1, num2;
	
	/* inicializa a semente: */
	srand (time(NULL));

	/* gera um número entre init e end por size vezes: */
	for(int i = 0; i < size; i++) {
		num1 = rand() % end + init;
		num2 = rand() % end + init;
		cout << num1 << " " << num2 << endl;
	}
  
}