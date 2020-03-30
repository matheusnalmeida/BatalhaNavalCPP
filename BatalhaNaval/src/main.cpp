#include <iostream>
#include "Tabuleiro.h"

int main() {
	Tabuleiro* tabuleiro = new Tabuleiro();
	tabuleiro->printarTabuleiro();
	delete tabuleiro;
}