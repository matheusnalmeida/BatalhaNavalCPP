#include "Tabuleiro.h"
#include <iostream>
#include "Barco.h"
#include <cstdlib>
#include <ctime>

Tabuleiro::Tabuleiro()
{
	/*
	Cada caracter na matriz ira ter os seguintes significados:
	- 0: Agua
	- x: Barco Ocupado
	- 1: Parte do barco ja destruida na posicao especifica
	*/
	this->matriz = new VetorDinamico<VetorDinamico<char>*>(10);
	//Criando as 10 colunas
	for (int i = 0; i < 10; i++) {
		VetorDinamico<char>* novaColuna = new VetorDinamico<char>(10);
		//Iniciando vetor com posicoes vazias
		for (int y = 0; y < 10; y++) {
			novaColuna->add('0');
		}
		this->matriz->add(novaColuna);
	}
	//Iniciando vetor de direcoes
	this->vetorDeDirecoes = new VetorDinamico<char>(4);
	this->vetorDeDirecoes->add('d'); this->vetorDeDirecoes->add('e'); this->vetorDeDirecoes->add('c'); this->vetorDeDirecoes->add('b');
	//Iniciando vetor de posicoes livres
	this->posicoes_livres1d = new VetorDinamico<int>(10);
	this->posicoes_livres2d = new VetorDinamico<VetorDinamico<int>*>(10);
	for (int i = 0; i < 10; i++) {
		this->posicoes_livres1d->add(i);
		VetorDinamico<int>* novaColuna = new VetorDinamico<int>(10);
		//Iniciando vetor com posicoes vazias
		for (int y = 0; y < 10; y++) {
			novaColuna->add(y);
		}
		this->posicoes_livres2d->add(novaColuna);
	}
	//Iniciando vetor de barcos
	this->vetorDeBarcos = new VetorDinamico<Barco*>(6);
	this->vetorDeBarcos->add(new Barco("porta-avioes", 5));
	this->vetorDeBarcos->add(new Barco("navio-tanques", 4));
	this->vetorDeBarcos->add(new Barco("contratorpedeiro", 3));
	this->vetorDeBarcos->add(new Barco("contratorpedeiro", 3));
	this->vetorDeBarcos->add(new Barco("submarino", 2));
	this->vetorDeBarcos->add(new Barco("submarino", 2));
	//Gerando barcos na matriz de forma aleatoria
	this->gerarTabuleiroAleatorio();
}

Tabuleiro::~Tabuleiro()
{
	//Deletando matriz
	for (int i = 0; i < 10; i++) {
		delete this->matriz->get(i);
	}
	delete this->matriz;
	//Deletando vetor de direcoes
	delete this->vetorDeDirecoes;
	//Deletando vetores de posicoes livres
	delete this->posicoes_livres1d;
	for (int i = 0; i < 10; i++) {
		delete this->posicoes_livres2d->get(i);
	}
	delete this->posicoes_livres2d;
	//Deletando vetor de barcos
	for (int i = 0; i < this->vetorDeBarcos->size(); i++) {
		delete this->vetorDeBarcos->get(i);
	}
	delete this->vetorDeBarcos;
}

void Tabuleiro::gerarTabuleiroAleatorio()
{
	srand(time(NULL));
	for (int i = 0; i < this->vetorDeBarcos->size(); i++)
	{
		int x_gerado = rand() % this->posicoes_livres1d->size();
		int y_gerado = rand() % this->posicoes_livres2d->get(x_gerado)->size();
		if (!this->cadastrarBarco(this->posicoes_livres1d->get(x_gerado), this->posicoes_livres2d->get(x_gerado)->get(y_gerado), this->vetorDeBarcos->get(i))) {
			i--;
		}
		this->posicoes_livres2d->get(x_gerado)->remove(y_gerado);
		if (this->posicoes_livres2d->get(x_gerado)->isEmpty()) {
			this->posicoes_livres2d->remove(x_gerado);
			this->posicoes_livres1d->remove(x_gerado);
		}
	}
}

