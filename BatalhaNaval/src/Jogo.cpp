#include "Jogo.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

std::string Jogo::atirar(Tabuleiro* tabuleiro,int x,int y)
{
	return tabuleiro->atirarEmBarco(x, y);
}

Jogo::Jogo()
{
	this->cpu = new Tabuleiro();
	this->jogador = new Tabuleiro();
}

Jogo::~Jogo()
{
	delete this->cpu;
	delete this->jogador;
}

void Jogo::iniciarJogo()
{
	srand(time(NULL));
	bool vezDaCPU = false;
	int linha;
	int coluna;
	while (true) {
		if (!vezDaCPU) {
			std::cout << "----------------------------------------------Vez do Jogador-----------------------------------------------" << std::endl;
			std::cout << std::endl;
			std::cout << "Digite a linha em que deseja atirar: " << std::endl;
			std::cin >> linha;
			std::cout << "Digite a coluna em que deseja atirar: " << std::endl;
			std::cin >> coluna;
			if ((0 <= linha && linha < 10) && (0 <= coluna && coluna < 10)) {
				std::string resp_at = this->atirar(this->getCPU(), linha, coluna);
				if (resp_at.find("ACERTOU") != std::string::npos) {
					std::cout << resp_at << std::endl;
					if (this->getCPU()->retornaQuantidadeDeBarcos() == 0) {
						std::cout << "Parabens voce ganhou!" << std::endl;
						break;
					}
				}
				else {
					std::cout << "Voce deu um tiro na " <<  resp_at << std::endl;
					vezDaCPU = true;
				}
				std::cout << "-----------------------Restam as seguintes embarcacoes da cpu------------------------------" << std::endl;
				VetorDinamico<Barco*>* barcos_cpu = this->getCPU()->retornarBarcos();
				for (int i = 0; i < barcos_cpu->size(); i++) {
					std::cout << (i + 1) << ": " << barcos_cpu->get(i)->getNome() << std::endl;
				}
			}
			else {
				std::cout << "Posicao Invalida!\n Digite um valor valido para linha e coluna(entre 0 e 9) " << std::endl;
			}
		}else {
			std::cout << "----------------------------------------------Vez da CPU-----------------------------------------------" << std::endl;
			linha = rand() % 10;
			coluna = rand() % 10;
			std::string resp_at = this->atirar(this->getJogador(), linha, coluna);
			if (resp_at.find("ACERTOU") != std::string::npos) {
				std::cout << resp_at << std::endl;
				if (this->getJogador()->retornaQuantidadeDeBarcos() == 0) {
					std::cout << "Voce perdeu!" << std::endl;
					break;
				}
			}
			else {
				std::cout << "A cpu deu um tiro na " << resp_at << std::endl;
				vezDaCPU = false;
			}
			std::cout << "-----------------------Restam as seguintes embarcacoes do Jogador------------------------------" << std::endl;
			VetorDinamico<Barco*>* barcos_jogador = this->getJogador()->retornarBarcos();
			for (int i = 0; i < barcos_jogador->size(); i++) {
				std::cout << (i + 1) << ": " << barcos_jogador->get(i)->getNome() << std::endl;
			}
		}
	}
	std::cout << "Programa finalizado" << std::endl;
}

Tabuleiro* Jogo::getCPU()
{
	return this->cpu;
}

Tabuleiro* Jogo::getJogador()
{
	return this->jogador;
}
