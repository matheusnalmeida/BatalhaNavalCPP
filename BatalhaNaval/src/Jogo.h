#pragma once
#include "Tabuleiro.h"
#include <string>

class Jogo {
private:
	std::string atirar(Tabuleiro* tabuleiro,int x, int y);
	Tabuleiro* cpu;
	Tabuleiro* jogador;
public:
	Jogo();
	~Jogo();
	void iniciarJogo();
	Tabuleiro* getCPU();
	Tabuleiro* getJogador();
};