bool Tabuleiro::cadastrarBarco(int x,int y,Barco* barco)
{
	int tamanho_barco = barco->getTamanho();
	char valor_pos = this->valorLinhaColuna(x, y);
	if (valor_pos == '0' && (this->validaCoordenadas(x,y))) {
		//Copiando os dados do vetor de direcao para outro vetor
		VetorDinamico<char>* vetorDeDirecoesCopia = new VetorDinamico<char>(4);
		for (int i = 0; i < this->vetorDeDirecoes->size(); i++) {
			vetorDeDirecoesCopia->add(vetorDeDirecoes->get(i));
		}
		int posicaoInicio;
		int posicaoFim;
		char direcaoNovoBarco;
		while (true) {
			direcaoNovoBarco = this->escolherDirecao(vetorDeDirecoesCopia);
			switch (direcaoNovoBarco) {
			case 'd':
				posicaoInicio = y;
				posicaoFim = (posicaoInicio + tamanho_barco) - 1;
				if (this->validaIntervalo(x, y, posicaoInicio, posicaoFim, direcaoNovoBarco)) {
					for (int i = posicaoInicio; i <= posicaoFim; i++) {
						this->matriz->get(x)->insert(i, 'x');
					}
					return true;
				}
				break;
			case 'e':
				posicaoInicio = y;
				posicaoFim = (posicaoInicio - tamanho_barco) + 1;
				if (this->validaIntervalo(x, y, posicaoInicio, posicaoFim, direcaoNovoBarco)) {
					for (int i = posicaoInicio; i >= posicaoFim; i--) {
						this->matriz->get(x)->insert(i, 'x');
					}
					return true;
				}
				break;
			case 'c':
				posicaoInicio = x;
				posicaoFim = (posicaoInicio - tamanho_barco) + 1;
				if (this->validaIntervalo(x, y, posicaoInicio, posicaoFim, direcaoNovoBarco)) {
					for (int i = posicaoInicio; i >= posicaoFim; i--) {
						this->matriz->get(i)->insert(y, 'x');
					}
					return true;
				}
				break;
			case 'b':
				posicaoInicio = x;
				posicaoFim = (posicaoInicio + tamanho_barco) - 1;
				if (this->validaIntervalo(x, y, posicaoInicio, posicaoFim, direcaoNovoBarco)) {
					for (int i = posicaoInicio; i <= posicaoFim; i++) {
						this->matriz->get(i)->insert(y, 'x');
					}
					return true;
				}
				break;
			default:
				break;
			}
			if (vetorDeDirecoesCopia->isEmpty()) {
				return false;
			}
		}
	}
	return false;
}

void Tabuleiro::printarTabuleiro()
{
	for (int i = 0; i < this->matriz->size(); i++) {
		for (int y = 0; y < this->matriz->get(i)->size(); y++) {
			std::cout << this->matriz->get(i)->get(y) << " ";
		}
		std::cout << std::endl;
	}
}

char Tabuleiro::valorLinhaColuna(int x, int y)
{
	return this->matriz->get(x)->get(y);
}

