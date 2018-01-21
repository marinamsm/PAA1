
#include "Generator.h"

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
	return 0;
}