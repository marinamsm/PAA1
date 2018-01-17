
#include "Generator.h"
#include "TNo.h"
#include "TPair.h"

//COMPILAR: g++ *.cpp -o teste
/*EX. DE EXECUÇÃO PARA 5 PONTOS (com coordenada de 1 a 100) E COM A ENTRADA (pontos gerados) E A SAÍDA (para "depuração") NO ARQUIVO POINTS.TXT:
	teste 1 100 5 > points.txt < points.txt
*/ 
int main(int argc, char** argv) {
	if(argc != 4) {
		//a geração dos pontos vai continuar? O prof. já disponibiliza as próprias entradas?
		cout << "Passe 3 argumentos ao executar para gerar o arquivo com os pontos: numero inicial da faixa geradora de numeros aleatorios, numero final e quantidade de pontos" << endl;
		return 1;
	}
	int init, end, size;
	init = atoi(argv[1]);
	end = atoi(argv[2]);
	size = atoi(argv[3]);
	generatePoints(init, end, size); //gera números aleatórios na faixa de init até end para criar arquivo com size pontos
	TNo* Points = createPoints(size); //o nome TNo pode ser modificado
	//pre-processamento, podemos usar o qsort também que já vem pronto do próprio c++:
	merge(Points, size, 0); //a flag 0 sinaliza que os pontos devem ser ordenados pela coordenada X --> O(nlgn)
	TPair pair = closestPointDC(Points, size); //o prof quer que retorne a menor distância && o par de pontos que possui essa menor dist.
	TNo leftAndRightPts;
	cout << "Main pair1: " << pair.distance << " points: (" << pair.point1.x << ", " << pair.point1.y << ") " << "(" << pair.point2.x << ", " << pair.point2.y << ") " << endl;
	//ATÉ AQUI FUNCIONA TUDO CERTO
	TPair pair2 = CPDC(&leftAndRightPts, Points, size, pair.distance); //esta função está errada, achei várias formas de fazê-la, mas essa não deu
	cout << "Main pair2: " << pair2.distance << " points: (" << pair2.point1.x << ", " << pair2.point1.y << ") " << "(" << pair2.point2.x << ", " << pair2.point2.y << ") " << endl;
	cout << "Main pair1 AGAIN: " << pair.distance << " points: (" << pair.point1.x << ", " << pair.point1.y << ") " << "(" << pair.point2.x << ", " << pair.point2.y << ") " << endl;
	if(pair.distance > pair2.distance)
		pair = pair2;
	cout << "Min(Total) = " << pair.distance << " points: (" << pair.point1.x << ", " << pair.point1.y << ") " << "(" << pair.point2.x << ", " << pair.point2.y << ") " << endl;
	cout << endl << "-----DC-----" << endl;
	cout << "(" << pair.point1.x << ", " << pair.point1.y << ") " << "(" << pair.point2.x << ", " << pair.point2.y << ") " << pair.distance << endl;
	cout << "-----END----" << endl;
	pair = bruteForce(Points, size); //o prof. pediu dois métodos, por DC e algum outro, este sempre acerta, é bom para comparar com o de DC
	cout << endl << "-----FB-----" << endl;
	cout << "(" << pair.point1.x << ", " << pair.point1.y << ") " << "(" << pair.point2.x << ", " << pair.point2.y << ") " << pair.distance << endl;
	cout << "-----END----" << endl;
	delete[] Points;
	return 0;
}