bool Tabuleiro::validaIntervalo(int x,int y,int posicaoInicio, int posicaoFim, char direcao)
{
	if ((0 > posicaoInicio || posicaoInicio > 10) || (0 > posicaoFim || posicaoFim > 10)) {
		return false;
	}
	//Armazenando todas as posicoes que arredoam a posicao inicial do barco atual
	int posicaoDireita[] = {x,y+1};
	int posicaoEsquerda[] = {x,y - 1 };
	int posicaoCima[] = { x - 1 ,y};
	int posicaoBaixo[] = { x + 1,y};
	int posicaoSupDir[] = { posicaoDireita[0] + 1,posicaoDireita[1] };
	int posicaoInfDir[] = { posicaoDireita[0] - 1,posicaoDireita[1] };
	int posicaoSupEsq[] = { posicaoEsquerda[0] - 1,posicaoEsquerda[1] };
	int posicaoInfEsq[] = { posicaoEsquerda[0] + 1,posicaoEsquerda[1] };
	//Validando cada posicao ao redor da posicao inicial e verificando se as posicoes nao possuem barco
	if (this->validaCoordenadas(x,y)) {
		if (this->matriz->get(x)->get(y) != '0') {
			return false;
		}
	}
	else {
		return false;
	}
	if (this->validaCoordenadas(posicaoDireita[0], posicaoDireita[1])) {
		if (this->matriz->get(posicaoDireita[0])->get(posicaoDireita[1]) != '0') {
			return false;
		}
	}
	if (this->validaCoordenadas(posicaoEsquerda[0], posicaoEsquerda[1])) {
		if (this->matriz->get(posicaoEsquerda[0])->get(posicaoEsquerda[1]) != '0') {
			return false;
		}
	}
	if (this->validaCoordenadas(posicaoCima[0], posicaoCima[1])) {
		if (this->matriz->get(posicaoCima[0])->get(posicaoCima[1]) != '0') {
			return false;
		}
	}
	if (this->validaCoordenadas(posicaoBaixo[0], posicaoBaixo[1])) {
		if (this->matriz->get(posicaoBaixo[0])->get(posicaoBaixo[1]) != '0') {
			return false;
		}
	}
	if (this->validaCoordenadas(posicaoSupDir[0], posicaoSupDir[1])) {
		if (this->matriz->get(posicaoSupDir[0])->get(posicaoSupDir[1]) != '0') {
			return false;
		}
	}
	if (this->validaCoordenadas(posicaoInfDir[0], posicaoInfDir[1])) {
		if (this->matriz->get(posicaoInfDir[0])->get(posicaoInfDir[1]) != '0') {
			return false;
		}
	}
	if (this->validaCoordenadas(posicaoSupEsq[0], posicaoSupEsq[1])) {
		if (this->matriz->get(posicaoSupEsq[0])->get(posicaoSupEsq[1]) != '0') {
			return false;
		}
	}
	if (this->validaCoordenadas(posicaoInfEsq[0], posicaoInfEsq[1])) {
		if (this->matriz->get(posicaoInfEsq[0])->get(posicaoInfEsq[1]) != '0') {
			return false;
		}
	}
	
	switch (direcao)
	{
	case 'd':
		for (int i = posicaoInicio; i <= posicaoFim; i++) {
			int posicaoDireita[] = {x,i+1};
			int posicaoSupDireita[] = { posicaoDireita[0] - 1,posicaoDireita[1]};
			int posicaoInfDireita[] = { posicaoDireita[0] + 1,posicaoDireita[1]};
			if (i == posicaoFim) {
				if (this->validaCoordenadas(posicaoDireita[0], posicaoDireita[1])) {
					if (this->verificaBarcoExiste(posicaoDireita[0], posicaoDireita[1])) {
						return false;
					}
				}
				if (this->validaCoordenadas(posicaoSupDireita[0], posicaoSupDireita[1])) {
					if (this->verificaBarcoExiste(posicaoSupDireita[0], posicaoSupDireita[1])) {
						return false;
					}
				}if (this->validaCoordenadas(posicaoInfDireita[0], posicaoInfDireita[1])) {
					if (this->verificaBarcoExiste(posicaoInfDireita[0], posicaoInfDireita[1])) {
						return false;
					}
				}
				return true;
			}
			if (this->validaCoordenadas(posicaoDireita[0],posicaoDireita[1])) {
				if (this->validaCoordenadas(posicaoSupDireita[0], posicaoSupDireita[1])) {
					if (this->verificaBarcoExiste(posicaoSupDireita[0], posicaoSupDireita[1])) {
						return false;
					}
				}if (this->validaCoordenadas(posicaoInfDireita[0], posicaoInfDireita[1])) {
					if (this->verificaBarcoExiste(posicaoInfDireita[0], posicaoInfDireita[1])) {
						return false;
					}
				}
				if (this->verificaBarcoExiste(posicaoDireita[0], posicaoDireita[1])) {
						return false;
				}
			}
			else {
				return false;
			}
		}
		return true;
	case 'e':
		for (int i = posicaoInicio; i >= posicaoFim; i--) {
			int posicaoEsquerda[] = { x,i - 1 };
			int posicaoSupEsquerda[] = { posicaoEsquerda[0] - 1,posicaoEsquerda[1] };
			int posicaoInfEsquerda[] = { posicaoEsquerda[0] + 1,posicaoEsquerda[1] };
			if (i == posicaoFim) {
				if (this->validaCoordenadas(posicaoEsquerda[0], posicaoEsquerda[1])) {
					if (this->verificaBarcoExiste(posicaoEsquerda[0], posicaoEsquerda[1])) {
						return false;
					}
				}
				if (this->validaCoordenadas(posicaoSupEsquerda[0], posicaoSupEsquerda[1])) {
					if (this->verificaBarcoExiste(posicaoSupEsquerda[0], posicaoSupEsquerda[1])) {
						return false;
					}
				}if (this->validaCoordenadas(posicaoInfEsquerda[0], posicaoInfEsquerda[1])) {
					if (this->verificaBarcoExiste(posicaoInfEsquerda[0], posicaoInfEsquerda[1])) {
						return false;
					}
				}
				return true;
			}
			if (this->validaCoordenadas(posicaoEsquerda[0], posicaoEsquerda[1])) {
				if (this->validaCoordenadas(posicaoSupEsquerda[0], posicaoSupEsquerda[1])) {
					if (this->verificaBarcoExiste(posicaoSupEsquerda[0], posicaoSupEsquerda[1])) {
						return false;
					}
				}if (this->validaCoordenadas(posicaoInfEsquerda[0], posicaoInfEsquerda[1])) {
					if (this->verificaBarcoExiste(posicaoInfEsquerda[0], posicaoInfEsquerda[1])) {
						return false;
					}
				}
				if (this->verificaBarcoExiste(posicaoEsquerda[0], posicaoEsquerda[1])) {
					return false;
				}
			}
			else {
				return false;
			}
		}
		return true;
	case 'c':
		for (int i = posicaoInicio; i >= posicaoFim; i--) {
			int posicaoCima[] = { i-1,y };
			int posicaoCimaEsquerda[] = { posicaoEsquerda[0],posicaoEsquerda[1]-1};
			int posicaoCimaDireita[] = { posicaoEsquerda[0],posicaoEsquerda[1]+1};
			if (i == posicaoFim) {
				if (this->validaCoordenadas(posicaoCima[0], posicaoCima[1])) {
					if (this->verificaBarcoExiste(posicaoCima[0], posicaoCima[1])) {
						return false;
					}
				}
				if (this->validaCoordenadas(posicaoCimaEsquerda[0], posicaoCimaEsquerda[1])) {
					if (this->verificaBarcoExiste(posicaoCimaEsquerda[0], posicaoCimaEsquerda[1])) {
						return false;
					}
				}if (this->validaCoordenadas(posicaoCimaDireita[0], posicaoCimaDireita[1])) {
					if (this->verificaBarcoExiste(posicaoCimaDireita[0], posicaoCimaDireita[1])) {
						return false;
					}
				}
				return true;
			}
			if (this->validaCoordenadas(posicaoCima[0], posicaoCima[1])) {
				if (this->validaCoordenadas(posicaoCimaEsquerda[0], posicaoCimaEsquerda[1])) {
					if (this->verificaBarcoExiste(posicaoCimaEsquerda[0], posicaoCimaEsquerda[1])) {
						return false;
					}
				}if (this->validaCoordenadas(posicaoCimaDireita[0], posicaoCimaDireita[1])) {
					if (this->verificaBarcoExiste(posicaoCimaDireita[0], posicaoCimaDireita[1])) {
						return false;
					}
				}
				if (this->verificaBarcoExiste(posicaoCima[0], posicaoCima[1])) {
					return false;
				}
			}
			else {
				return false;
			}
		}
		return true;
	case 'b':
		for (int i = posicaoInicio; i <= posicaoFim; i++) {
			int posicaoBaixo[] = { i + 1,y };
			int posicaoBaixoEsq[] = { posicaoBaixo[0],posicaoBaixo[1] - 1 };
			int posicaoBaixoDir[] = { posicaoBaixo[0],posicaoBaixo[1] + 1 };
			if (i == posicaoFim) {
				if (this->validaCoordenadas(posicaoBaixo[0], posicaoBaixo[1])) {
					if (this->verificaBarcoExiste(posicaoBaixo[0], posicaoBaixo[1])) {
						return false;
					}
				}
				if (this->validaCoordenadas(posicaoBaixoEsq[0], posicaoBaixoEsq[1])) {
					if (this->verificaBarcoExiste(posicaoBaixoEsq[0], posicaoBaixoEsq[1])) {
						return false;
					}
				}if (this->validaCoordenadas(posicaoBaixoDir[0], posicaoBaixoDir[1])) {
					if (this->verificaBarcoExiste(posicaoBaixoDir[0], posicaoBaixoDir[1])) {
						return false;
					}
				}
				return true;
			}
			if (this->validaCoordenadas(posicaoBaixo[0], posicaoBaixo[1])) {
				if (this->validaCoordenadas(posicaoBaixoEsq[0], posicaoBaixoEsq[1])) {
					if (this->verificaBarcoExiste(posicaoBaixoEsq[0], posicaoBaixoEsq[1])) {
						return false;
					}
				}if (this->validaCoordenadas(posicaoBaixoDir[0], posicaoBaixoDir[1])) {
					if (this->verificaBarcoExiste(posicaoBaixoDir[0], posicaoBaixoDir[1])) {
						return false;
					}
				}
				if (this->verificaBarcoExiste(posicaoBaixo[0], posicaoBaixo[1])) {
					return false;
				}
			}
			else {
				return false;
			}
		}
		return true;
	default:
		return false;
	}
}

bool Tabuleiro::validaCoordenadas(int x, int y)
{
	if ((0 <= x && x < 10) && (0 <= y && y < 10)) {
		return true;
	}
	return false;
}

bool Tabuleiro::verificaBarcoExiste(int x, int y)
{
	if (this->matriz->get(x)->get(y) == 'x') {
		return true;
	}
	return false;
}

char Tabuleiro::escolherDirecao(VetorDinamico<char>* vetorDeDirecoes)
{

	srand(time(NULL));
	int posicaoDirecao = rand() % vetorDeDirecoes->size();
	char direcao = vetorDeDirecoes->get(posicaoDirecao);
	vetorDeDirecoes->remove(posicaoDirecao);
	return direcao;
}


