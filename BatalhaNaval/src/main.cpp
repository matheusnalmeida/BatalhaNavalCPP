#include <iostream>
#include "Jogo.h"

int main() {
	Jogo* jogo = new Jogo();
	//jogo->getCPU()->printarTabuleiro();
	jogo->iniciarJogo();
	delete jogo;
}
