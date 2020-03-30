#pragma once
#include "Tabuleiro.h"


class Jogo {
private:
	void atirar(Tabuleiro tabuleiro);
	Tabuleiro* cpu;
	Tabuleiro* jogador;
public:
	Jogo();
	~Jogo();
	void iniciarJogo();
};